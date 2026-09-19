#pragma once
#include <algorithm>
#include <queue>
#include <vector>

#include "breadth_first_search.h"

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
  // Indexed directly by vertex_id_t rather than an unordered_set: ids are
  // dense, and the graph is unmodified for the duration of the traversal
  // (it's taken by const reference), so a plain vector that grows as new
  // ids are discovered is a direct, allocation-light fit.
  std::vector<bool> seen_vertices{};
  // Marks id as seen, returning whether it was not already seen (mirrors
  // std::unordered_set::insert().second).
  const auto try_mark_seen{[&](vertex_id_t id) {
    if (id >= seen_vertices.size()) {
      seen_vertices.resize(id + 1, false);
    }
    if (seen_vertices[id]) {
      return false;
    }
    seen_vertices[id] = true;
    return true;
  }};

  std::queue<vertex_id_t> to_explore{};

  // Vertices are marked as seen when enqueued rather than when dequeued, so
  // each vertex enters the queue at most once.
  try_mark_seen(start_vertex);
  to_explore.push(start_vertex);

  while (!to_explore.empty()) {
    const auto current{to_explore.front()};
    to_explore.pop();

    if (search_termination_strategy(current)) {
      return;
    }

    for (const auto neighbor_vertex : graph.get_neighbors(current)) {
      if (try_mark_seen(neighbor_vertex)) {
        edge_callback(edge_id_t{current, neighbor_vertex});
        to_explore.push(neighbor_vertex);
      }
    }
  }
}

}  // namespace graaf::algorithm
