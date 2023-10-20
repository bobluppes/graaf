#pragma once

#include <graaflib/algorithm/strongly_connected_components/common.h>
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
 * @return An sccs_t, a type representing an std::vector of vectors,
 * each of which contains the vertex IDs forming a strongly connected
 * component.
 */
template <typename V, typename E>
[[nodiscard]] sccs_t tarjans_strongly_connected_components(
    const graph<V, E, graph_type::DIRECTED>& graph);

}  // namespace graaf::algorithm

#include "tarjan.tpp"