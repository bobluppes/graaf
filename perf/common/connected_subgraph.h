#pragma once

#include <cstddef>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "dataset.h"

namespace perf_common {

struct bounded_subgraph {
  std::vector<std::size_t> vertices{};
  std::vector<std::pair<std::size_t, std::size_t>> edges{};
};

// Explores the dataset's edge list breadth-first from start_vertex and
// returns the subgraph made up of the first max_vertices vertices
// discovered, together with every edge between two included vertices.
//
// Used by benchmarks that need to bound how much of a large, real-world
// dataset they run against. The result is plain data, independent of any
// particular graph library, so every benchmark comparing libraries against
// each other runs on exactly the same bounded input.
[[nodiscard]] inline bounded_subgraph compute_connected_subgraph(
    const dataset& dataset_name, std::size_t start_vertex,
    std::size_t max_vertices) {
  std::unordered_map<std::size_t, std::vector<std::size_t>> adjacency{};
  read_dataset_edges(dataset_name,
                     [&adjacency](std::size_t source, std::size_t target) {
                       adjacency[source].push_back(target);
                       adjacency[target].push_back(source);
                     });

  bounded_subgraph result{};
  std::unordered_set<std::size_t> included{start_vertex};
  result.vertices.push_back(start_vertex);

  std::queue<std::size_t> to_explore{};
  to_explore.push(start_vertex);

  while (!to_explore.empty() && result.vertices.size() < max_vertices) {
    const auto current{to_explore.front()};
    to_explore.pop();

    for (const auto neighbor : adjacency[current]) {
      if (result.vertices.size() >= max_vertices) {
        break;
      }

      if (included.insert(neighbor).second) {
        result.vertices.push_back(neighbor);
        to_explore.push(neighbor);
      }
    }
  }

  std::unordered_set<std::pair<std::size_t, std::size_t>,
                     detail::vertex_pair_hash>
      seen_edges{};

  for (const auto vertex : result.vertices) {
    for (const auto neighbor : adjacency[vertex]) {
      if (!included.contains(neighbor)) {
        continue;
      }

      const auto normalized{vertex < neighbor
                                ? std::make_pair(vertex, neighbor)
                                : std::make_pair(neighbor, vertex)};
      if (seen_edges.insert(normalized).second) {
        result.edges.push_back(normalized);
      }
    }
  }

  return result;
}

}  // namespace perf_common
