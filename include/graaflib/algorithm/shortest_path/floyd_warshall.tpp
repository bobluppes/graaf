#pragma once
#include <graaflib/algorithm/shortest_path/floyd_warshall.h>

#include <algorithm>
#include <limits>
#include <unordered_map>
#include <vector>

#include "floyd_warshall.h"

namespace graaf::algorithm {

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::vector<std::vector<WEIGHT_T>> floyd_warshall_shortest_paths(
    const graph<V, E, T>& graph) {
  WEIGHT_T ZERO{};
  auto INF = std::numeric_limits<WEIGHT_T>::max();

  // Vertex IDs are not guaranteed to be contiguous (e.g. after a
  // remove_vertex call), so we cannot use them directly as indices into a
  // dense matrix. Instead, we map the graph's (live) vertex IDs to a compact
  // 0..n-1 index space for the duration of the algorithm. IDs are sorted
  // ascending before assigning indices, so for the common case where vertex
  // IDs already form a contiguous 0..n-1 range (i.e. no vertex has been
  // removed), index i and vertex ID i coincide and the result matches the
  // long-standing [i][j] == "vertex i to vertex j" contract exactly.
  std::vector<vertex_id_t> index_to_vertex_id;
  index_to_vertex_id.reserve(graph.vertex_count());
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    index_to_vertex_id.push_back(vertex_id);
  }
  std::sort(index_to_vertex_id.begin(), index_to_vertex_id.end());

  const std::size_t n = index_to_vertex_id.size();
  std::unordered_map<vertex_id_t, std::size_t> vertex_id_to_index;
  vertex_id_to_index.reserve(n);
  for (std::size_t index = 0; index < n; ++index) {
    vertex_id_to_index[index_to_vertex_id[index]] = index;
  }

  std::vector<std::vector<WEIGHT_T>> shortest_paths(
      n, std::vector<WEIGHT_T>(n, INF));

  for (std::size_t vertex = 0; vertex < n; ++vertex) {
    shortest_paths[vertex][vertex] = ZERO;
  }

  // Initial weights between vertices
  for (std::size_t from_index = 0; from_index < n; ++from_index) {
    const vertex_id_t from_vertex{index_to_vertex_id[from_index]};
    for (const auto& to_vertex : graph.get_neighbors(from_vertex)) {
      const std::size_t to_index{vertex_id_to_index.at(to_vertex)};
      shortest_paths[from_index][to_index] =
          std::min(shortest_paths[from_index][to_index],
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
