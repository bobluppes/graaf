#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <unordered_map>

namespace graaf::properties {

template <typename V, typename E, graph_type T>
[[nodiscard]] std::size_t vertex_degree(const graaf::graph<V, E, T>& graph,
                                        vertex_id_t vertex_id);

template <typename V, typename E, graph_type T>
[[nodiscard]] std::size_t vertex_outdegree(const graaf::graph<V, E, T>& graph,
                                           vertex_id_t vertex_id);

template <typename V, typename E, graph_type T>
[[nodiscard]] std::size_t vertex_indegree(const graaf::graph<V, E, T>& graph,
                                          vertex_id_t vertex_id);

/**
 * @brief Computes the betweenness centrality of every vertex.
 *
 * Edge weights are ignored. Undirected results are divided by two to account
 * for paths being counted in both directions.
 *
 * @param graph The graph whose vertex centralities are computed.
 * @return A map from each vertex ID to its betweenness centrality.
 */
template <typename V, typename E, graph_type T>
[[nodiscard]] std::unordered_map<vertex_id_t, double> betweenness_centrality(
    const graph<V, E, T>& graph);

/**
 * @brief Computes the unweighted closeness centrality of every vertex.
 *
 * Disconnected vertices are not considered in a vertex's distance sum.
 * Vertices that cannot reach another vertex therefore have zero centrality.
 *
 * @param graph The graph whose vertex centralities are computed.
 * @return A map from each vertex ID to its closeness centrality.
 */
template <typename V, typename E, graph_type T>
[[nodiscard]] std::unordered_map<vertex_id_t, double> closeness_centrality(
    const graph<V, E, T>& graph);

}  // namespace graaf::properties

#include "vertex_properties.tpp"
