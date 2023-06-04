#pragma once

#include <algorithm>

namespace graaf::properties {

template <typename V, typename E, graph_spec S>
std::size_t get_vertex_degree(const graaf::graph<V, E, S>& graph,
                              vertex_id_t vertex_id) {
  if constexpr (S == graph_spec::DIRECTED) {
    return get_vertex_outdegree(graph, vertex_id) +
           get_vertex_indegree(graph, vertex_id);
  }

  if constexpr (S == graph_spec::UNDIRECTED) {
    return get_vertex_outdegree(graph, vertex_id);
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
  using vertex_id_to_vertex_t = std::unordered_map<vertex_id_t, V>;

  if constexpr (S == graph_spec::DIRECTED) {
    return std::ranges::count_if(
        graph.get_vertices(),
        [&graph, vertex_id](const vertex_id_to_vertex_t::value_type& kv_pair) {
          const auto& [current_vertex_id, _]{kv_pair};
          return graph.get_neighbors(current_vertex_id).contains(vertex_id);
        });
  }

  if constexpr (S == graph_spec::UNDIRECTED) {
    return (graph.get_neighbors(vertex_id)).size();
  }

  // Should never reach this
  std::abort();
}

}  // namespace graaf::properties