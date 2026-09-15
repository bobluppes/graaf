#pragma once

#include <graaflib/graph.h>
#include <graaflib/tree.h>
#include <graaflib/types.h>

#include <optional>

namespace graaf::algorithm {

/**
 * Computes the minimum spanning tree (MST) of a graph using Prim's algorithm.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @tparam WEIGHT_T The type of edge weights.
 * @param graph The input graph. Should be undirected.
 * @param start_vertex The starting vertex for the MST construction. Becomes
 * the root of the returned tree.
 * @return An optional containing a tree rooted at start_vertex, where each
 * edge value is the weight of the corresponding edge in the graph, if the MST
 * exists, or an empty optional if the MST doesn't exist (e.g., graph is not
 * connected).
 */
template <typename V, typename E,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
[[nodiscard]] std::optional<tree<vertex_id_t, WEIGHT_T>>
prim_minimum_spanning_tree(const graph<V, E, graph_type::UNDIRECTED>& graph,
                           vertex_id_t start_vertex);

}  // namespace graaf::algorithm

#include "prim.tpp"