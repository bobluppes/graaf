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

  const auto enqueue_neighbors{[&graph, &to_explore](const vertex_id_t vertex) {
    std::ranges::for_each(graph.get_neighbors(vertex),
                          [&to_explore](const vertex_id_t neighbor) {
                            to_explore.push(neighbor);
                          });
  }};

  while (!to_explore.empty()) {
    const auto current{to_explore.front()};
    to_explore.pop();

    if (!seen_vertices.contains(current)) {
      callback(current);
      enqueue_neighbors(current);
      seen_vertices.insert(current);
    }
  }
}

template <typename V, typename E, graph_type T, typename CALLBACK_T>
void do_dfs(const graph<V, E, T>& graph,
            std::unordered_set<vertex_id_t>& seen_vertices, vertex_id_t current,
            const CALLBACK_T& callback) {
  callback(current);
  seen_vertices.insert(current);

  for (auto neighbor_vertex : graph.get_neighbors(current)) {
    if (!seen_vertices.contains(neighbor_vertex)) {
      do_dfs(graph, seen_vertices, neighbor_vertex, callback);
    }
  }
}

}  // namespace detail

template <typename V, typename E, graph_type T, typename CALLBACK_T>
  requires std::invocable<const CALLBACK_T&, vertex_id_t>
void breadth_first_traverse(const graph<V, E, T>& graph,
                            vertex_id_t start_vertex,
                            const CALLBACK_T& callback) {
  std::unordered_set<vertex_id_t> seen_vertices{};
  return detail::do_bfs(graph, seen_vertices, start_vertex, callback);
}

template <typename V, typename E, graph_type T, typename CALLBACK_T>
  requires std::invocable<const CALLBACK_T&, vertex_id_t>
void depth_first_traverse(const graph<V, E, T>& graph, vertex_id_t start_vertex,
                          const CALLBACK_T& callback) {
  std::unordered_set<vertex_id_t> seen_vertices{};
  return detail::do_dfs(graph, seen_vertices, start_vertex, callback);
}

}  // namespace graaf::algorithm