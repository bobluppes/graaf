#pragma once

#include <graaflib/graph.h>

namespace graaf::algorithm {
/**
 * @brief Finds all cliques in an undirected graph using the Bron-Kerbosch
 * algorithm.
 *
 * The Bron-Kerbosch algorithm is used for finding all cliques in an undirected
 * graph. A clique_detection is a subset of vertices such that every two
 * distinct vertices are adjacent. This function returns a list of all cliques,
 * each represented as a vector of vertex identifiers.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The graph in which we want to find the cliques.
 * @return A vector of cliques, each represented as a vector of vertex
 * identifiers.
 */
template <typename V, typename E>
std::vector<std::vector<vertex_id_t>> bron_kerbosch(
    const graph<V, E, graph_type::UNDIRECTED>& graph);

}  // namespace graaf::algorithm

#include "bron_kerbosch.tpp"
