#pragma once
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <stack>
#include <vector>

#include "vertex_properties.h"

namespace graaf::properties {

template <typename V, typename E, graph_type T>
std::size_t vertex_degree(const graaf::graph<V, E, T>& graph,
                          vertex_id_t vertex_id) {
  if constexpr (T == graph_type::DIRECTED) {
    return vertex_outdegree(graph, vertex_id) +
           vertex_indegree(graph, vertex_id);
  }

  if constexpr (T == graph_type::UNDIRECTED) {
    return vertex_outdegree(graph, vertex_id);
  }

  // Should never reach this
  std::abort();
}

template <typename V, typename E, graph_type T>
std::size_t vertex_outdegree(const graaf::graph<V, E, T>& graph,
                             vertex_id_t vertex_id) {
  const auto& neighbors{graph.get_neighbors(vertex_id)};

  if constexpr (T == graph_type::UNDIRECTED) {
    // A self-loop is stored once in the neighbor list, but conventionally
    // contributes two to the degree of a vertex in an undirected graph.
    return neighbors.size() +
           (std::ranges::find(neighbors, vertex_id) != neighbors.end() ? 1 : 0);
  }

  return neighbors.size();
}

template <typename V, typename E, graph_type T>
std::size_t vertex_indegree(const graaf::graph<V, E, T>& graph,
                            vertex_id_t vertex_id) {
  if constexpr (T == graph_type::DIRECTED) {
    return std::ranges::count_if(
        graph.get_vertices(), [&graph, vertex_id](const auto& kv_pair) {
          const auto& [current_vertex_id, _]{kv_pair};
          const auto& neighbors{graph.get_neighbors(current_vertex_id)};
          return std::ranges::find(neighbors, vertex_id) != neighbors.end();
        });
  }

  if constexpr (T == graph_type::UNDIRECTED) {
    // For an undirected graph, the indegree of a vertex is equal to the
    // outdegree
    return vertex_outdegree(graph, vertex_id);
  }

  // Should never reach this
  std::abort();
}

template <typename V, typename E, graph_type T>
std::unordered_map<vertex_id_t, double> betweenness_centrality(
    const graph<V, E, T>& graph) {
  std::unordered_map<vertex_id_t, double> centrality{};

  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    centrality[vertex_id] = 0.0;
  }

  for (const auto& [source_vertex, _] : graph.get_vertices()) {
    std::unordered_map<vertex_id_t, std::vector<vertex_id_t>> predecessors{};
    std::unordered_map<vertex_id_t, std::size_t> distance{};
    std::unordered_map<vertex_id_t, std::size_t> path_count{};
    std::unordered_map<vertex_id_t, double> dependency{};
    std::queue<vertex_id_t> bfsQueue{};
    std::stack<vertex_id_t> bfsStack{};

    distance[source_vertex] = 0;
    path_count[source_vertex] = 1;
    bfsQueue.push(source_vertex);

    while (!bfsQueue.empty()) {
      const vertex_id_t current_vertex{bfsQueue.front()};
      bfsQueue.pop();
      bfsStack.push(current_vertex);
      for (const vertex_id_t neighbor : graph.get_neighbors(current_vertex)) {
        if (distance.find(neighbor) == distance.end()) {
          distance[neighbor] = distance[current_vertex] + 1;
          path_count[neighbor] = 0;
          bfsQueue.push(neighbor);
        }
        if (distance[neighbor] == distance[current_vertex] + 1) {
          path_count[neighbor] += path_count[current_vertex];
          predecessors[neighbor].push_back(current_vertex);
        }
      }
    }

    while (!bfsStack.empty()) {
      const vertex_id_t current_vertex{bfsStack.top()};
      bfsStack.pop();
      for (const vertex_id_t predecessor : predecessors[current_vertex]) {
        dependency[predecessor] +=
            (static_cast<double>(path_count[predecessor]) /
             static_cast<double>(path_count[current_vertex])) *
            (1.0 + dependency[current_vertex]);
      }
      if (current_vertex != source_vertex) {
        centrality[current_vertex] += dependency[current_vertex];
      }
    }
  }

  if constexpr (T == graph_type::UNDIRECTED) {
    for (auto& [_, value] : centrality) {
      value /= 2.0;
    }
  }
  return centrality;
}

template <typename V, typename E, graph_type T>
std::unordered_map<vertex_id_t, double> closeness_centrality(
    const graph<V, E, T>& graph) {
  std::unordered_map<vertex_id_t, double> result{};

  if (graph.vertex_count() == 0) {
    return result;
  }

  for (const auto& [source_vertex, _] : graph.get_vertices()) {
    std::unordered_map<vertex_id_t, std::size_t> distance{};
    std::queue<vertex_id_t> vertices_to_visit{};

    vertices_to_visit.push(source_vertex);
    distance[source_vertex] = 0;

    while (!vertices_to_visit.empty()) {
      const vertex_id_t current_vertex{vertices_to_visit.front()};
      vertices_to_visit.pop();
      for (const vertex_id_t neighbor : graph.get_neighbors(current_vertex)) {
        if (distance.find(neighbor) == distance.end()) {
          distance[neighbor] = distance[current_vertex] + 1;
          vertices_to_visit.push(neighbor);
        }
      }
    }
    double sum_of_distances = 0.0;
    for (const auto& [vertex, dist] : distance) {
      if (vertex != source_vertex) {
        sum_of_distances += dist;
      }
    }
    if (sum_of_distances == 0.0) {
      result[source_vertex] = 0.0;
    } else {
      result[source_vertex] = 1.0 / sum_of_distances;
    }
  }
  return result;
}

}  // namespace graaf::properties
