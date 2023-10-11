#pragma once

#include <graaflib/algorithm/graph_traversal/depth_first_search.h>
#include <graaflib/algorithm/strongly_connected_components/kosaraju.h>
#include <graaflib/algorithm/utils.h>

#include <iostream>
#include <stack>

namespace graaf::algorithm {

namespace {

template <typename V, typename E>
void do_visit_vertex(const vertex_id_t vertex_id,
                     const directed_graph<V, E>& graph,
                     std::stack<vertex_id_t>& stack,
                     std::unordered_set<vertex_id_t>& seen_vertices) {
  if (!seen_vertices.contains(vertex_id)) {
    seen_vertices.insert(vertex_id);
    for (const auto neighbour : graph.get_neighbors(vertex_id)) {
      do_visit_vertex(neighbour, graph, stack, seen_vertices);
    }
    stack.push(vertex_id);
  }
}

template <typename V, typename E>
void make_strongly_connected_component_from_vertex(
    const vertex_id_t vertex, const directed_graph<V, E>& transposed_graph,
    std::vector<vertex_id_t>& scc,
    std::unordered_set<vertex_id_t>& seen_vertices) {
  if (!seen_vertices.contains(vertex)) {
    seen_vertices.insert(vertex);
    scc.push_back(vertex);

    for (const auto neighbour : transposed_graph.get_neighbors(vertex)) {
      make_strongly_connected_component_from_vertex(neighbour, transposed_graph,
                                                    scc, seen_vertices);
    }
  }
}

}  // namespace

template <typename V, typename E>
sccs_t kosarajus_strongly_connected_components(
    const directed_graph<V, E>& graph) {
  sccs_t sccs{};

  if (graph.get_vertices().size() == 0) {
    return sccs;
  }

  std::stack<vertex_id_t> stack{};
  std::unordered_set<vertex_id_t> seen_vertices{};

  for (const auto& [vertex_id, vertex] : graph.get_vertices()) {
    if (!seen_vertices.contains(vertex_id)) {
      do_visit_vertex(vertex_id, graph, stack, seen_vertices);
    }
  }

  seen_vertices.clear();

  const auto transposed_graph = get_transposed_graph(graph);
  std::vector<vertex_id_t> scc{};

  while (!stack.empty()) {
    if (!seen_vertices.contains(stack.top())) {
      scc.clear();
      make_strongly_connected_component_from_vertex(
          stack.top(), transposed_graph, scc, seen_vertices);
      sccs.push_back(scc);
    }

    stack.pop();
  }

  return sccs;
}

}  // namespace graaf::algorithm
