#pragma once
#include <graaflib/algorithm/connectivity/articulation_points.h>
#include <graaflib/algorithm/connectivity/low_link.h>

#include <vector>

namespace graaf::algorithm {

template <typename V, typename E>
std::vector<vertex_id_t> articulation_points(
    const graph<V, E, graph_type::UNDIRECTED>& graph) {
  return detail::find_cut_structure(graph).articulation_points;
}

}  // namespace graaf::algorithm
