#pragma once

#include <graaflib/graph.h>

#include <vector>

namespace graaf::algorithm {
/**
 * @brief Calculates order of vertices in topological order
 * using Kahn's algorithm
 *
 * Repeatedly emits vertices with an in-degree of zero, removing their
 * outgoing edges as it goes. Cycles are detected as a side effect: if not
 * every vertex can be emitted, the remaining vertices lie on or downstream
 * of a cycle.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The input graph.
 * @return Vector of vertices sorted in topological order
 * @throws std::invalid_argument If the graph contains a cycle.
 */
template <typename V, typename E>
[[nodiscard]] std::vector<vertex_id_t> kahn_topological_sort(
    const graph<V, E, graph_type::DIRECTED>& graph);

}  // namespace graaf::algorithm
#include "kahn_topological_sorting.tpp"
