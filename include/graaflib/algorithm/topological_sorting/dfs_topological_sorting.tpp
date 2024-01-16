#pragma once

#include <graaflib/algorithm/cycle_detection/dfs_cycle_detection.h>
#include <graaflib/algorithm/topological_sorting/dfs_topological_sorting.h>

#include <optional>
#include <unordered_set>
#include <vector>

namespace graaf::algorithm {

namespace detail {

// DFS topological sort
template <typename V, typename E>
void do_dfs_topological_sort(
    const graph<V, E, graph_type::DIRECTED>& graph, vertex_id_t start_vertex,
    std::unordered_set<vertex_id_t>& processed_vertices,
    std::vector<vertex_id_t>& sorted_vertices) {
  processed_vertices.insert(start_vertex);
  for (const auto& next_vertex : graph.get_neighbors(start_vertex)) {
    if (!processed_vertices.contains(next_vertex)) {
      do_dfs_topological_sort(graph, next_vertex, processed_vertices,
                              sorted_vertices);
    }
  }

  sorted_vertices.push_back(start_vertex);
}

};  // namespace detail

template <typename V, typename E>
std::optional<std::vector<vertex_id_t>> dfs_topological_sort(
    const graph<V, E, graph_type::DIRECTED>& graph) {
  // Graph should be acyclic
  if (dfs_cycle_detection(graph)) {
    return std::nullopt;
  }

  std::vector<vertex_id_t> sorted_vertices{};
  sorted_vertices.reserve(graph.vertex_count());
  std::unordered_set<vertex_id_t> processed_vertices{};

  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    if (!processed_vertices.contains(vertex_id)) {
      detail::do_dfs_topological_sort(graph, vertex_id, processed_vertices,
                                      sorted_vertices);
    }
  }

  std::reverse(sorted_vertices.begin(), sorted_vertices.end());
  return sorted_vertices;
}

};  // namespace graaf::algorithm
