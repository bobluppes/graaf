#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

/**
 * Computes the Strongly Connected Components (SCCs) of a graph using Tarjan's
 * algorithm.
 *
 * This function takes a graph and returns a vector of vectors representing the
 * SCCs. Each inner vector contains the vertices of a strongly connected
 * component, and the outer vector contains all the strongly connected
 * components in the graph.
 *
 * @tparam V Vertex type.
 * @tparam E Edge type.
 * @param graph The graph for which to compute SCCs.
 * @return std::vector<std::vector<vertex_id_t>> A vector of vectors
 * representing SCCs.
 */
template <typename V, typename E>
[[nodiscard]] std::vector<std::vector<vertex_id_t>>
tarjans_strongly_connected_components(
    const graph<V, E, graph_type::DIRECTED>& graph);

}  // namespace graaf::algorithm

#include "tarjan.tpp"