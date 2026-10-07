#pragma once

#include <graaflib/algorithm/connectivity/common.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

/**
 * Computes the bridges (cut edges) of an undirected graph.
 *
 * A bridge is an edge whose removal increases the number of connected
 * components of the graph.
 *
 * @tparam V Vertex type.
 * @tparam E Edge type.
 * @param graph The undirected graph to analyse.
 * @return A list of edges that are bridges.
 */
template <typename V, typename E>
[[nodiscard]] bridges_t bridges(
    const graph<V, E, graph_type::UNDIRECTED>& graph);

}  // namespace graaf::algorithm

#include "bridges.tpp"