#pragma once

#include <graaflib/algorithm/coloring/greedy_graph_coloring.h>

#include <unordered_map>

namespace graaf::algorithm {

template <typename GRAPH>
std::unordered_map<vertex_id_t, int> greedy_graph_coloring(const GRAPH& graph) {
  // Initialize a map to store the coloring
  std::unordered_map<vertex_id_t, int> coloring{};

  // Get the vertices from the graph
  const auto& vertices = graph.get_vertices();

  // Iterate through each vertex
  for (const auto& [current_vertex_id, _] : vertices) {
    // Iterate through neighboring vertices
    // Find the smallest available color for the current vertex
    int available_color{0};
    for (const auto neighbor_id : graph.get_neighbors(current_vertex_id)) {
      if (coloring.contains(neighbor_id)) {
        const auto neighbor_color{coloring.at(neighbor_id)};
        if (neighbor_color >= available_color) {
          available_color = neighbor_color + 1;
        }
      }
    }

    // Assign the color to the current vertex
    coloring[current_vertex_id] = available_color;
  }

  return coloring;
}

}  // namespace graaf::algorithm
