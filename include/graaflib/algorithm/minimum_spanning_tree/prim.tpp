#pragma once

#include <graaflib/types.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace graaf::algorithm {

namespace detail {

template <class GRAPH_T>
[[nodiscard]] std::vector<edge_id_t> find_candidate_edges(
    const GRAPH_T& graph,
    const std::unordered_set<vertex_id_t>& fringe_vertices) {
  std::vector<edge_id_t> candidates{};

  for (const auto fringe_vertex : fringe_vertices) {
    for (const auto neighbor : graph.get_neighbors(fringe_vertex)) {
      if (!fringe_vertices.contains(neighbor)) {
        candidates.emplace_back(fringe_vertex, neighbor);
      }
    }
  }

  return candidates;
}

};  // namespace detail

template <typename V, typename E>
std::optional<std::vector<edge_id_t>> prim_minimum_spanning_tree(
    const graph<V, E, graph_type::UNDIRECTED>& graph,
    vertex_id_t start_vertex) {
  std::vector<edge_id_t> edges_in_mst{};
  edges_in_mst.reserve(
      graph.edge_count());  // Reserve the upper bound of edges in the mst

  std::unordered_set<vertex_id_t> fringe_vertices{start_vertex};

  while (fringe_vertices.size() < graph.vertex_count()) {
    const auto candidates{detail::find_candidate_edges(graph, fringe_vertices)};

    if (candidates.empty()) {
      // The graph is not connected
      return std::nullopt;
    }

    const edge_id_t mst_edge{*std::ranges::min_element(
        candidates,
        [graph](const edge_id_t& lhs, const edge_id_t& rhs) -> bool {
          return get_weight(graph.get_edge(lhs)) <
                 get_weight(graph.get_edge(rhs));
        })};

    edges_in_mst.emplace_back(mst_edge);
    fringe_vertices.insert(mst_edge.second);
  }

  return edges_in_mst;
}

};  // namespace graaf::algorithm
