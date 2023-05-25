#pragma once

#include <algorithm>
#include <concepts>
#include <unordered_set>
#include <queue>

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

enum class search_strategy {DFS, BFS};

/**
 * @brief Traverses the graph, starting at start_vertex, and visits all
 * reachable vertices.
 * 
 * @tparam ALGORITHM Tag to specify the search algorithm, can be either DFS of BFS.
 * @param graph The graph to traverse.
 * @param start_vertex Vertex id where the traversal should be started.
 * @param callback A callback which is called for each traversed vertex. Should be 
 * invocable with a vertex_id_t.
 */
template <search_strategy ALGORITHM, typename V, typename E, GRAPH_SPEC S, typename CALLBACK_T>
requires std::invocable<const CALLBACK_T&, vertex_id_t>
void traverse(const graph<V, E, S> &graph,
                                  vertex_id_t start_vertex,
                                  const CALLBACK_T&callback);

} // namespace graaf::algorithm

#include "graph_traversal.tpp"