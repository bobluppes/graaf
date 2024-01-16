#pragma once

#include <graaflib/graph.h>

namespace graaf::algorithm {

/*
 * @brief Traverses a directed graph and checks for cycles.
 *
 * @param graph The directed graph to traverse.
 */
template <typename V, typename E>
[[nodiscard]] bool dfs_cycle_detection(
    const graph<V, E, graph_type::DIRECTED> &graph);

/*
 * @brief Traverses an undirected graph and checks for cycles.
 *
 * @param graph The undirected graph to traverse.
 */
template <typename V, typename E>
[[nodiscard]] bool dfs_cycle_detection(
    const graph<V, E, graph_type::UNDIRECTED> &graph);

}  // namespace graaf::algorithm

#include "dfs_cycle_detection.tpp"