#pragma once

#include <queue>
#include <sstream>

namespace graaf::algorithm {

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
        std::ostringstream error_msg;
        error_msg << "Negative edge weight [" << edge_weight
                  << "] between vertices [" << current.id << "] -> ["
                  << neighbor << "].";
        throw std::invalid_argument{error_msg.str()};
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