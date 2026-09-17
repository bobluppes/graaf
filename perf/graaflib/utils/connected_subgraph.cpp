#include "connected_subgraph.h"

#include "common/connected_subgraph.h"

namespace utils {

graph_t compute_connected_subgraph(const graph_t& graph,
                                   const dataset& dataset_name,
                                   const graaf::vertex_id_t start_vertex,
                                   const std::size_t max_vertices) {
  const auto raw{perf_common::compute_connected_subgraph(
      dataset_name, start_vertex, max_vertices)};

  graph_t connected_subgraph{};
  for (const auto vertex : raw.vertices) {
    connected_subgraph.add_vertex(graph.get_vertex(vertex), vertex);
  }

  for (const auto& [source, target] : raw.edges) {
    connected_subgraph.add_edge(source, target, graph.get_edge(source, target));
  }

  return connected_subgraph;
}

}  // namespace utils
