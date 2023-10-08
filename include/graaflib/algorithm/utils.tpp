#pragma once

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
directed_graph<VERTEX_T, EDGE_T> get_transposed_graph(
    const directed_graph<VERTEX_T, EDGE_T>& graph) {
  directed_graph<VERTEX_T, EDGE_T> transposed_graph{};
  for (auto [edge_vertices, edge_type] : graph.get_edges()) {
    const auto [vertex_id_lhs, vertex_id_rhs] = edge_vertices;

    auto vertex_value_lhs = graph.get_vertex(vertex_id_lhs);
    auto vertex_value_rhs = graph.get_vertex(vertex_id_rhs);

    if (!transposed_graph.has_vertex(vertex_id_lhs)) {
      auto vertex_id = transposed_graph.add_vertex(std::move(vertex_value_lhs),
                                                   vertex_id_lhs);
    }

    if (!transposed_graph.has_vertex(vertex_id_rhs)) {
      auto vertex_id = transposed_graph.add_vertex(std::move(vertex_value_rhs),
                                                   vertex_id_rhs);
    }

    transposed_graph.add_edge(vertex_id_rhs, vertex_id_lhs,
                              std::move(edge_type));
  }

  return transposed_graph;
}

}  // namespace graaf
