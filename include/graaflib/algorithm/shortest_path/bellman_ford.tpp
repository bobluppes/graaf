#pragma once

namespace graaf::algorithm {

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
bellman_ford_shortest_paths(const graph<V, E, T>& graph,
                            vertex_id_t start_vertex) {
  std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>> shortest_paths;

  const auto found_shorter_path{
      [&shortest_paths](edge_id_t edge_id, const E& edge) {
        const auto weight = get_weight(edge);
        const auto [u, v]{edge_id};
        return shortest_paths[u].total_weight !=
                   std::numeric_limits<WEIGHT_T>::max() &&
               shortest_paths[u].total_weight + weight <
                   shortest_paths[v].total_weight;
      }};

  // Initialize the shortest path distances from the starting vertex to
  // "infinity" for all vertices
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    shortest_paths[vertex_id] = {{vertex_id},
                                 std::numeric_limits<WEIGHT_T>::max()};
  }

  // Set the distance from the starting vertex to itself to 0
  shortest_paths[start_vertex] = {{start_vertex}, 0};

  // Relax edges for |V| - 1 iterations
  for (std::size_t i = 1; i < graph.vertex_count(); ++i) {
    for (const auto& [edge_id, edge] : graph.get_edges()) {
      const auto [u, v]{edge_id};
      WEIGHT_T weight = get_weight(edge);

      if (found_shorter_path(edge_id, edge)) {
        // Update the shortest path to vertex v
        shortest_paths[v] = {
            {shortest_paths[u].vertices},
            shortest_paths[u].total_weight + weight,
        };
        shortest_paths[v].vertices.push_back(v);
      }
    }
  }
  // Negative cycle detection by doing an additional pass in the graph
  for (const auto& [edge_id, edge] : graph.get_edges()) {
    const auto [u, v]{edge_id};
    WEIGHT_T weight = get_weight(edge);
    if (found_shorter_path(edge_id, edge)) {
      throw std::invalid_argument{"Negative cycle detected in the graph."};
    }
  }
  return shortest_paths;
}

}  // namespace graaf::algorithm