#pragma once

#include <graaflib/algorithm/strongly_connected_components/common.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <vector>

namespace graaf::algorithm {

/**
 * @brief Finds strongly connected components in a directed graph using
 * Kosaraju's algorithm.
 *
 * Kosaraju's algorithm identifies strongly connected components (SCCs) in a
 * directed graph. The algorithm uses two depth-first searches to discover these
 * components.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The input directed graph.
 *
 * @return An sccs_t, a type representing an std::vector of vectors,
 * each of which contains the vertex IDs forming a strongly connected
 * component.
 */
template <typename V, typename E>
sccs_t kosarajus_strongly_connected_components(
    const directed_graph<V, E>& graph);

}  // namespace graaf::algorithm

#include "kosaraju.tpp"