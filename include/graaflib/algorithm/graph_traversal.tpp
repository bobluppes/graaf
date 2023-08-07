#pragma once

#include <algorithm>
#include <queue>
#include <unordered_set>

namespace graaf::algorithm {

namespace detail {

template <typename V, typename E, graph_type T, typename CALLBACK_T>
void do_bfs(const graph<V, E, T>& graph,
            std::unordered_set<vertex_id_t>& seen_vertices,
            vertex_id_t start_vertex, const CALLBACK_T& callback) {
  std::queue<vertex_id_t> to_explore{};

  to_explore.push(start_vertex);

  while (!to_explore.empty()) {
    const auto current{to_explore.front()};
    to_explore.pop();

    seen_vertices.insert(current);
    for (const auto neighbor_vertex : graph.get_neighbors(current)) {
      if (!seen_vertices.contains(neighbor_vertex)) {
        callback(edge_id_t{current, neighbor_vertex});
        to_explore.push(neighbor_vertex);
      }
    }
  }
}

template <typename V, typename E, graph_type T, typename CALLBACK_T>
void do_dfs(const graph<V, E, T>& graph,
            std::unordered_set<vertex_id_t>& seen_vertices, vertex_id_t current,
            const CALLBACK_T& callback) {
  seen_vertices.insert(current);

  for (auto neighbor_vertex : graph.get_neighbors(current)) {
    if (!seen_vertices.contains(neighbor_vertex)) {
      callback(edge_id_t{current, neighbor_vertex});
      do_dfs(graph, seen_vertices, neighbor_vertex, callback);
    }
  }
}

}  // namespace detail

template <typename V, typename E, graph_type T, typename CALLBACK_T>
  requires std::invocable<CALLBACK_T&, edge_id_t&>
void breadth_first_traverse(const graph<V, E, T>& graph,
                            vertex_id_t start_vertex,
                            const CALLBACK_T& callback) {
  std::unordered_set<vertex_id_t> seen_vertices{};
  return detail::do_bfs(graph, seen_vertices, start_vertex, callback);
}

template <typename V, typename E, graph_type T, typename CALLBACK_T>
  requires std::invocable<CALLBACK_T&, edge_id_t&>
void depth_first_traverse(const graph<V, E, T>& graph, vertex_id_t start_vertex,
                          const CALLBACK_T& callback) {
  std::unordered_set<vertex_id_t> seen_vertices{};
  return detail::do_dfs(graph, seen_vertices, start_vertex, callback);
}

}  // namespace graaf::algorithm