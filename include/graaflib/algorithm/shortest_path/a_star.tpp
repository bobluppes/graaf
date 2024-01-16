#pragma once

#include <queue>

namespace graaf::algorithm {

template <typename V, typename E, graph_type T, typename HEURISTIC_T,
          typename WEIGHT_T>
  requires std::is_invocable_r_v<WEIGHT_T, HEURISTIC_T&, vertex_id_t>
std::optional<graph_path<WEIGHT_T>> a_star_search(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t target_vertex, const HEURISTIC_T& heuristic) {
  // Define a priority queue for open set of vertices to explore.
  // This part is similar to dijkstra_shortest_path
  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  // The set of discovered vertices that may need to be (re-)expanded.
  // f_score represents the estimated total cost of the path from the start
  // vertex to the goal vertex through the current vertex.
  // It's a combination of g_score and h_score:
  // f_score[n] = g_score[n] + h_score[n]
  // For vertex n, prev_id in path_vertex is the vertex immediately preceding
  // it on the cheapest path from the start to n currently known. The priority
  // queue uses internally a binary heap. To get the minimum element, we use
  // the std::greater comparator.
  using a_star_queue_t =
      std::priority_queue<weighted_path_item, std::vector<weighted_path_item>,
                          std::greater<>>;
  a_star_queue_t open_set{};

  // For vertex n, g_score[n] is the cost of the cheapest path from start to n
  // currently known. It tracks the cost of reaching each vertex
  std::unordered_map<vertex_id_t, WEIGHT_T> g_score;
  // Initialize g_score map.
  g_score[start_vertex] = 0;

  std::unordered_map<vertex_id_t, weighted_path_item> vertex_info;
  vertex_info[start_vertex] = {
      start_vertex,
      heuristic(start_vertex),  // f_score[n] = g_score[n] + h(n), and
                                // g_score[n] is 0 if n is start_vertex.
      start_vertex};

  // Initialize start vertex in open set queue
  open_set.push(vertex_info[start_vertex]);

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
        throw std::invalid_argument{fmt::format(
            "Negative edge weight [{}] between vertices [{}] -> [{}].",
            edge_weight, current.id, neighbor)};
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

        // always update vertex_info[neighbor]
        vertex_info[neighbor] = {
            neighbor,   // vertex id
            f_score,    // f_score = tentantive_g_score + h(neighbor)
            current.id  // neighbor vertex came from current vertex
        };

        open_set.push(vertex_info[neighbor]);
      }
    }
  }

  // No path found
  return std::nullopt;
}

}  // namespace graaf::algorithm