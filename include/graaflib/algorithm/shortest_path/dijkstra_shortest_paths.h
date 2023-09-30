#pragma once

#include <graaflib/algorithm/shortest_path/common.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

/**
 * Find the shortest paths from a source vertex to all other vertices in the
 * graph using Dijkstra's algorithm.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @tparam T The graph type (directed or undirected).
 * @tparam WEIGHT_T The type of edge weights.
 * @param graph The graph we want to search.
 * @param source_vertex The source vertex from which to compute shortest paths.
 * @return A map containing the shortest paths from the source vertex to all
 * other vertices. The map keys are target vertex IDs, and the values are
 * instances of graph_path, representing the shortest distance and the path
 * (list of vertex IDs) from the source to the target. If a vertex is not
 * reachable from the source, its entry will be absent from the map.
 */
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
[[nodiscard]] std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
dijkstra_shortest_paths(const graph<V, E, T>& graph, vertex_id_t source_vertex);

}  // namespace graaf::algorithm

#include "dijkstra_shortest_paths.tpp"