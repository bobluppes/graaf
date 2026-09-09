#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <unordered_map>

namespace graaf::algorithm {
/**
 * @brief Floyd-Warshall Algorithm
 *
 * This function computes the shortest paths between all pairs of vertices in a
 * given weighted graph. It works for graphs with negative weight edges as well,
 * but not for graphs with negative weight cycles. The function returns the
 * shortest distance between every pair of vertices, keyed by their vertex IDs.
 *
 * @tparam V The type of a graph vertex
 * @tparam E The type of a graph edge
 * @tparam T the graph type (DIRECTED or UNDIRECTED)
 * @tparam WEIGHT_T The weight type of an edge in the graph
 * @param graph The graph object
 * @return A map of maps where `result.at(from).at(to)` is the shortest
 * distance from vertex `from` to vertex `to`. If no path exists between two
 * vertices, there is no corresponding entry.
 */
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
[[nodiscard]] std::unordered_map<vertex_id_t,
                                  std::unordered_map<vertex_id_t, WEIGHT_T>>
floyd_warshall_shortest_paths(const graph<V, E, T>& graph);

};  // namespace graaf::algorithm

#include "floyd_warshall.tpp"