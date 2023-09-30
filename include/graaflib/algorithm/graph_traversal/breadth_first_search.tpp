#pragma once

#include <algorithm>
#include <queue>
#include <unordered_set>

namespace graaf::algorithm {

template <typename V, typename E, graph_type T, typename EDGE_CALLBACK_T,
          typename SEARCH_TERMINATION_STRATEGY_T>
  requires std::invocable<EDGE_CALLBACK_T&, edge_id_t&> &&
           std::is_invocable_r_v<bool, SEARCH_TERMINATION_STRATEGY_T&,
                                 vertex_id_t>
void breadth_first_traverse(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    const EDGE_CALLBACK_T& edge_callback,
    const SEARCH_TERMINATION_STRATEGY_T& search_termination_strategy) {
  std::unordered_set<vertex_id_t> seen_vertices{};
  std::queue<vertex_id_t> to_explore{};

  to_explore.push(start_vertex);

  while (!to_explore.empty()) {
    const auto current{to_explore.front()};
    to_explore.pop();

    if (search_termination_strategy(current)) {
      return;
    }

    seen_vertices.insert(current);
    for (const auto neighbor_vertex : graph.get_neighbors(current)) {
      if (!seen_vertices.contains(neighbor_vertex)) {
        edge_callback(edge_id_t{current, neighbor_vertex});
        to_explore.push(neighbor_vertex);
      }
    }
  }
}

}  // namespace graaf::algorithm