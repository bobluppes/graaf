#pragma once

#include <graaflib/algorithm/coloring/greedy_graph_coloring.h>

#include <unordered_map>

namespace graaf::algorithm {

template <typename GRAPH>
std::unordered_map<vertex_id_t, int> greedy_graph_coloring(const GRAPH& graph) {
  // Initialize a map to store the coloring
  std::unordered_map<vertex_id_t, int> coloring;

  // Get the vertices from the graph
  const auto& vertices = graph.get_vertices();

  // Iterate through each vertex
  for (const auto& vertex_pair : vertices) {
    const vertex_id_t& current_vertex_id = vertex_pair.first;

    // Create a set of colors used by neighboring vertices
    std::unordered_set<int> neighbor_colors;

    // Iterate through neighboring vertices
    for (const auto& neighbor_id : graph.get_neighbors(current_vertex_id)) {
      auto neighbor_color_it = coloring.find(neighbor_id);
      if (neighbor_color_it != coloring.end()) {
        neighbor_colors.insert(neighbor_color_it->second);
      }
    }

    // Find the smallest available color for the current vertex
    int available_color = 1;
    while (neighbor_colors.count(available_color) > 0) {
      ++available_color;
    }

    // Assign the color to the current vertex
    coloring[current_vertex_id] = available_color;
  }

  return coloring;
}

}  // namespace graaf::algorithm
