#pragma once
#include <graaflib/algorithm/coloring/greedy_graph_coloring.h>
#include <graaflib/algorithm/utils.h>

#include <unordered_map>
#include <unordered_set>

#include "greedy_graph_coloring.h"

namespace graaf::algorithm {

template <typename GRAPH>
std::unordered_map<vertex_id_t, int> greedy_graph_coloring(const GRAPH& graph) {
  // Initialize a map to store the coloring
  std::unordered_map<vertex_id_t, int> coloring{};

  // Get the vertices from the graph
  const auto& vertices = graph.get_vertices();

  // graph::get_neighbors() only reports outgoing edges. For a directed graph,
  // two vertices sharing a common predecessor must still get different
  // colors, so we additionally need to take incoming edges into account.
  std::unordered_map<vertex_id_t, std::unordered_set<vertex_id_t>>
      predecessors{};
  if (graph.is_directed()) {
    predecessors = get_predecessors(graph);
  }

  // Iterate through each vertex
  for (const auto& [current_vertex_id, _] : vertices) {
    // Iterate through neighboring vertices
    // Find the smallest available color for the current vertex
    int available_color{0};

    const auto consider_neighbor{[&](vertex_id_t neighbor_id) {
      if (const auto it{coloring.find(neighbor_id)}; it != coloring.end()) {
        if (it->second >= available_color) {
          available_color = it->second + 1;
        }
      }
    }};

    for (const auto neighbor_id : graph.get_neighbors(current_vertex_id)) {
      consider_neighbor(neighbor_id);
    }

    if (const auto it{predecessors.find(current_vertex_id)};
        it != predecessors.end()) {
      for (const auto predecessor_id : it->second) {
        consider_neighbor(predecessor_id);
      }
    }

    // Assign the color to the current vertex
    coloring[current_vertex_id] = available_color;
  }

  return coloring;
}

}  // namespace graaf::algorithm
