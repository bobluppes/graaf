#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <vector>

namespace graaf::algorithm {
/**
 * @brief Floyd-Warshall Algorithm
 *
 * This function computes the shortest paths between all pairs of vertices in a
 * given weighted graph. It works for graphs with negative weight edges as well,
 * but not for graphs with negative weight cycles. The function returns an
 * adjacency matrix representing the shortest distances.
 *
 * Rows/columns are indexed by the ascending order of the graph's (live)
 * vertex IDs. If no vertex has ever been removed from the graph, vertex IDs
 * are contiguous starting at 0, so index i corresponds exactly to vertex i.
 * If vertices have been removed, index i corresponds to the i-th smallest
 * remaining vertex ID rather than vertex ID i itself.
 *
 * @tparam V The type of a graph vertex
 * @tparam E The type of a graph edge
 * @tparam T the graph type (DIRECTED or UNDIRECTED)
 * @tparam WEIGHT_T The weight type of an edge in the graph
 * @param graph The graph object
 * @return A 2D vector where element at [i][j] is the shortest distance from
 * the vertex at index i to the vertex at index j (see above for how indices
 * map to vertex IDs).
 */
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::vector<std::vector<WEIGHT_T>> floyd_warshall_shortest_paths(
    const graph<V, E, T>& graph);

};  // namespace graaf::algorithm

#include "floyd_warshall.tpp"