#pragma once
#include <queue>
#include <vector>

#include "a_star.h"

namespace graaf::algorithm {

namespace detail {

// Open set entries are ordered by f_score (g_score + heuristic), which is
// only used to pick the next vertex to expand. This is intentionally kept
// separate from path_vertex::dist_from_start, which path reconstruction reports
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

  // Preserve the existing heuristic call and trivial-path behavior even for
  // an absent start vertex, without allocating storage indexed by an invalid
  // (potentially very large) id.
  const auto initial_f_score{heuristic(start_vertex)};
  if (start_vertex == target_vertex) {
    return graph_path<WEIGHT_T>{{start_vertex}, 0};
  }
  if (!graph.has_vertex(start_vertex)) {
    return std::nullopt;
  }

  // An empty slot denotes an undiscovered vertex. Grow lazily by vertex id,
  // including holes left by removed vertices. dist_from_start stores g_score,
  // so a second container for the same accumulated cost is unnecessary.
  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  std::vector<std::optional<weighted_path_item>> vertex_info{};
  const auto has_info{[&](vertex_id_t id) {
    return id < vertex_info.size() && vertex_info[id].has_value();
  }};
  const auto set_info{
      [&](vertex_id_t id, WEIGHT_T distance, vertex_id_t predecessor) {
        if (id >= vertex_info.size()) {
          vertex_info.resize(id + 1);
        }
        vertex_info[id] = weighted_path_item{id, distance, predecessor};
      }};
  set_info(start_vertex, 0, start_vertex);

  // Initialize start vertex in open set queue
  open_set.push(open_set_item{start_vertex, initial_f_score});

  while (!open_set.empty()) {
    // Get the vertex with the lowest f_score
    auto current{open_set.top()};
    open_set.pop();

    // Check if current vertex is the target
    if (current.id == target_vertex) {
      graph_path<WEIGHT_T> path;
      auto vertex{target_vertex};
      while (vertex != start_vertex) {
        path.vertices.push_front(vertex);
        vertex = vertex_info[vertex]->prev_id;
      }
      path.vertices.push_front(start_vertex);
      path.total_weight = vertex_info[target_vertex]->dist_from_start;
      return path;
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
      WEIGHT_T tentative_g_score =
          vertex_info[current.id]->dist_from_start + edge_weight;

      // Checks if vertex_info doesn't contain neighbor yet.
      // But if it contains it, and the tentative_g_score is smaller,
      // we need to update vertex_info and add it to the open set.
      if (!has_info(neighbor) ||
          tentative_g_score < vertex_info[neighbor]->dist_from_start) {
        // This path to neighbor is better than any previous one, so we need
        // to update our data. Update neighbor's g_score, f_score and previous
        // vertex on the path
        auto f_score = tentative_g_score + heuristic(neighbor);

        // always update vertex_info[neighbor] with the true accumulated cost
        // (g_score), so the resulting path reports the correct total_weight.
        set_info(neighbor, tentative_g_score, current.id);

        open_set.push(open_set_item{neighbor, f_score});
      }
    }
  }

  // No path found
  return std::nullopt;
}

}  // namespace graaf::algorithm
