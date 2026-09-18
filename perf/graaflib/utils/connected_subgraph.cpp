#include "connected_subgraph.h"

#include <unordered_map>

#include "common/connected_subgraph.h"

namespace utils {

namespace {

int UNIT_WEIGHT{1};

}  // namespace

connected_subgraph_result construct_connected_subgraph(
    const dataset& dataset_name, const graaf::vertex_id_t start_vertex,
    const std::size_t max_vertices) {
  const auto raw{perf_common::compute_connected_subgraph(
      dataset_name, start_vertex, max_vertices)};

  graph_t connected_subgraph{};
  std::unordered_map<std::size_t, graaf::vertex_id_t> compact_index{};
  compact_index.reserve(raw.vertices.size());
  for (const auto vertex : raw.vertices) {
    compact_index.emplace(vertex, connected_subgraph.add_vertex(no_data{}));
  }

  for (const auto& [source, target] : raw.edges) {
    connected_subgraph.add_edge(compact_index.at(source),
                                compact_index.at(target), UNIT_WEIGHT);
  }

  return {std::move(connected_subgraph), compact_index.at(start_vertex)};
}

}  // namespace utils
