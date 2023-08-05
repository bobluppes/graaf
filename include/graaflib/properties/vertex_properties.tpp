#pragma once

#include <algorithm>

namespace graaf::properties {

template <typename V, typename E, graph_type T>
std::size_t vertex_degree(const graaf::graph<V, E, T>& graph,
                          vertex_id_t vertex_id) {
  if constexpr (T == graph_type::DIRECTED) {
    return vertex_outdegree(graph, vertex_id) +
           vertex_indegree(graph, vertex_id);
  }

  if constexpr (T == graph_type::UNDIRECTED) {
    return vertex_outdegree(graph, vertex_id);
  }

  // Should never reach this
  std::abort();
}

template <typename V, typename E, graph_type T>
std::size_t vertex_outdegree(const graaf::graph<V, E, T>& graph,
                             vertex_id_t vertex_id) {
  return (graph.get_neighbors(vertex_id)).size();
}

template <typename V, typename E, graph_type T>
std::size_t vertex_indegree(const graaf::graph<V, E, T>& graph,
                            vertex_id_t vertex_id) {
  using vertex_id_to_vertex_t = std::unordered_map<vertex_id_t, V>;

  if constexpr (T == graph_type::DIRECTED) {
    return std::ranges::count_if(
        graph.get_vertices(),
        [&graph,
         vertex_id](const typename vertex_id_to_vertex_t::value_type& kv_pair) {
          const auto& [current_vertex_id, _]{kv_pair};
          return graph.get_neighbors(current_vertex_id).contains(vertex_id);
        });
  }

  if constexpr (T == graph_type::UNDIRECTED) {
    // For an undirected graph, the indegree of a vertex is equal to the
    // outdegree
    return vertex_outdegree(graph, vertex_id);
  }

  // Should never reach this
  std::abort();
}

}  // namespace graaf::properties