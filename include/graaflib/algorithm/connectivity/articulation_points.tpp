#pragma once
#include <graaflib/algorithm/connectivity/articulation_points.h>

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

namespace graaf::algorithm {

template <typename V, typename E>
[[nodiscard]] articulation_points_t articulation_points(
    const graph<V, E, graph_type::UNDIRECTED>& graph) {
  articulation_points_t result{};

  std::unordered_map<vertex_id_t, size_t> discovery{};
  std::unordered_map<vertex_id_t, size_t> low{};
  size_t timer{0};

  std::function<void(vertex_id_t, vertex_id_t)> dfs =
      [&](vertex_id_t vertex, vertex_id_t parent) {
        discovery[vertex] = low[vertex] = timer++;
        size_t children{0};
        bool is_articulation{false};

        for (const auto neighbor : graph.get_neighbors(vertex)) {
          if (neighbor == parent) {
            continue;
          }
          if (discovery.contains(neighbor)) {
            low[vertex] = std::min(low[vertex], discovery[neighbor]);
          } else {
            dfs(neighbor, vertex);
            low[vertex] = std::min(low[vertex], low[neighbor]);
            ++children;

            if (parent != INVALID_VERTEX &&
                low[neighbor] >= discovery[vertex]) {
              is_articulation = true;
            }
          }
        }

        if (parent == INVALID_VERTEX && children > 1) {
          is_articulation = true;
        }

        if (is_articulation) {
          result.push_back(vertex);
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