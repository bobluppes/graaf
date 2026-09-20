#pragma once
#include <graaflib/algorithm/coloring/greedy_graph_coloring.h>
#include <graaflib/algorithm/utils.h>

#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "greedy_graph_coloring.h"

namespace graaf::algorithm {

template <typename GRAPH>
std::unordered_map<vertex_id_t, int> greedy_graph_coloring(const GRAPH& graph) {
  // graph::get_neighbors() only reports outgoing edges. On a directed graph,
  // a vertex must also differ in color from each of its predecessors (the
  // vertices with an edge into it), not just its successors, so we
  // additionally need to take incoming edges into account.
  std::unordered_map<vertex_id_t, std::unordered_set<vertex_id_t>>
      predecessors{};
  if (graph.is_directed()) {
    predecessors = get_predecessors(graph);
  }

  // Indexed directly by vertex_id_t rather than an unordered_map for the
  // per-edge lookups in consider_neighbor() below - the public
  // unordered_map<vertex_id_t, int> contract is only built once, at the end.
  std::vector<std::optional<int>> coloring{};
  const auto get_color{[&](vertex_id_t id) -> std::optional<int> {
    return id < coloring.size() ? coloring[id] : std::nullopt;
  }};
  const auto set_color{[&](vertex_id_t id, int color) {
    if (id >= coloring.size()) {
      coloring.resize(id + 1);
    }
    coloring[id] = color;
  }};

  // Iterate through each vertex
  for (const auto& [current_vertex_id, _] : graph.get_vertices()) {
    // Iterate through neighboring vertices
    // Find the smallest available color for the current vertex
    int available_color{0};

    const auto consider_neighbor{[&](vertex_id_t neighbor_id) {
      if (const auto color{get_color(neighbor_id)}; color.has_value()) {
        if (*color >= available_color) {
          available_color = *color + 1;
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
    set_color(current_vertex_id, available_color);
  }

  std::unordered_map<vertex_id_t, int> coloring_result{};
  for (vertex_id_t id{0}; id < coloring.size(); ++id) {
    if (coloring[id].has_value()) {
      coloring_result.emplace(id, *coloring[id]);
    }
  }
  return coloring_result;
}

}  // namespace graaf::algorithm
