#pragma once
#include <graaflib/algorithm/topological_sorting/kahn_topological_sorting.h>

#include <cstddef>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "kahn_topological_sorting.h"

namespace graaf::algorithm {

namespace detail {

// Computes the in-degree of every vertex in a single pass over the adjacency
// lists. Note that properties::vertex_indegree scans the entire graph on every
// call, so seeding the in-degrees with it would cost O(|V| * (|V| + |E|)).
// Kahn's algorithm is expected to run in O(|V| + |E|), so we count the incoming
// edges in one sweep instead.
template <typename V, typename E>
[[nodiscard]] std::unordered_map<vertex_id_t, std::size_t> compute_indegrees(
    const graph<V, E, graph_type::DIRECTED>& graph) {
  std::unordered_map<vertex_id_t, std::size_t> indegrees{};
  indegrees.reserve(graph.vertex_count());

  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    indegrees.try_emplace(vertex_id, 0);
  }

  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    for (const auto& neighbor : graph.get_neighbors(vertex_id)) {
      ++indegrees[neighbor];
    }
  }

  return indegrees;
}

};  // namespace detail

template <typename V, typename E>
std::vector<vertex_id_t> kahn_topological_sort(
    const graph<V, E, graph_type::DIRECTED>& graph) {
  auto indegrees{detail::compute_indegrees(graph)};

  // All vertices without incoming edges can be emitted right away
  std::queue<vertex_id_t> sources{};
  for (const auto& [vertex_id, indegree] : indegrees) {
    if (indegree == 0) {
      sources.push(vertex_id);
    }
  }

  std::vector<vertex_id_t> sorted_vertices{};
  sorted_vertices.reserve(graph.vertex_count());

  while (!sources.empty()) {
    const auto current_vertex{sources.front()};
    sources.pop();
    sorted_vertices.push_back(current_vertex);

    // Removing the outgoing edges of the current vertex can turn its
    // neighbors into sources
    for (const auto& neighbor : graph.get_neighbors(current_vertex)) {
      if (--indegrees[neighbor] == 0) {
        sources.push(neighbor);
      }
    }
  }

  // Any vertex we could not emit still has an incoming edge, which means it
  // lies on a cycle or is reachable from one. A self-loop is covered by this
  // as well, since it contributes one to the in-degree of its own vertex.
  if (sorted_vertices.size() != graph.vertex_count()) {
    throw std::invalid_argument{"Cycle detected in the graph."};
  }

  return sorted_vertices;
}

};  // namespace graaf::algorithm
