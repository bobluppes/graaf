#pragma once
#include <graaflib/algorithm/connectivity/low_link.h>

#include <algorithm>
#include <cstddef>
#include <limits>
#include <vector>

namespace graaf::algorithm::detail {

template <typename V, typename E>
cut_structure find_cut_structure(
    const graph<V, E, graph_type::UNDIRECTED>& graph) {
  cut_structure result{};
  if (graph.vertex_count() == 0) {
    return result;
  }

  // Ids of removed vertices leave gaps, so the vectors span the largest live
  // id while only the live ids collected here are iterated.
  std::vector<vertex_id_t> vertex_ids{};
  vertex_ids.reserve(graph.vertex_count());
  vertex_id_t max_vertex_id{0};
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    vertex_ids.push_back(vertex_id);
    max_vertex_id = std::max(max_vertex_id, vertex_id);
  }
  std::sort(vertex_ids.begin(), vertex_ids.end());

  constexpr auto unvisited{std::numeric_limits<std::size_t>::max()};
  std::vector<std::size_t> discovery_time(max_vertex_id + 1, unvisited);
  std::vector<std::size_t> low_link(max_vertex_id + 1, unvisited);
  std::vector<bool> is_articulation_point(max_vertex_id + 1, false);

  // The DFS keeps an explicit stack so that long paths cannot overflow the
  // call stack. A root is its own parent.
  struct frame {
    vertex_id_t vertex;
    vertex_id_t parent;
    std::size_t next_neighbor_index;
    std::size_t child_count;
  };
  std::vector<frame> stack{};
  std::size_t time{0};

  for (const auto root : vertex_ids) {
    if (discovery_time[root] != unvisited) {
      continue;
    }

    discovery_time[root] = low_link[root] = time++;
    stack.push_back({root, root, 0, 0});

    while (!stack.empty()) {
      auto& current{stack.back()};
      const auto& neighbors{graph.get_neighbors(current.vertex)};

      if (current.next_neighbor_index < neighbors.size()) {
        const auto neighbor{neighbors[current.next_neighbor_index++]};

        // Parallel edges cannot exist, so skipping the parent by id only
        // skips the tree edge itself. A self-loop never affects connectivity.
        if (neighbor == current.parent || neighbor == current.vertex) {
          continue;
        }

        if (discovery_time[neighbor] == unvisited) {
          ++current.child_count;
          discovery_time[neighbor] = low_link[neighbor] = time++;
          stack.push_back({neighbor, current.vertex, 0, 0});
        } else {
          low_link[current.vertex] =
              std::min(low_link[current.vertex], discovery_time[neighbor]);
        }
        continue;
      }

      const frame finished{current};
      stack.pop_back();

      if (stack.empty()) {
        if (finished.child_count >= 2) {
          is_articulation_point[finished.vertex] = true;
        }
        continue;
      }

      const auto& parent{stack.back()};
      low_link[parent.vertex] =
          std::min(low_link[parent.vertex], low_link[finished.vertex]);

      if (low_link[finished.vertex] > discovery_time[parent.vertex]) {
        result.bridges.emplace_back(
            std::minmax(parent.vertex, finished.vertex));
      }

      const bool parent_is_root{parent.vertex == parent.parent};
      if (!parent_is_root &&
          low_link[finished.vertex] >= discovery_time[parent.vertex]) {
        is_articulation_point[parent.vertex] = true;
      }
    }
  }

  for (const auto vertex_id : vertex_ids) {
    if (is_articulation_point[vertex_id]) {
      result.articulation_points.push_back(vertex_id);
    }
  }
  std::sort(result.bridges.begin(), result.bridges.end());

  return result;
}

}  // namespace graaf::algorithm::detail
