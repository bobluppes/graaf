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
 * @brief calculates the shortest path between one start_vertex and one
 * end_vertex using BFS. This does not consider edge weights.
 *
 * @param graph The graph to extract shortest path from.
 * @param start_vertex Vertex id where the shortest path should start.
 * @param end_vertex Vertex id where the shortest path should end.
 * @return An optional with the shortest path (list of vertices) if found.
 */
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::optional<graph_path<WEIGHT_T>> bfs_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex);

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

/**
 * @brief Finds the shortest path between a start_vertex and target_vertex
 *        using the A* search algorithm.
 *
 * @param graph The graph to search in.
 * @param start_vertex The starting vertex for the search.
 * @param target_vertex The target vertex to reach.
 * @param heuristic A heuristic function estimating the cost from a vertex to
 * the target.
 * @return An optional containing the shortest path if found, or std::nullopt if
 * no path exists.
 */
template <typename V, typename E, graph_type T, typename HEURISTIC_T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
  requires std::is_invocable_r_v<WEIGHT_T, HEURISTIC_T&, vertex_id_t>
std::optional<graph_path<WEIGHT_T>> a_star_search(const graph<V, E, T>& graph,
                                                  vertex_id_t start_vertex,
                                                  vertex_id_t target_vertex,
                                                  const HEURISTIC_T& heuristic);

}  // namespace graaf::algorithm

#include "shortest_path.tpp"