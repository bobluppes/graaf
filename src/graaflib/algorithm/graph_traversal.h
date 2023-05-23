#pragma once

#include <functional>
#include <unordered_set>

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

using callback_t = std::function<void(vertex_id_t)>;

template <typename V, typename E, GRAPH_SPEC S>
void depth_first_search_recurse(
    const graph<V, E, S> &graph,
    std::unordered_set<vertex_id_t> seen_vertices,
    vertex_id_t current, const callback_t &callback) {
  callback(current);
  seen_vertices.insert(current);

  for (auto neighbor_vertex : graph.get_neighbors(current)) {
    if (!seen_vertices.contains(neighbor_vertex)) {
      depth_first_search_recurse(graph, seen_vertices, neighbor_vertex,
                                 callback);
    }
  }
}

template <typename V, typename E, GRAPH_SPEC S>
void depth_first_search(const graph<V, E, S> &graph,
                                  vertex_id_t start_vertex,
                                  const callback_t &callback) {
  std::unordered_set<vertex_id_t> seen_vertices{};
  return depth_first_search_recurse(graph, seen_vertices, start_vertex,
                                    callback);
}

} // namespace graaf::algorithm