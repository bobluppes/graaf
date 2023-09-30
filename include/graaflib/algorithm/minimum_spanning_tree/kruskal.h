#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <vector>

namespace graaf::algorithm {
/**
 * Computes the minimum spanning tree (MST) or minimum spanning forest of a
 * graph using Kruskal's algorithm.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The input graph.
 * @return A vector of edges forming the MST or minimum spanning forest.
 */
template <typename V, typename E>
[[nodiscard]] std::vector<edge_id_t> kruskal_minimum_spanning_tree(
    const graph<V, E, graph_type::UNDIRECTED>& graph);

}  // namespace graaf::algorithm

#include "kruskal.tpp"