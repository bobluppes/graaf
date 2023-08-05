#pragma once

#include <algorithm>
#include <optional>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace graaf::algorithm {

namespace detail {

template <typename WEIGHT_T>
struct path_vertex {
  vertex_id_t id;
  WEIGHT_T dist_from_start;
  vertex_id_t prev_id;

  [[nodiscard]] bool operator>(const path_vertex<WEIGHT_T>& other) {
    return dist_from_start > other.dist_from_start;
  }
};

template <typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> reconstruct_path(
    vertex_id_t start_vertex, vertex_id_t end_vertex,
    std::unordered_map<vertex_id_t, path_vertex<WEIGHT_T>>& vertex_info) {
  if (!vertex_info.contains(end_vertex)) {
    return std::nullopt;
  }

  graph_path<WEIGHT_T> path;
  auto current = end_vertex;

  while (current != start_vertex) {
    path.vertices.push_front(current);
    current = vertex_info[current].prev_id;
  }

  path.vertices.push_front(start_vertex);
  path.total_weight = vertex_info[end_vertex].dist_from_start;
  return path;
}

}  // namespace detail

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> bfs_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  std::unordered_map<vertex_id_t, detail::path_vertex<WEIGHT_T>> vertex_info;
  std::queue<vertex_id_t> to_explore{};

  vertex_info[start_vertex] = {start_vertex, 1, start_vertex};
  to_explore.push(start_vertex);

  while (!to_explore.empty()) {
    auto current{to_explore.front()};
    to_explore.pop();

    if (current == end_vertex) {
      break;
    }

    for (const auto& neighbor : graph.get_neighbors(current)) {
      if (!vertex_info.contains(neighbor)) {
        vertex_info[neighbor] = {
            neighbor, vertex_info[current].dist_from_start + 1, current};
        to_explore.push(neighbor);
      }
    }
  }

  return reconstruct_path(start_vertex, end_vertex, vertex_info);
}

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> dijkstra_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  std::unordered_map<vertex_id_t, detail::path_vertex<WEIGHT_T>> vertex_info;

  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  std::priority_queue<weighted_path_item, std::vector<weighted_path_item>,
                      std::greater<>>
      to_explore{};

  vertex_info[start_vertex] = {start_vertex, 0, start_vertex};
  to_explore.push(vertex_info[start_vertex]);

  while (!to_explore.empty()) {
    auto current{to_explore.top()};
    to_explore.pop();

    if (current.id == end_vertex) {
      break;
    }

    for (const auto& neighbor : graph.get_neighbors(current.id)) {
      WEIGHT_T distance = current.dist_from_start +
                          get_weight(graph.get_edge(current.id, neighbor));

      if (!vertex_info.contains(neighbor) ||
          distance < vertex_info[neighbor].dist_from_start) {
        vertex_info[neighbor] = {neighbor, distance, current.id};
        to_explore.push(vertex_info[neighbor]);
      }
    }
  }

  return reconstruct_path(start_vertex, end_vertex, vertex_info);
}

}  // namespace graaf::algorithm