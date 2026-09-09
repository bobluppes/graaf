#pragma once
#include <graaflib/algorithm/coloring/welsh_powell.h>
#include <graaflib/properties/vertex_properties.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "welsh_powell.h"

namespace graaf::algorithm {

template <typename GRAPH>
std::unordered_map<vertex_id_t, int> welsh_powell_coloring(const GRAPH& graph) {
  using degree_vertex_pair = std::pair<int, vertex_id_t>;

  // Step 1: Sort vertices by degree in descending order
  std::vector<degree_vertex_pair> degree_vertex_pairs;
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    int degree = properties::vertex_degree(graph, vertex_id);
    degree_vertex_pairs.emplace_back(degree, vertex_id);
  }

  std::sort(degree_vertex_pairs.rbegin(), degree_vertex_pairs.rend());

  // Step 2: Assign colors to vertices
  std::unordered_map<vertex_id_t, int> color_map;

  for (const auto [_, current_vertex] : degree_vertex_pairs) {
    // Collect the colors already used by neighbors of the current vertex.
    // Note that this needs to be gathered up front and independent of
    // iteration order, since graph::get_neighbors() returns an
    // unordered_set whose iteration order is unspecified.
    std::unordered_set<int> neighbor_colors;
    for (const auto& neighbor : graph.get_neighbors(current_vertex)) {
      if (const auto it{color_map.find(neighbor)}; it != color_map.end()) {
        neighbor_colors.insert(it->second);
      }
    }

    // Assign the smallest color not used by any neighbor to the current
    // vertex.
    int color = 0;
    while (neighbor_colors.contains(color)) {
      color++;
    }

    color_map[current_vertex] = color;
  }

  return color_map;
}

}  // namespace graaf::algorithm
