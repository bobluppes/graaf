#pragma once
#include <queue>

#include "a_star.h"

namespace graaf::algorithm {

namespace detail {

// Open set entries are ordered by f_score (g_score + heuristic), which is
// only used to pick the next vertex to expand. This is intentionally kept
// separate from path_vertex::dist_from_start, which reconstruct_path reports
// as the path's total_weight and therefore must hold the true accumulated
// cost (g_score), not the heuristic-inflated f_score.
template <typename WEIGHT_T>
struct a_star_open_set_item {
  vertex_id_t id;
  WEIGHT_T f_score;

  [[nodiscard]] bool operator>(const a_star_open_set_item& other) const {
    return f_score > other.f_score;
  }
};

}  // namespace detail

template <typename V, typename E, graph_type T, typename HEURISTIC_T,
          typename WEIGHT_T>
  requires std::is_invocable_r_v<WEIGHT_T, HEURISTIC_T&, vertex_id_t>
std::optional<graph_path<WEIGHT_T>> a_star_search(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t target_vertex, const HEURISTIC_T& heuristic) {
  // Define a priority queue for open set of vertices to explore.
  // This part is similar to dijkstra_shortest_path, except the queue is
  // ordered by f_score rather than the true path cost, see
  // detail::a_star_open_set_item above.
  using open_set_item = detail::a_star_open_set_item<WEIGHT_T>;
  using a_star_queue_t =
      std::priority_queue<open_set_item, std::vector<open_set_item>,
                          std::greater<>>;
  a_star_queue_t open_set{};

  // For vertex n, g_score[n] is the cost of the cheapest path from start to n
  // currently known. It tracks the cost of reaching each vertex
  std::unordered_map<vertex_id_t, WEIGHT_T> g_score;
  // Initialize g_score map.
  g_score[start_vertex] = 0;

  // vertex_info tracks, for each discovered vertex, the true accumulated
  // cost from start (dist_from_start = g_score) and its predecessor on the
  // cheapest known path. This is what reconstruct_path uses to build the
  // resulting graph_path, including its total_weight.
  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  std::unordered_map<vertex_id_t, weighted_path_item> vertex_info;
  vertex_info[start_vertex] = {start_vertex, 0, start_vertex};

  // Initialize start vertex in open set queue
  open_set.push(open_set_item{start_vertex, heuristic(start_vertex)});

  while (!open_set.empty()) {
    // Get the vertex with the lowest f_score
    auto current{open_set.top()};
    open_set.pop();

    // Check if current vertex is the target
    if (current.id == target_vertex) {
      return reconstruct_path(start_vertex, target_vertex, vertex_info);
    }

    // Iterate through neighboring vertices
    for (const auto& neighbor : graph.get_neighbors(current.id)) {
      WEIGHT_T edge_weight = get_weight(graph.get_edge(current.id, neighbor));

      // A* search does not work on negative edge weights.
      if (edge_weight < 0) {
        throw std::invalid_argument{
            "Negative edge weight [" + std::to_string(edge_weight) +
            "] between vertices [" + std::to_string(current.id) + "] -> [" +
            std::to_string(neighbor) + "]."};
      }

      // tentative_g_score is the distance from start to the neighbor through
      // current_vertex
      WEIGHT_T tentative_g_score = g_score[current.id] + edge_weight;

      // Checks if vertex_info doesn't contain neighbor yet.
      // But if it contains it, and the tentative_g_score is smaller,
      // we need to update vertex_info and add it to the open set.
      if (!vertex_info.contains(neighbor) ||
          tentative_g_score < g_score[neighbor]) {
        // This path to neighbor is better than any previous one, so we need
        // to update our data. Update neighbor's g_score, f_score and previous
        // vertex on the path
        g_score[neighbor] = tentative_g_score;
        auto f_score = tentative_g_score + heuristic(neighbor);

        // always update vertex_info[neighbor] with the true accumulated cost
        // (g_score), so reconstruct_path reports the correct total_weight.
        vertex_info[neighbor] = {
            neighbor,          // vertex id
            tentative_g_score, // true accumulated cost from start
            current.id         // neighbor vertex came from current vertex
        };

        open_set.push(open_set_item{neighbor, f_score});
      }
    }
  }

  // No path found
  return std::nullopt;
}

}  // namespace graaf::algorithm
