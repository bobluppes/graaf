#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

/**
 * @brief Greedy Graph Coloring Algorithm
 *
 * This function performs greedy graph coloring on a given graph. It assigns
 * colors to vertices in such a way that no two adjacent vertices share the
 * same color. The algorithm is heuristic and does not guarantee an optimal
 * coloring.
 *
 * For a directed graph, this colors the underlying undirected graph: two
 * vertices are considered adjacent if there is an edge between them in
 * either direction. This is not the only reasonable notion of coloring for a
 * directed graph (the "dichromatic number", which only forbids monochromatic
 * directed cycles, is another well-known one and generally admits fewer
 * colors), but it is the one this library implements.
 *
 * @tparam GRAPH The type of the graph
 * @param graph The graph object
 * @return An unordered_map where keys are vertex identifiers and values are
 * their respective colors.
 */
template <typename GRAPH>
std::unordered_map<vertex_id_t, int> greedy_graph_coloring(const GRAPH& graph);

}  // namespace graaf::algorithm

#include "greedy_graph_coloring.tpp"