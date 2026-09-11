#pragma once
#include "utils.h"

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
directed_graph<VERTEX_T, EDGE_T> get_transposed_graph(
    const directed_graph<VERTEX_T, EDGE_T>& graph) {
  directed_graph<VERTEX_T, EDGE_T> transposed_graph{};

  for (const auto& [vertex_id, vertex_value] : graph.get_vertices()) {
    transposed_graph.add_vertex(vertex_value, vertex_id);
  }

  for (auto [edge_vertices, edge_type] : graph.get_edges()) {
    const auto [vertex_id_lhs, vertex_id_rhs] = edge_vertices;

    transposed_graph.add_edge(vertex_id_rhs, vertex_id_lhs,
                              std::move(edge_type));
  }

  return transposed_graph;
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
std::unordered_map<vertex_id_t, std::unordered_set<vertex_id_t>>
get_predecessors(const graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>& graph) {
  std::unordered_map<vertex_id_t, std::unordered_set<vertex_id_t>>
      predecessors{};
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    for (const auto& neighbor_id : graph.get_neighbors(vertex_id)) {
      predecessors[neighbor_id].insert(vertex_id);
    }
  }
  return predecessors;
}

}  // namespace graaf
