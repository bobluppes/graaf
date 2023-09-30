#pragma once

#include <graaflib/algorithm/shortest_path/common.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <optional>

namespace graaf::algorithm {

/**
 * @brief calculates the shortest path between one start_vertex and one
 * end_vertex using Dijkstra's algorithm. Works on both weighted as well as
 * unweighted graphs. For unweighted graphs, a unit weight is used for each
 * edge.
 *
 * @param graph The graph to extract shortest path from.
 * @param start_vertex Vertex id where the shortest path should start.
 * @param end_vertex Vertex id where the shortest path should end.
 * @return An optional with the shortest path (list of vertices) if found.
 */
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::optional<graph_path<WEIGHT_T>> dijkstra_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex);

}  // namespace graaf::algorithm

#include "dijkstra_shortest_path.tpp"