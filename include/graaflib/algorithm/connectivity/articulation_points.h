#pragma once

#include <graaflib/algorithm/connectivity/common.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

/**
 * Computes the articulation points (cut vertices) of an undirected graph.
 *
 * An articulation point is a vertex whose removal increases the number of
 * connected components of the graph.
 *
 * @tparam V Vertex type.
 * @tparam E Edge type.
 * @param graph The undirected graph to analyse.
 * @return A list of vertex IDs that are articulation points.
 */
template <typename V, typename E>
[[nodiscard]] articulation_points_t articulation_points(
    const graph<V, E, graph_type::UNDIRECTED>& graph);

}  // namespace graaf::algorithm

#include "articulation_points.tpp"