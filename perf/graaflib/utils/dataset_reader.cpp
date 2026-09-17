#include "dataset_reader.h"

#include <map>

#include "common/dataset.h"

namespace utils {

namespace {

int UNIT_WEIGHT{1};

}  // namespace

const graph_t& construct_graph_from_file(const dataset& dataset_name) {
  static std::map<dataset, graph_t> cache{};
  if (const auto it{cache.find(dataset_name)}; it != cache.end()) {
    return it->second;
  }

  graph_t graph{};

  perf_common::read_dataset_edges(
      dataset_name, [&graph](std::size_t source, std::size_t target) {
        if (!graph.has_vertex(source)) {
          graph.add_vertex(no_data{}, source);
        }

        if (!graph.has_vertex(target)) {
          graph.add_vertex(no_data{}, target);
        }

        graph.add_edge(source, target, UNIT_WEIGHT);
      });

  const auto [inserted_it,
              inserted]{cache.emplace(dataset_name, std::move(graph))};
  return inserted_it->second;
}

}  // namespace utils
