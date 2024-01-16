#pragma once

#include <queue>
#include <sstream>

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
        std::ostringstream error_msg;
        error_msg << "Negative edge weight [" << edge_weight
                  << "] between vertices [" << current.id << "] -> ["
                  << neighbor << "].";
        throw std::invalid_argument{error_msg.str()};
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

}  // namespace graaf::algorithm