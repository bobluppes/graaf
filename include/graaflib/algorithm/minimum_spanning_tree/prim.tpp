#pragma once
#include <graaflib/types.h>

#include <queue>
#include <unordered_map>

#include "prim.h"

namespace graaf::algorithm {

namespace detail {

template <typename WEIGHT_T>
struct prim_candidate_edge {
  vertex_id_t from;
  vertex_id_t to;
  WEIGHT_T weight;

  [[nodiscard]] bool operator>(
      const prim_candidate_edge<WEIGHT_T>& other) const {
    return weight > other.weight;
  }
};

};  // namespace detail

template <typename V, typename E, typename WEIGHT_T>
std::optional<tree<vertex_id_t, WEIGHT_T>> prim_minimum_spanning_tree(
    const graph<V, E, graph_type::UNDIRECTED>& graph,
    vertex_id_t start_vertex) {
  const auto vertex_count{graph.vertex_count()};

  tree<vertex_id_t, WEIGHT_T> mst_tree{start_vertex};

  // Doubles as the "is this vertex in the MST yet" membership check: a
  // vertex has been added to the tree if and only if it has an entry here.
  using tree_node_t = typename tree<vertex_id_t, WEIGHT_T>::tree_node;
  std::unordered_map<vertex_id_t, tree_node_t*> tree_node_for_vertex{
      {start_vertex, mst_tree.root()}};

  using candidate_edge = detail::prim_candidate_edge<WEIGHT_T>;
  std::priority_queue<candidate_edge, std::vector<candidate_edge>,
                      std::greater<>>
      to_explore{};

  const auto push_edges_from{
      [&graph, &tree_node_for_vertex, &to_explore](vertex_id_t from) {
        for (const auto neighbor : graph.get_neighbors(from)) {
          if (!tree_node_for_vertex.contains(neighbor)) {
            to_explore.push(candidate_edge{
                from, neighbor, get_weight(graph.get_edge(from, neighbor))});
          }
        }
      }};

  push_edges_from(start_vertex);

  while (!to_explore.empty() && tree_node_for_vertex.size() < vertex_count) {
    const auto candidate{to_explore.top()};
    to_explore.pop();

    // The target vertex may already have been added to the tree via a
    // cheaper edge found later than this one - skip this stale entry rather
    // than removing it from the queue up front (lazy deletion).
    if (tree_node_for_vertex.contains(candidate.to)) {
      continue;
    }

    auto* parent_node{tree_node_for_vertex.at(candidate.from)};
    auto* child_node{parent_node->add_child(candidate.weight, candidate.to)};
    tree_node_for_vertex.emplace(candidate.to, child_node);

    push_edges_from(candidate.to);
  }

  if (tree_node_for_vertex.size() < vertex_count) {
    // The graph is not connected
    return std::nullopt;
  }

  return mst_tree;
}

};  // namespace graaf::algorithm
