#pragma once

#include <graaflib/algorithm/shortest_path/common.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <concepts>
#include <optional>

namespace graaf::algorithm {

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

#include "a_star.tpp"