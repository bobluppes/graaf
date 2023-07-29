#pragma once

#include <algorithm>
#include <optional>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace graaf::algorithm {

namespace detail {

template <typename E>
struct PathVertex {
  vertex_id_t id;
  E dist_from_start;
  vertex_id_t prev_id;
};

template <typename WEIGHT_T>
std::optional<GraphPath<WEIGHT_T>> reconstruct_path(
    vertex_id_t start_vertex, vertex_id_t end_vertex,
    std::unordered_map<vertex_id_t, PathVertex<WEIGHT_T>>& vertex_info) {
  if (!vertex_info.contains(end_vertex)) {
    return std::nullopt;
  }

  GraphPath<WEIGHT_T> path;
  auto current = end_vertex;

  while (current != start_vertex) {
    path.vertices.push_front(current);
    current = vertex_info[current].prev_id;
  }

  path.vertices.push_front(start_vertex);
  path.total_weight = vertex_info[end_vertex].dist_from_start;
  return path;
}

template <typename V, typename E, graph_spec S, typename WEIGHT_T>
std::optional<GraphPath<WEIGHT_T>> get_unweighted_shortest_path(
    const graph<V, E, S>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  std::unordered_map<vertex_id_t, PathVertex<WEIGHT_T>> vertex_info;
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

template <typename V, typename E, graph_spec S, typename WEIGHT_T>
std::optional<GraphPath<WEIGHT_T>> get_weighted_shortest_path(
    const graph<V, E, S>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  std::unordered_map<vertex_id_t, PathVertex<WEIGHT_T>> vertex_info;
  std::priority_queue<PathVertex<WEIGHT_T>, std::vector<PathVertex<WEIGHT_T>>,
                      std::function<bool(const PathVertex<WEIGHT_T>&,
                                         const PathVertex<WEIGHT_T>&)>>
      to_explore(
          [](const PathVertex<WEIGHT_T>& v1, const PathVertex<WEIGHT_T>& v2) {
            return v1.dist_from_start > v2.dist_from_start;
          });

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
                          graph.get_edge(current.id, neighbor)->get_weight();

      if (!vertex_info.contains(neighbor) ||
          distance < vertex_info[neighbor].dist_from_start) {
        vertex_info[neighbor] = {neighbor, distance, current.id};
        to_explore.push(vertex_info[neighbor]);
      }
    }
  }

  return reconstruct_path(start_vertex, end_vertex, vertex_info);
}

}  // namespace detail

template <edge_strategy EDGE_STRATEGY, typename V, typename E, graph_spec S,
          typename WEIGHT_T>
std::optional<GraphPath<WEIGHT_T>> get_shortest_path(
    const graph<V, E, S>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  using enum edge_strategy;
  if constexpr (EDGE_STRATEGY == UNWEIGHTED) {
    return detail::get_unweighted_shortest_path<V, E, S, WEIGHT_T>(
        graph, start_vertex, end_vertex);
  }

  if constexpr (EDGE_STRATEGY == WEIGHTED) {
    return detail::get_weighted_shortest_path<V, E, S, WEIGHT_T>(
        graph, start_vertex, end_vertex);
  }
}

}  // namespace graaf::algorithm