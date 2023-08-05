#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <concepts>
#include <list>
#include <optional>

namespace graaf::algorithm {

template <typename WEIGHT_T>
struct graph_path {
  std::list<vertex_id_t> vertices;
  WEIGHT_T total_weight;

  bool operator==(const graph_path& other) const {
    return vertices == other.vertices && total_weight == other.total_weight;
  }
};

/**
 * @brief calculates the shortest path between on start_vertex and one
 * end_vertex using BFS. This does not consider edge weights.
 *
 * @param graph The graph to extract shortest path from.
 * @param start_vertex Vertex id where the shortest path should start.
 * @param end_vertex Vertex id where the shortest path should end.
 */
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::optional<graph_path<WEIGHT_T>> bfs_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex);

/**
 * @brief calculates the shortest path between on start_vertex and one
 * end_vertex using Dijkstra's algorithm. Works on both weighted as well as
 * unweighted graphs. For unweighted graphs, a unit weight is used for each
 * edge.
 *
 * @param graph The graph to extract shortest path from.
 * @param start_vertex Vertex id where the shortest path should start.
 * @param end_vertex Vertex id where the shortest path should end.
 */
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::optional<graph_path<WEIGHT_T>> dijkstra_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex);

}  // namespace graaf::algorithm

#include "shortest_path.tpp"