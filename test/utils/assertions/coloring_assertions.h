#pragma once

#include <graaflib/types.h>

#include <unordered_map>

namespace graaf::utils::assertions {

// A coloring is proper iff no two vertices connected by an edge share the
// same color. Note that graph::get_neighbors() returns an unordered_set, so
// the exact colors assigned to individual vertices are not guaranteed to be
// stable across STL implementations/platforms - only this invariant is.
template <typename GRAPH>
bool is_proper_coloring(const GRAPH& graph,
                        const std::unordered_map<vertex_id_t, int>& coloring) {
  for (const auto& [edge_id, edge] : graph.get_edges()) {
    const auto [u, v]{edge_id};
    if (coloring.at(u) == coloring.at(v)) {
      return false;
    }
  }
  return true;
}

}  // namespace graaf::utils::assertions
