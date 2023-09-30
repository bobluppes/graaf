#pragma once

#include <graaflib/graph.h>

#include <optional>

namespace graaf::algorithm {
/**
 * @brief Calculates order of vertices in topological order
 * using DFS traversal
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The input graph.
 * @return Vector of vertices sorted in topological order
 */
template <typename V, typename E>
[[nodiscard]] std::optional<std::vector<vertex_id_t>> dfs_topological_sort(
    const graph<V, E, graph_type::DIRECTED>& graph);

}  // namespace graaf::algorithm
#include "dfs_topological_sorting.tpp"
