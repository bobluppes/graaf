#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

/**
 * @brief Computes the maximum flow in a flow network using the Edmonds-Karp
 * algorithm.
 *
 * This algorithm finds the maximum flow in a flow network from a source vertex
 * to a sink vertex.
 *
 * @param graph The flow network graph.
 * @param source The source vertex.
 * @param sink The sink vertex.
 * @return The maximum flow value.
 */
template <typename V, typename E,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
[[nodiscard]] WEIGHT_T edmonds_karp_max_flow(
    const graph<V, E, graph_type::DIRECTED>& graph, vertex_id_t source,
    vertex_id_t sink);

}  // namespace graaf::algorithm

#include "edmonds_karp.tpp"