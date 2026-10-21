#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <vector>

namespace graaf::algorithm {

/**
 * @brief Finds the articulation points of an undirected graph.
 *
 * An articulation point (or cut vertex) is a vertex whose removal, together
 * with its incident edges, increases the number of connected components of
 * the graph.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The input graph.
 * @return The ids of all articulation points, in ascending order. Empty if the
 * graph has none.
 */
template <typename V, typename E>
[[nodiscard]] std::vector<vertex_id_t> articulation_points(
    const graph<V, E, graph_type::UNDIRECTED>& graph);

}  // namespace graaf::algorithm

#include "articulation_points.tpp"
