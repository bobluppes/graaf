#pragma once

#include <graaflib/algorithm/strongly_connected_components/tarjan.h>

#include <functional>  // For std::function
#include <stack>
#include <unordered_map>
#include <vector>

namespace graaf::algorithm {

template <typename V, typename E>
[[nodiscard]] sccs_t
tarjans_strongly_connected_components(
    const graph<V, E, graph_type::DIRECTED>& graph) {
  // Vector to store strongly connected components
  sccs_t sccs{};

  // Stack to hold vertices during traversal
  std::stack<vertex_id_t> stack;

  // Maps to keep track of indices, low-link values, and stack membership
  std::unordered_map<vertex_id_t, size_t> indices{};
  std::unordered_map<vertex_id_t, size_t> low_links{};
  std::unordered_map<vertex_id_t, bool> on_stack{};

  // Counter for indexing vertices
  size_t index_counter = 0;

  // Lambda function for the strong connect traversal
  std::function<void(vertex_id_t)> strong_connect;

  strong_connect = [&](vertex_id_t vertex) {
    // Set indices and low-link values for the current vertex
    indices[vertex] = index_counter;
    low_links[vertex] = index_counter;
    index_counter++;

    // Push the vertex onto the stack and mark it as on-stack
    stack.push(vertex);
    on_stack[vertex] = true;

    // Traverse neighbors
    for (const auto neighbor : graph.get_neighbors(vertex)) {
      if (!indices.contains(neighbor)) {
        // Neighbor has not yet been visited; recurse on it
        strong_connect(neighbor);
        low_links[vertex] = std::min(low_links[vertex], low_links[neighbor]);
      } else if (on_stack[neighbor]) {
        // Neighbor is in stack and hence in the current SCC
        low_links[vertex] = std::min(low_links[vertex], indices[neighbor]);
      }
    }

    // If low-link and index match, a strongly connected component is found
    if (low_links[vertex] == indices[vertex]) {
      std::vector<vertex_id_t> scc;
      vertex_id_t top;
      // Pop vertices from the stack to form the SCC
      do {
        top = stack.top();
        stack.pop();
        on_stack[top] = false;
        scc.push_back(top);  // Add to current strongly connected component
      } while (top != vertex);

      // Add the SCC to the list of SCCs
      sccs.push_back(scc);
    }
  };

  // Traverse all vertices to find SCCs
  for (const auto& [vertex_id, vertex] : graph.get_vertices()) {
    if (!indices.contains(vertex_id)) {
      strong_connect(vertex_id);
    }
  }

  return sccs;
}

}  // namespace graaf::algorithm