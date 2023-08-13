#pragma once

#include <graaflib/algorithm/graph_traversal.h>

#include <algorithm>
#include <format>
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
  std::unordered_map<vertex_id_t, detail::path_vertex<WEIGHT_T>> vertex_info{
      {start_vertex, {start_vertex, 0, start_vertex}}};

  const auto callback{[&vertex_info](const edge_id_t& edge) {
    const auto [source, target]{edge};

    if (!vertex_info.contains(target)) {
      vertex_info[target] = {target, vertex_info[source].dist_from_start + 1,
                             source};
    }
  }};

  // We keep searching until we have reached the target vertex
  const auto search_termination_strategy{
      [end_vertex](const vertex_id_t vertex_id) {
        return vertex_id == end_vertex;
      }};

  breadth_first_traverse(graph, start_vertex, callback,
                         search_termination_strategy);

  return reconstruct_path(start_vertex, end_vertex, vertex_info);
}

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> dijkstra_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  using dijkstra_queue_t =
      std::priority_queue<weighted_path_item, std::vector<weighted_path_item>,
                          std::greater<>>;
  dijkstra_queue_t to_explore{};
  std::unordered_map<vertex_id_t, weighted_path_item> vertex_info;

  vertex_info[start_vertex] = {start_vertex, 0, start_vertex};
  to_explore.push(vertex_info[start_vertex]);

  while (!to_explore.empty()) {
    auto current{to_explore.top()};
    to_explore.pop();

    if (current.id == end_vertex) {
      break;
    }

    for (const auto& neighbor : graph.get_neighbors(current.id)) {
      WEIGHT_T edge_weight = get_weight(graph.get_edge(current.id, neighbor));

      if (edge_weight < 0) {
        throw std::invalid_argument{std::format(
            "Negative edge weight [{}] between vertices [{}] -> [{}].",
            edge_weight, current.id, neighbor)};
      }

      WEIGHT_T distance = current.dist_from_start + edge_weight;

      if (!vertex_info.contains(neighbor) ||
          distance < vertex_info[neighbor].dist_from_start) {
        vertex_info[neighbor] = {neighbor, distance, current.id};
        to_explore.push(vertex_info[neighbor]);
      }
    }
  }

  return reconstruct_path(start_vertex, end_vertex, vertex_info);
}

template <typename V, typename E, graph_type T, typename WEIGHT_T>
[[nodiscard]] std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
dijkstra_shortest_paths(const graph<V, E, T>& graph,
                        vertex_id_t source_vertex) {
  std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>> shortest_paths;

  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  using dijkstra_queue_t =
      std::priority_queue<weighted_path_item, std::vector<weighted_path_item>,
                          std::greater<>>;
  dijkstra_queue_t to_explore{};

  shortest_paths[source_vertex].total_weight = 0;
  shortest_paths[source_vertex].vertices.push_back(source_vertex);
  to_explore.push(weighted_path_item{source_vertex, 0});

  while (!to_explore.empty()) {
    auto current{to_explore.top()};
    to_explore.pop();

    if (shortest_paths.contains(current.id) &&
        current.dist_from_start > shortest_paths[current.id].total_weight) {
      continue;
    }

    for (const auto neighbor : graph.get_neighbors(current.id)) {
      WEIGHT_T edge_weight = get_weight(graph.get_edge(current.id, neighbor));

      if (edge_weight < 0) {
        throw std::invalid_argument{std::format(
            "Negative edge weight [{}] between vertices [{}] -> [{}].",
            edge_weight, current.id, neighbor)};
      }

      WEIGHT_T distance = current.dist_from_start + edge_weight;

      if (!shortest_paths.contains(neighbor) ||
          distance < shortest_paths[neighbor].total_weight) {
        shortest_paths[neighbor].total_weight = distance;
        shortest_paths[neighbor].vertices = shortest_paths[current.id].vertices;
        shortest_paths[neighbor].vertices.push_back(neighbor);
        to_explore.push(weighted_path_item{neighbor, distance});
      }
    }
  }

  return shortest_paths;
}

}  // namespace graaf::algorithm