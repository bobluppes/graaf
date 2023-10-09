#pragma once

#include <graaflib/algorithm/graph_traversal/depth_first_search.h>
#include <graaflib/algorithm/strongly_connected_components/kosaraju.h>
#include <graaflib/algorithm/utils.h>

#include <iostream>
#include <stack>

namespace graaf::algorithm {

template <typename V, typename E>
std::vector<std::vector<vertex_id_t>> kosarajus_strongly_connected_components(
    const directed_graph<V, E>& graph) {
  std::vector<std::vector<vertex_id_t>> sccs;

  if (graph.get_vertices().size() == 0) {
    return sccs;
  }

  std::stack<vertex_id_t> stack;
  std::unordered_set<vertex_id_t> seen_vertices;

  std::function<void(vertex_id_t)> visit_vertex;
  visit_vertex = [&](vertex_id_t vertex) {
    if (!seen_vertices.contains(vertex)) {
      stack.push(vertex);
      seen_vertices.insert(vertex);

      for (const auto neighbour : graph.get_neighbors(vertex)) {
        visit_vertex(neighbour);
      }
    }
  };

  for (const auto& [vertex_id, vertex] : graph.get_vertices()) {
    if (!seen_vertices.contains(vertex_id)) {
      visit_vertex(vertex_id);
    }
  }

  seen_vertices.clear();

  directed_graph<V, E> transposed_graph = get_transposed_graph(graph);
  std::vector<vertex_id_t> scc;

  std::function<void(vertex_id_t)> strong_connect;
  strong_connect = [&](vertex_id_t vertex) {
    if (!seen_vertices.contains(vertex)) {
      seen_vertices.insert(vertex);
      scc.push_back(vertex);

      for (const auto neighbour : transposed_graph.get_neighbors(vertex)) {
        strong_connect(neighbour);
      }
    }
  };

  while (!stack.empty()) {
    if (!seen_vertices.contains(stack.top())) {
      scc.clear();
      strong_connect(stack.top());
      sccs.push_back(scc);
    }

    stack.pop();
  }

  return sccs;
}

}  // namespace graaf::algorithm
