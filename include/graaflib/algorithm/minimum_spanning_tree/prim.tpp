#pragma once
#include <graaflib/types.h>

#include <queue>
#include <unordered_set>
#include <vector>

#include "prim.h"

namespace graaf::algorithm {

namespace detail {

template <typename WEIGHT_T>
struct prim_candidate_edge {
  vertex_id_t from;
  vertex_id_t to;
  WEIGHT_T weight;

  [[nodiscard]] bool operator>(const prim_candidate_edge<WEIGHT_T>& other) const {
    return weight > other.weight;
  }
};

};  // namespace detail

template <typename V, typename E, typename WEIGHT_T>
std::optional<std::vector<edge_id_t>> prim_minimum_spanning_tree(
    const graph<V, E, graph_type::UNDIRECTED>& graph,
    vertex_id_t start_vertex) {
  const auto vertex_count{graph.vertex_count()};

  std::vector<edge_id_t> edges_in_mst{};
  edges_in_mst.reserve(vertex_count > 0 ? vertex_count - 1 : 0);

  std::unordered_set<vertex_id_t> in_mst{start_vertex};

  using candidate_edge = detail::prim_candidate_edge<WEIGHT_T>;
  std::priority_queue<candidate_edge, std::vector<candidate_edge>,
                      std::greater<>>
      to_explore{};

  const auto push_edges_from{[&graph, &in_mst, &to_explore](vertex_id_t from) {
    for (const auto neighbor : graph.get_neighbors(from)) {
      if (!in_mst.contains(neighbor)) {
        to_explore.push(candidate_edge{
            from, neighbor, get_weight(graph.get_edge(from, neighbor))});
      }
    }
  }};

  push_edges_from(start_vertex);

  while (!to_explore.empty() && in_mst.size() < vertex_count) {
    const auto candidate{to_explore.top()};
    to_explore.pop();

    // The target vertex may already have been added to the tree via a
    // cheaper edge found later than this one - skip this stale entry rather
    // than removing it from the queue up front (lazy deletion).
    if (in_mst.contains(candidate.to)) {
      continue;
    }

    in_mst.insert(candidate.to);
    edges_in_mst.emplace_back(candidate.from, candidate.to);
    push_edges_from(candidate.to);
  }

  if (in_mst.size() < vertex_count) {
    // The graph is not connected
    return std::nullopt;
  }

  return edges_in_mst;
}

};  // namespace graaf::algorithm
