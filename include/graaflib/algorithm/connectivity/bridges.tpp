#pragma once
#include <graaflib/algorithm/connectivity/bridges.h>

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

namespace graaf::algorithm {

template <typename V, typename E>
[[nodiscard]] bridges_t bridges(
    const graph<V, E, graph_type::UNDIRECTED>& graph) {
  bridges_t result{};

  std::unordered_map<vertex_id_t, size_t> discovery{};
  std::unordered_map<vertex_id_t, size_t> low{};
  size_t timer{0};

  std::function<void(vertex_id_t, vertex_id_t)> dfs =
      [&](vertex_id_t vertex, vertex_id_t parent) {
        discovery[vertex] = low[vertex] = timer++;

        for (const auto neighbor : graph.get_neighbors(vertex)) {
          if (neighbor == parent) {
            continue;
          }
          if (discovery.contains(neighbor)) {
            low[vertex] = std::min(low[vertex], discovery[neighbor]);
          } else {
            dfs(neighbor, vertex);
            low[vertex] = std::min(low[vertex], low[neighbor]);

            if (low[neighbor] > discovery[vertex]) {
              result.push_back(
                  vertex < neighbor ? edge_id_t{vertex, neighbor}
                                    : edge_id_t{neighbor, vertex});
            }
          }
        }
      };

  for (const auto& [vertex_id, vertex] : graph.get_vertices()) {
    if (!discovery.contains(vertex_id)) {
      dfs(vertex_id, INVALID_VERTEX);
    }
  }

  std::sort(result.begin(), result.end());
  return result;
}

}  // namespace graaf::algorithm