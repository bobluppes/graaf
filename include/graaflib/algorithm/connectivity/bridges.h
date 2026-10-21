#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <vector>

namespace graaf::algorithm {

/**
 * @brief Finds the bridges of an undirected graph.
 *
 * A bridge (or cut edge) is an edge whose removal increases the number of
 * connected components of the graph.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The input graph.
 * @return The ids of all bridges, in ascending order. Each id holds the
 * smaller vertex id first. Empty if the graph has none.
 */
template <typename V, typename E>
[[nodiscard]] std::vector<edge_id_t> bridges(
    const graph<V, E, graph_type::UNDIRECTED>& graph);

}  // namespace graaf::algorithm

#include "bridges.tpp"
