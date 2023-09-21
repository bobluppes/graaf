#pragma once

#include <graaflib/algorithm/graph_traversal.h>

#include <algorithm>
#include <optional>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

namespace graaf::algorithm {

namespace detail {

template <typename WEIGHT_T>
struct path_vertex {
  vertex_id_t id;
  WEIGHT_T dist_from_start;
  vertex_id_t prev_id;

  [[nodiscard]] bool operator>(const path_vertex<WEIGHT_T>& other) {
    return dist_from_start > other.dist_from_start;
  }
};

template <typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> reconstruct_path(
    vertex_id_t start_vertex, vertex_id_t end_vertex,
    std::unordered_map<vertex_id_t, path_vertex<WEIGHT_T>>& vertex_info) {
  if (!vertex_info.contains(end_vertex)) {
    return std::nullopt;
  }

  graph_path<WEIGHT_T> path;
  auto current = end_vertex;

  while (current != start_vertex) {
    path.vertices.push_front(current);
    current = vertex_info[current].prev_id;
  }

  path.vertices.push_front(start_vertex);
  path.total_weight = vertex_info[end_vertex].dist_from_start;
  return path;
}

}  // namespace detail

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> bfs_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  std::unordered_map<vertex_id_t, detail::path_vertex<WEIGHT_T>> vertex_info{
      {start_vertex, {start_vertex, 0, start_vertex}}};

  const auto callback{[&vertex_info](const edge_id_t& edge) {
    const auto [source, target]{edge};

    if (!vertex_info.contains(target)) {
      vertex_info[target] = {target, vertex_info[source].dist_from_start + 1,
                             source};
    }
  }};

  // We keep searching until we have reached the target vertex
  const auto search_termination_strategy{
      [end_vertex](const vertex_id_t vertex_id) {
        return vertex_id == end_vertex;
      }};

  breadth_first_traverse(graph, start_vertex, callback,
                         search_termination_strategy);

  return reconstruct_path(start_vertex, end_vertex, vertex_info);
}

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> dijkstra_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex,
    vertex_id_t end_vertex) {
  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  using dijkstra_queue_t =
      std::priority_queue<weighted_path_item, std::vector<weighted_path_item>,
                          std::greater<>>;
  dijkstra_queue_t to_explore{};
  std::unordered_map<vertex_id_t, weighted_path_item> vertex_info;

  vertex_info[start_vertex] = {start_vertex, 0, start_vertex};
  to_explore.push(vertex_info[start_vertex]);

  while (!to_explore.empty()) {
    auto current{to_explore.top()};
    to_explore.pop();

    if (current.id == end_vertex) {
      break;
    }

    for (const auto& neighbor : graph.get_neighbors(current.id)) {
      WEIGHT_T edge_weight = get_weight(graph.get_edge(current.id, neighbor));

      if (edge_weight < 0) {
        std::ostringstream error_msg;
        error_msg << "Negative edge weight [" << edge_weight
                  << "] between vertices [" << current.id << "] -> ["
                  << neighbor << "].";
        throw std::invalid_argument{error_msg.str()};
      }

      WEIGHT_T distance = current.dist_from_start + edge_weight;

      if (!vertex_info.contains(neighbor) ||
          distance < vertex_info[neighbor].dist_from_start) {
        vertex_info[neighbor] = {neighbor, distance, current.id};
        to_explore.push(vertex_info[neighbor]);
      }
    }
  }

  return reconstruct_path(start_vertex, end_vertex, vertex_info);
}

template <typename V, typename E, graph_type T, typename WEIGHT_T>
[[nodiscard]] std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
dijkstra_shortest_paths(const graph<V, E, T>& graph,
                        vertex_id_t source_vertex) {
  std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>> shortest_paths;

  using weighted_path_item = detail::path_vertex<WEIGHT_T>;
  using dijkstra_queue_t =
      std::priority_queue<weighted_path_item, std::vector<weighted_path_item>,
                          std::greater<>>;
  dijkstra_queue_t to_explore{};

  shortest_paths[source_vertex].total_weight = 0;
  shortest_paths[source_vertex].vertices.push_back(source_vertex);
  to_explore.push(weighted_path_item{source_vertex, 0});

  while (!to_explore.empty()) {
    auto current{to_explore.top()};
    to_explore.pop();

    if (shortest_paths.contains(current.id) &&
        current.dist_from_start > shortest_paths[current.id].total_weight) {
      continue;
    }

    for (const auto neighbor : graph.get_neighbors(current.id)) {
      WEIGHT_T edge_weight = get_weight(graph.get_edge(current.id, neighbor));

      if (edge_weight < 0) {
        std::ostringstream error_msg;
        error_msg << "Negative edge weight [" << edge_weight
                  << "] between vertices [" << current.id << "] -> ["
                  << neighbor << "].";
        throw std::invalid_argument{error_msg.str()};
      }

      WEIGHT_T distance = current.dist_from_start + edge_weight;

      if (!shortest_paths.contains(neighbor) ||
          distance < shortest_paths[neighbor].total_weight) {
        shortest_paths[neighbor].total_weight = distance;
        shortest_paths[neighbor].vertices = shortest_paths[current.id].vertices;
        shortest_paths[neighbor].vertices.push_back(neighbor);
        to_explore.push(weighted_path_item{neighbor, distance});
      }
    }
  }

  return shortest_paths;
}

template <typename V, typename E, graph_type T, typename WEIGHT_T>
std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
bellman_ford_shortest_paths(const graph<V, E, T>& graph,
                            vertex_id_t start_vertex) {
  std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>> shortest_paths;

  // Initialize the shortest path distances from the starting vertex to
  // "infinity" for all vertices
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    shortest_paths[vertex_id] = {{vertex_id},
                                 std::numeric_limits<WEIGHT_T>::max()};
  }

  // Set the distance from the starting vertex to itself to 0
  shortest_paths[start_vertex] = {{start_vertex}, 0};

  // Relax edges for |V| - 1 iterations
  for (std::size_t i = 1; i < graph.vertex_count(); ++i) {
    for (const auto& [edge_id, edge] : graph.get_edges()) {
      const auto [u, v]{edge_id};
      WEIGHT_T weight = get_weight(edge);

      if (shortest_paths[u].total_weight !=
              std::numeric_limits<WEIGHT_T>::max() &&
          shortest_paths[u].total_weight + weight <
              shortest_paths[v].total_weight) {
        // Update the shortest path to vertex v
        shortest_paths[v] = {
            {shortest_paths[u].vertices},
            shortest_paths[u].total_weight + weight,
        };
        shortest_paths[v].vertices.push_back(v);
      }
    }
  }
  // Negative cycle detection by doing an additional pass in the graph
  for (const auto& [edge_id, edge] : graph.get_edges()) {
    const auto [u, v]{edge_id};
    WEIGHT_T weight = get_weight(edge);
    if (shortest_paths[u].total_weight != std::numeric_limits<WEIGHT_T>::max() && shortest_paths[u].total_weight + weight < shortest_paths[v].total_weight) {
        std::ostringstream error_msg;
        error_msg << "Negative cycle detected in the graph.";
        throw std::invalid_argument{error_msg.str()};
    }
  }
  return shortest_paths;
}

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
  // For vertex n, prev_id in path_vertex is the vertex immediately preceding it
  // on the cheapest path from the start to n currently known.
  // The priority queue uses internally a binary heap.
  // To get the minimum element, we use the std::greater comparator.
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
        // This path to neighbor is better than any previous one, so we need to
        // update our data.
        // Update neighbor's g_score, f_score and previous vertex on the path
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