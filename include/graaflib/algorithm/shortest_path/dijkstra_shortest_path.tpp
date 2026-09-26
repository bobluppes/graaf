#pragma once
#include <optional>
#include <queue>
#include <sstream>
#include <vector>

#include "dijkstra_shortest_path.h"

namespace graaf::algorithm {

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> dijkstra_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  using dijkstra_queue_t =
      std::priority_queue<weighted_path_item, std::vector<weighted_path_item>,
                          std::greater<>>;
  dijkstra_queue_t to_explore{};

  // Indexed directly by vertex_id_t, grown lazily as vertices are
  // discovered during the search. Path reconstruction is inlined below
  // rather than going through reconstruct_path(), since backtracking is
  // only a few lines.
  std::vector<std::optional<weighted_path_item>> vertex_info{};
  const auto has_info{[&](vertex_id_t id) {
    return id < vertex_info.size() && vertex_info[id].has_value();
  }};
  const auto set_info{[&](vertex_id_t id, weighted_path_item item) {
    if (id >= vertex_info.size()) {
      vertex_info.resize(id + 1);
    }
    vertex_info[id] = item;
  }};

  set_info(start_vertex, {start_vertex, 0, start_vertex});
  to_explore.push(*vertex_info[start_vertex]);

  while (!to_explore.empty()) {
    auto current{to_explore.top()};
    to_explore.pop();

    if (current.id == end_vertex) {
      break;
    }

    for (const auto& neighbor : graph.get_neighbors(current.id)) {
      WEIGHT_T edge_weight = get_weight(graph.get_edge(current.id, neighbor));

      if (edge_weight < 0) {
        std::ostringstream error_msg;
        error_msg << "Negative edge weight [" << edge_weight
                  << "] between vertices [" << current.id << "] -> ["
                  << neighbor << "].";
        throw std::invalid_argument{error_msg.str()};
      }

      WEIGHT_T distance = current.dist_from_start + edge_weight;

      if (!has_info(neighbor) ||
          distance < vertex_info[neighbor]->dist_from_start) {
        set_info(neighbor, {neighbor, distance, current.id});
        to_explore.push(*vertex_info[neighbor]);
      }
    }
  }

  if (!has_info(end_vertex)) {
    return std::nullopt;
  }

  graph_path<WEIGHT_T> path;
  auto current{end_vertex};
  while (current != start_vertex) {
    path.vertices.push_front(current);
    current = vertex_info[current]->prev_id;
  }
  path.vertices.push_front(start_vertex);
  path.total_weight = vertex_info[end_vertex]->dist_from_start;
  return path;
}

}  // namespace graaf::algorithm
