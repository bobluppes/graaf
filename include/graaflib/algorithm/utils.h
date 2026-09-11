#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <unordered_map>
#include <unordered_set>

namespace graaf {

/**
 * Get transposed version of a given directed graph
 *
 * @param  graph The directed graph that is to be transposed
 * @return directed_graph<VERTEX_T, EDGE_T> The transposed graph
 */
template <typename VERTEX_T, typename EDGE_T>
directed_graph<VERTEX_T, EDGE_T> get_transposed_graph(
    const directed_graph<VERTEX_T, EDGE_T>& graph);

/**
 * @brief Computes, for every vertex, the set of vertices with an edge into it
 * (its predecessors / in-neighbors).
 *
 * graph::get_neighbors() only reports outgoing edges, so this is useful for
 * algorithms which also need to reason about incoming edges on a directed
 * graph. Runs in O(V + E).
 *
 * @param graph The graph to compute predecessors for.
 * @return An unordered_map from vertex ID to the set of its predecessor
 * vertex IDs. Vertices with no incoming edges are absent from the map.
 */
template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
std::unordered_map<vertex_id_t, std::unordered_set<vertex_id_t>>
get_predecessors(const graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>& graph);

}  // namespace graaf

#include "utils.tpp"