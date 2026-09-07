#include "dataset_reader.h"

#include <graaflib/utils/dataset_dir.h>

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace utils {

namespace {

struct graph_file {
  std::filesystem::path filename{};
  std::size_t number_of_header_lines{};
};

const std::unordered_map<dataset, graph_file> DATASETS{
    {dataset::WEB_GOOGLE,
     graph_file{.filename = WEB_GOOGLE_FILENAME, .number_of_header_lines = 4}},
    {dataset::WEB_BERK_STAN, graph_file{.filename = WEB_BERK_STAN_FILENAME,
                                        .number_of_header_lines = 4}}};

int UNIT_WEIGHT{1};

}  // namespace

graph_t construct_graph_from_file(const dataset& dataset_name) {
  const auto& dataset{DATASETS.at(dataset_name)};
  const auto path{std::filesystem::path(DATASET_DIR) / dataset.filename};

  std::ifstream file{};
  file.open(path);
  if (!file.is_open()) {
    throw std::runtime_error(
        "Could not open dataset file: " + path.string() +
        ". Re-run cmake with -DGRAAF_DOWNLOAD_PERF_DATASETS=ON to download "
        "it.");
  }

  std::string line;

  // Skip the header lines
  for (int i{0}; i < dataset.number_of_header_lines; ++i) {
    std::getline(file, line);
  }

  graph_t graph{};

  while (std::getline(file, line)) {
    const auto delim{line.find("\t")};
    const auto source{std::stoi(line.substr(0, delim))};
    const auto target{std::stoi(line.substr(delim, line.size() - delim))};

    if (!graph.has_vertex(source)) {
      graph.add_vertex(no_data{}, source);
    }

    if (!graph.has_vertex(target)) {
      graph.add_vertex(no_data{}, target);
    }

    graph.add_edge(source, target, UNIT_WEIGHT);
  }

  return graph;
}

}  // namespace utils
