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

  // TODO: align/merge with implementation of do_bfs in graph_traversal.tpp
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

  const auto reconstruct_path = [&start_vertex, &end_vertex, &prev_vertex]() {
    GraphPath<int> path;
    auto current{end_vertex};

    while (current != start_vertex) {
      path.vertices.push_front(current);
      current = prev_vertex[current];
    }

    path.vertices.push_front(start_vertex);
    path.total_weight = path.vertices.size();

    return path;
  };

  if (seen_vertices.contains(end_vertex)) {
    return reconstruct_path();
  } else {
    return std::nullopt;
  }
}

template <typename V, typename E, graph_spec S>
std::optional<GraphPath<E>> get_weighted_shortest_path(
    const graph<V, E, S>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  using weight_t = typename graph<V, E, S>::edge_t;

  struct DijkstraVertex {
    vertex_id_t id;
    weight_t distance;
    vertex_id_t previous;
  };

  std::unordered_set<vertex_id_t> seen_vertices{};
  std::unordered_map<vertex_id_t, DijkstraVertex> vertex_info;
  std::priority_queue<
      DijkstraVertex, std::vector<DijkstraVertex>,
      std::function<bool(const DijkstraVertex&, const DijkstraVertex&)>>
      to_explore([](const DijkstraVertex& v1, const DijkstraVertex& v2) {
        return v1.distance > v2.distance;
      });

  vertex_info[start_vertex] = {start_vertex, 0, start_vertex};
  to_explore.push(vertex_info[start_vertex]);

  while (!to_explore.empty()) {
    auto current{to_explore.top()};
    to_explore.pop();

    if (seen_vertices.contains(current.id)) {
      continue;
    }

    seen_vertices.insert(current.id);

    if (current.id == end_vertex) {
      break;
    }

    for (const auto& neighbor : graph.get_neighbors(current.id)) {
      weight_t distance =
          current.distance + graph.get_edge(current.id, neighbor)->get_weight();

      if (!vertex_info.contains(neighbor) ||
          distance < vertex_info[neighbor].distance) {
        vertex_info[neighbor] = {neighbor, distance, current.id};
        to_explore.push(vertex_info[neighbor]);
      }
    }
  }

  const auto reconstruct_path = [&start_vertex, &end_vertex, &vertex_info]() {
    GraphPath<weight_t> path;
    auto current = end_vertex;

    while (current != start_vertex) {
      path.vertices.push_back(current);
      current = vertex_info[current].previous;
    }

    path.vertices.push_back(start_vertex);
    path.total_weight = vertex_info[end_vertex].distance;

    std::reverse(path.vertices.begin(), path.vertices.end());

    return path;
  };

  if (seen_vertices.contains(end_vertex)) {
    return reconstruct_path();
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
    return detail::get_weighted_shortest_path(graph, start_vertex, end_vertex);
  }
}

}  // namespace graaf::algorithm