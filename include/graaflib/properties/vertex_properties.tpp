#pragma once

namespace graaf::properties {

template <typename V, typename E, graph_spec S>
std::size_t get_vertex_degree(const graaf::graph<V, E, S>& graph,
                              vertex_id_t vertex_id) {
  if constexpr (S == graph_spec::DIRECTED) {
    return get_vertex_outdegree(graph, vertex_id) +
           get_vertex_indegree(graph, vertex_id);
  }

  if constexpr (S == graph_spec::UNDIRECTED) {
    return (graph.get_neighbors(vertex_id)).size();
  }

  // Should never reach this
  std::abort();
}

template <typename V, typename E, graph_spec S>
std::size_t get_vertex_outdegree(const graaf::graph<V, E, S>& graph,
                                 vertex_id_t vertex_id) {
  return (graph.get_neighbors(vertex_id)).size();
}

template <typename V, typename E, graph_spec S>
std::size_t get_vertex_indegree(const graaf::graph<V, E, S>& graph,
                                vertex_id_t vertex_id) {
  if constexpr (S == graph_spec::DIRECTED) {
    int indegree{0};
    for (const auto& current_vertex : graph.get_vertices()) {
      if (graph.get_neighbors(current_vertex.first).contains(vertex_id)) {
        indegree++;
      }
    }
    return indegree;
  }

  if constexpr (S == graph_spec::UNDIRECTED) {
    return (graph.get_neighbors(vertex_id)).size();
  }

  // Should never reach this
  std::abort();
}

}  // namespace graaf::properties