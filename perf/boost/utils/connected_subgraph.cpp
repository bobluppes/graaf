#include "connected_subgraph.h"

#include <unordered_map>

#include "common/connected_subgraph.h"

namespace utils {

namespace {

int UNIT_WEIGHT{1};

}  // namespace

connected_subgraph_result construct_connected_subgraph(
    const dataset& dataset_name, const std::size_t start_vertex,
    const std::size_t max_vertices) {
  const auto raw{perf_common::compute_connected_subgraph(
      dataset_name, start_vertex, max_vertices)};

  std::unordered_map<std::size_t, std::size_t> compact_index{};
  compact_index.reserve(raw.vertices.size());
  for (std::size_t i{0}; i < raw.vertices.size(); ++i) {
    compact_index.emplace(raw.vertices[i], i);
  }

  graph_t graph{raw.vertices.size()};
  for (const auto& [source, target] : raw.edges) {
    boost::add_edge(compact_index.at(source), compact_index.at(target),
                    UNIT_WEIGHT, graph);
  }

  return {std::move(graph), compact_index.at(start_vertex)};
}

}  // namespace utils
