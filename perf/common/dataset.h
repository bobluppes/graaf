#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "common/dataset_dir.h"

namespace perf_common {

enum class dataset { WEB_GOOGLE, WEB_BERK_STAN };

namespace detail {

struct dataset_file {
  std::filesystem::path filename{};
  std::size_t number_of_header_lines{};
};

inline const std::unordered_map<dataset, dataset_file>& datasets() {
  static const std::unordered_map<dataset, dataset_file> value{
      {dataset::WEB_GOOGLE, dataset_file{.filename = WEB_GOOGLE_FILENAME,
                                         .number_of_header_lines = 4}},
      {dataset::WEB_BERK_STAN, dataset_file{.filename = WEB_BERK_STAN_FILENAME,
                                            .number_of_header_lines = 4}}};
  return value;
}

struct vertex_pair_hash {
  std::size_t operator()(
      const std::pair<std::size_t, std::size_t>& pair) const noexcept {
    return std::hash<std::size_t>{}(pair.first) ^
           (std::hash<std::size_t>{}(pair.second) << 1);
  }
};

}  // namespace detail

// Streams the edge list for the given dataset, invoking
// edge_callback(source, target) once per unique undirected edge.
//
// The source datasets are directed and may contain reciprocal edges
// (source->target and target->source); since every benchmark comparison
// here treats them as undirected graphs, those reciprocal pairs are
// only reported once.
//
// This has no dependency on any particular graph library, so every
// benchmark - regardless of which graph library it exercises - builds its
// graph from exactly the same edge list.
template <typename EDGE_CALLBACK_T>
void read_dataset_edges(const dataset& dataset_name,
                        EDGE_CALLBACK_T&& edge_callback) {
  const auto& info{detail::datasets().at(dataset_name)};
  const auto path{std::filesystem::path(DATASET_DIR) / info.filename};

  std::ifstream file{};
  file.open(path);
  if (!file.is_open()) {
    throw std::runtime_error(
        "Could not open dataset file: " + path.string() +
        ". Re-run cmake with -DGRAAF_DOWNLOAD_PERF_DATASETS=ON to download "
        "it.");
  }

  std::string line;

  for (std::size_t i{0}; i < info.number_of_header_lines; ++i) {
    std::getline(file, line);
  }

  std::unordered_set<std::pair<std::size_t, std::size_t>,
                     detail::vertex_pair_hash>
      seen_edges{};

  while (std::getline(file, line)) {
    const auto delim{line.find('\t')};
    const auto source{
        static_cast<std::size_t>(std::stoull(line.substr(0, delim)))};
    const auto target{
        static_cast<std::size_t>(std::stoull(line.substr(delim + 1)))};

    const auto normalized{source < target ? std::make_pair(source, target)
                                          : std::make_pair(target, source)};
    if (seen_edges.insert(normalized).second) {
      edge_callback(source, target);
    }
  }
}

}  // namespace perf_common
