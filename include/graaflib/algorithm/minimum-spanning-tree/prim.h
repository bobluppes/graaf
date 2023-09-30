#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <optional>
#include <vector>

namespace graaf::algorithm {

/**
 * Computes the minimum spanning tree (MST) of a graph using Prim's algorithm.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The input graph. Should be undirected.
 * @param start_vertex The starting vertex for the MST construction.
 * @return An optional containing a vector of edges forming the MST if it
 * exists, or an empty optional if the MST doesn't exist (e.g., graph is not
 * connected).
 */
template <typename V, typename E>
[[nodiscard]] std::optional<std::vector<edge_id_t> > prim_minimum_spanning_tree(
    const graph<V, E, graph_type::UNDIRECTED>& graph, vertex_id_t start_vertex);

}  // namespace graaf::algorithm

#include "prim.tpp"