#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <concepts>

namespace graaf::algorithm {

enum class search_strategy { DFS, BFS };

/**
 * @brief Traverses the graph, starting at start_vertex, and visits all
 * reachable vertices.
 *
 * @tparam ALGORITHM Tag to specify the search algorithm, can be either DFS of
 * BFS.
 * @param graph The graph to traverse.
 * @param start_vertex Vertex id where the traversal should be started.
 * @param callback A callback which is called for each traversed vertex. Should
 * be invocable with a vertex_id_t.
 */
template <search_strategy ALGORITHM, typename V, typename E, graph_type T,
          typename CALLBACK_T>
  requires std::invocable<const CALLBACK_T &, vertex_id_t>
void traverse(const graph<V, E, T> &graph, vertex_id_t start_vertex,
              const CALLBACK_T &callback);

}  // namespace graaf::algorithm

#include "graph_traversal.tpp"