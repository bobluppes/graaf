#pragma once
#include <graaflib/algorithm/coloring/welsh_powell.h>
#include <graaflib/algorithm/utils.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "welsh_powell.h"

namespace graaf::algorithm {

template <typename GRAPH>
std::unordered_map<vertex_id_t, int> welsh_powell_coloring(const GRAPH& graph) {
  using degree_vertex_pair = std::pair<int, vertex_id_t>;

  // graph::get_neighbors() only reports outgoing edges. For a directed graph,
  // two vertices sharing a common predecessor must still get different
  // colors, so we additionally need to take incoming edges into account.
  std::unordered_map<vertex_id_t, std::unordered_set<vertex_id_t>>
      predecessors{};
  if (graph.is_directed()) {
    predecessors = get_predecessors(graph);
  }

  // Step 1: Sort vertices by degree in descending order. The degree is the
  // number of outgoing edges plus, for a directed graph, the number of
  // incoming edges (from the predecessors map computed above).
  std::vector<degree_vertex_pair> degree_vertex_pairs;
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    int degree = static_cast<int>(graph.get_neighbors(vertex_id).size());
    if (const auto it{predecessors.find(vertex_id)}; it != predecessors.end()) {
      degree += static_cast<int>(it->second.size());
    }
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

    const auto collect_neighbor_color{[&](vertex_id_t neighbor_id) {
      if (const auto it{color_map.find(neighbor_id)}; it != color_map.end()) {
        neighbor_colors.insert(it->second);
      }
    }};

    for (const auto& neighbor : graph.get_neighbors(current_vertex)) {
      collect_neighbor_color(neighbor);
    }

    if (const auto it{predecessors.find(current_vertex)};
        it != predecessors.end()) {
      for (const auto& predecessor : it->second) {
        collect_neighbor_color(predecessor);
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
