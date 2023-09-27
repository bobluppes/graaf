#pragma once

#include <graaflib/algorithm/shortest_path/floyd_warshall.h>

#include <limits>
#include <vector>

namespace graaf::algorithm {

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::vector<std::vector<WEIGHT_T>> floyd_warshall_shortest_paths(
    const graph<V, E, T>& graph) {
  WEIGHT_T ZERO{};
  std::size_t n = graph.vertex_count();
  auto INF = std::numeric_limits<WEIGHT_T>::max();

  std::vector<std::vector<WEIGHT_T>> shortest_paths(
      n, std::vector<WEIGHT_T>(n, INF));

  for (std::size_t vertex = 0; vertex < n; ++vertex) {
    shortest_paths[vertex][vertex] = ZERO;
  }

  // Initial weights between vertices
  for (std::size_t from_vertex = 0; from_vertex < n; ++from_vertex) {
    for (const auto& to_vertex : graph.get_neighbors(from_vertex)) {
      shortest_paths[from_vertex][to_vertex] =
          std::min(shortest_paths[from_vertex][to_vertex],
                   get_weight(graph.get_edge(from_vertex, to_vertex)));
    }
  }

  for (std::size_t through_vertex = 0; through_vertex < n; ++through_vertex) {
    for (std::size_t start_vertex = 0; start_vertex < n; ++start_vertex) {
      if (shortest_paths[start_vertex][through_vertex] < INF) {
        for (std::size_t end_vertex = 0; end_vertex < n; ++end_vertex) {
          if (shortest_paths[through_vertex][end_vertex] < INF) {
            shortest_paths[start_vertex][end_vertex] =
                std::min(shortest_paths[start_vertex][end_vertex],
                         shortest_paths[start_vertex][through_vertex] +
                             shortest_paths[through_vertex][end_vertex]);
          }
        }
      }
    }
  }

  return shortest_paths;
}

};  // namespace graaf::algorithm