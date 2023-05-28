#pragma once

#include <algorithm>
#include <optional>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace graaf::algorithm {

namespace detail {

template <typename V, typename E, graph_spec S>
std::optional<GraphPath<int>> get_unweighted_shortest_path(
    const graph<V, E, S>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  std::unordered_set<vertex_id_t> seen_vertices{};
  std::unordered_map<vertex_id_t, vertex_id_t> prev_vertex{};
  std::queue<vertex_id_t> to_explore{};

  to_explore.push(start_vertex);
  seen_vertices.insert(start_vertex);

  while (!to_explore.empty()) {
    auto current{to_explore.front()};
    to_explore.pop();

    if (current == end_vertex) {
      break;
    }

    for (const auto& neighbor : graph.get_neighbors(current)) {
      if (!seen_vertices.contains(neighbor)) {
        seen_vertices.insert(neighbor);
        prev_vertex[neighbor] = current;
        to_explore.push(neighbor);
      }
    }
  }

  if (seen_vertices.contains(end_vertex)) {
    GraphPath<int> path;
    auto current{end_vertex};

    while (current != start_vertex) {
      path.vertices.push_front(current);
      current = prev_vertex[current];
    }

    path.vertices.push_front(start_vertex);
    path.total_weight = path.vertices.size();

    return path;

  } else {
    return std::nullopt;
  }
}

}  // namespace detail

template <edge_strategy EDGE_STRATEGY, typename V, typename E, graph_spec S>
std::optional<GraphPath<E>> get_shortest_path(const graph<V, E, S>& graph,
                                              vertex_id_t start_vertex,
                                              vertex_id_t end_vertex) {
  using enum edge_strategy;
  if constexpr (EDGE_STRATEGY == UNWEIGHTED) {
    return detail::get_unweighted_shortest_path(graph, start_vertex,
                                                end_vertex);
  }

  if constexpr (EDGE_STRATEGY == WEIGHTED) {
    // TODO: Implement A* or Dijkstra
    throw std::logic_error(
        "Shortest path for weighted graphs not yet implemented.");
  }
}

}  // namespace graaf::algorithm