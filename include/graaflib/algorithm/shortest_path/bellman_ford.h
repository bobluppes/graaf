#pragma once

#include <graaflib/algorithm/shortest_path/common.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

/**
 * Find the shortest paths from a source vertex to all other vertices using
 * the Bellman-Ford algorithm.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @tparam T The graph specialization (directed or undirected).
 * @tparam WEIGHT_T The type of weight associated with the edges.
 * @param graph The graph in which to find the shortest paths.
 * @param start_vertex The source vertex for the shortest paths.
 * @return A map of target vertex IDs to shortest path structures. Each
 *         value contains a graph_path object representing the
 *         shortest path from the source vertex to the respective vertex.
 *         If a vertex is unreachable from the source, its entry will be
 *         absent from the map.
 */
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
bellman_ford_shortest_paths(const graph<V, E, T>& graph,
                            vertex_id_t start_vertex);

}  // namespace graaf::algorithm

#include "bellman_ford.tpp"