#pragma once

#include <graaflib/algorithm/maximum_flow/edmonds_karp.h>
#include <graaflib/algorithm/maximum_flow/residual_graph.h>
#include <graaflib/types.h>

#include <queue>
#include <unordered_map>

namespace graaf::algorithm {

// Helper function for the Edmonds-Karp algorithm to find augmenting paths using
// BFS.
template <typename V, typename E, typename WEIGHT_T>
[[nodiscard]] WEIGHT_T find_augmenting_path(
    residual_graph_adapter_t<V, E, WEIGHT_T>& residual_graph,
    vertex_id_t source, vertex_id_t sink,
    std::unordered_map<vertex_id_t, vertex_id_t>& parent) {
  // Create a queue for BFS traversal starting from the source vertex.
  std::queue<vertex_id_t> bfs_queue;
  bfs_queue.push(source);

  // Create a set to keep track of visited vertices.
  std::unordered_set<vertex_id_t> visited;
  visited.insert(source);

  // Create a map to store the parent vertex for each visited vertex.
  parent.clear();
  parent[source] = source;  // The source is its own parent.

  // Perform BFS to find an augmenting path.
  while (!bfs_queue.empty()) {
    vertex_id_t current = bfs_queue.front();
    bfs_queue.pop();

    // Iterate over the neighbors of the current vertex.
    for (const auto& neighbor : residual_graph.get_neighbors(current)) {
      // Check if the neighbor has not been visited and has residual capacity.
      if (!visited.count(neighbor) &&
          residual_graph.has_residual_capacity(current, neighbor)) {
        // Set the parent of the neighbor to the current vertex.
        parent[neighbor] = current;

        // Mark the neighbor as visited and add it to the BFS queue.
        visited.insert(neighbor);
        bfs_queue.push(neighbor);

        // If the neighbor is the sink vertex, we have found an augmenting path.
        if (neighbor == sink) {
          // Calculate the minimum residual capacity along the path (path_flow).
          WEIGHT_T path_flow = std::numeric_limits<WEIGHT_T>::max();
          vertex_id_t v = sink;
          while (v != source) {
            vertex_id_t u = parent[v];
            path_flow =
                std::min(path_flow, residual_graph.get_residual_capacity(u, v));
            v = u;
          }
          return path_flow;  // Return the maximum flow that can be added along
                             // this path.
        }
      }
    }
  }

  // No augmenting path found
  return 0;
}

// Edmonds-Karp algorithm for maximum flow
template <typename V, typename E, typename WEIGHT_T>
[[nodiscord]] WEIGHT_T edmonds_karp_max_flow(
    const graph<V, E, graph_type::DIRECTED>& graph, vertex_id_t source,
    vertex_id_t sink) {
  // Initialize flow and residual graph
  WEIGHT_T max_flow = WEIGHT_T(0);
  residual_graph_adapter_t<V, E, WEIGHT_T> residual_graph(graph);

  // Keep track of parent vertices for path reconstruction
  std::unordered_map<vertex_id_t, vertex_id_t> parent;
  WEIGHT_T path_flow;
  while ((path_flow =
              find_augmenting_path(residual_graph, source, sink, parent)) > 0) {
    max_flow += path_flow;

    // Update residual capacities along the augmenting path
    vertex_id_t v = sink;
    while (v != source) {
      vertex_id_t u = parent[v];
      residual_graph.update_residual_capacity(u, v, path_flow);
      residual_graph.update_residual_capacity(v, u,
                                              -path_flow);  // Reverse edge
      v = u;
    }
  }

  return max_flow;
}

}  // namespace graaf::algorithm