#pragma once

#include <graaflib/types.h>

#include <cstddef>
#include <unordered_map>
#include <vector>

namespace graaf::utils::assertions {

// Kahn's and DFS's topological sort pick their next vertex from an
// unordered container, so a graph usually admits several valid orderings.
// Rather than enumerating them all, this asserts the two properties that
// define a topological order: the result contains every vertex exactly
// once, and every edge points forward.
template <typename graph_t>
[[nodiscard]] bool is_topological_order(
    const graph_t& graph, const std::vector<vertex_id_t>& sorted_vertices) {
  if (sorted_vertices.size() != graph.vertex_count()) {
    return false;
  }

  std::unordered_map<vertex_id_t, std::size_t> position{};
  for (std::size_t index{0}; index < sorted_vertices.size(); ++index) {
    const auto [_,
                inserted]{position.try_emplace(sorted_vertices[index], index)};
    if (!inserted) {
      // Duplicate vertex in the result
      return false;
    }
  }

  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    if (!position.contains(vertex_id)) {
      return false;
    }

    for (const auto& neighbor : graph.get_neighbors(vertex_id)) {
      if (position.at(vertex_id) >= position.at(neighbor)) {
        return false;
      }
    }
  }

  return true;
}

}  // namespace graaf::utils::assertions
