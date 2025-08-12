#pragma once

#include <graaflib/algorithm/shortest_path/common.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

/**
 * @brief Find the shortest paths from a source vertex to all other vertices
 * using a Duan-style multi-phase SSSP algorithm. Works on graphs with
 * non-negative edge weights. For unweighted graphs, a unit weight is assumed
 * for each edge.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @tparam T The graph specialization (directed or undirected).
 * @tparam WEIGHT_T The type of weight associated with the edges.
 * @param graph The graph in which to find the shortest paths.
 * @param source_vertex The source vertex for the shortest paths.
 * @param k Number of Bellman–Ford-style frontier relaxation rounds per outer
 * loop (default 3).
 * @param work_factor Heap-pop limit multiplier for the bounded multi-source
 * phase (default 6.0).
 * @throws std::invalid_argument If a negative edge weight is encountered.
 * @return A map of target vertex IDs to shortest path structures. Each value
 * contains a graph_path object representing the shortest path from the source
 * vertex to the respective vertex. If a vertex is unreachable from the
 * source, its entry will be absent from the map.
 */
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
[[nodiscard]] std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
duan_shortest_paths(const graph<V, E, T>& graph, vertex_id_t source_vertex,
                    int k = 0 /* if <=0, choose k=⌊log^(1/3) n⌋ automatically */);

}  // namespace graaf::algorithm

#include "duan_shortest_paths.tpp"
