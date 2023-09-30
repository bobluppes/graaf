#pragma once

#include <algorithm>
#include <queue>
#include <unordered_set>

namespace graaf::algorithm {

namespace detail {

template <typename V, typename E, graph_type T, typename EDGE_CALLBACK_T,
          typename SEARCH_TERMINATION_STRATEGY_T>
bool do_dfs(const graph<V, E, T>& graph,
            std::unordered_set<vertex_id_t>& seen_vertices, vertex_id_t current,
            const EDGE_CALLBACK_T& edge_callback,
            const SEARCH_TERMINATION_STRATEGY_T& search_termination_strategy) {
  seen_vertices.insert(current);

  if (search_termination_strategy(current)) {
    return false;
  }

  for (auto neighbor_vertex : graph.get_neighbors(current)) {
    if (!seen_vertices.contains(neighbor_vertex)) {
      edge_callback(edge_id_t{current, neighbor_vertex});
      if (!do_dfs(graph, seen_vertices, neighbor_vertex, edge_callback,
                  search_termination_strategy)) {
        // Further down the call stack we have hit the search termination point.
        // Bubble this up the call stack.
        return false;
      }
    }
  }

  // We did not hit the search termination point
  return true;
}

}  // namespace detail

template <typename V, typename E, graph_type T, typename EDGE_CALLBACK_T,
          typename SEARCH_TERMINATION_STRATEGY_T>
  requires std::invocable<EDGE_CALLBACK_T&, edge_id_t&> &&
           std::is_invocable_r_v<bool, SEARCH_TERMINATION_STRATEGY_T&,
                                 vertex_id_t>
void depth_first_traverse(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    const EDGE_CALLBACK_T& edge_callback,
    const SEARCH_TERMINATION_STRATEGY_T& search_termination_strategy) {
  std::unordered_set<vertex_id_t> seen_vertices{};
  detail::do_dfs(graph, seen_vertices, start_vertex, edge_callback,
                 search_termination_strategy);
}

}  // namespace graaf::algorithm