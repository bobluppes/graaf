#pragma once
#include <optional>
#include <queue>
#include <sstream>
#include <vector>

#include "dijkstra_shortest_paths.h"

namespace graaf::algorithm {

template <typename V, typename E, graph_type T, typename WEIGHT_T>
[[nodiscard]] std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
dijkstra_shortest_paths(const graph<V, E, T>& graph,
                        vertex_id_t source_vertex) {
  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  using dijkstra_queue_t =
      std::priority_queue<weighted_path_item, std::vector<weighted_path_item>,
                          std::greater<>>;
  dijkstra_queue_t to_explore{};

  // Indexed directly by vertex_id_t rather than an unordered_map, grown
  // lazily as vertices are discovered. Tracks only (dist_from_start,
  // prev_id) per vertex during the search - each reachable vertex's full
  // path is reconstructed once at the end via backtracking, rather than
  // copied on every relaxation.
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

  set_info(source_vertex, {source_vertex, 0, source_vertex});
  to_explore.push(*vertex_info[source_vertex]);

  while (!to_explore.empty()) {
    auto current{to_explore.top()};
    to_explore.pop();

    if (current.dist_from_start > vertex_info[current.id]->dist_from_start) {
      continue;
    }

    for (const auto neighbor : graph.get_neighbors(current.id)) {
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

  std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>> shortest_paths;
  for (vertex_id_t id{0}; id < vertex_info.size(); ++id) {
    if (!vertex_info[id].has_value()) {
      continue;
    }

    graph_path<WEIGHT_T> path;
    path.total_weight = vertex_info[id]->dist_from_start;

    auto current{id};
    while (current != source_vertex) {
      path.vertices.push_front(current);
      current = vertex_info[current]->prev_id;
    }
    path.vertices.push_front(source_vertex);

    shortest_paths.emplace(id, std::move(path));
  }

  return shortest_paths;
}

}  // namespace graaf::algorithm
