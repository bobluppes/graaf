#pragma once
#include <graaflib/types.h>

#include <queue>
#include <vector>

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

  using tree_node_t = typename tree<vertex_id_t, WEIGHT_T>::tree_node;

  // Indexed directly by vertex_id_t rather than an unordered_map: doubles as
  // the "is this vertex in the MST yet" membership check via a null entry,
  // and grows lazily as vertices are added to the tree. vertices_in_tree
  // tracks the count separately, since a null-filled vector slot isn't the
  // same as an absent unordered_map entry for sizing purposes.
  std::vector<tree_node_t*> tree_node_for_vertex{};
  std::size_t vertices_in_tree{0};

  const auto in_tree{[&](vertex_id_t id) {
    return id < tree_node_for_vertex.size() &&
           tree_node_for_vertex[id] != nullptr;
  }};

  const auto add_to_tree{[&](vertex_id_t id, tree_node_t* node) {
    if (id >= tree_node_for_vertex.size()) {
      tree_node_for_vertex.resize(id + 1, nullptr);
    }
    tree_node_for_vertex[id] = node;
    ++vertices_in_tree;
  }};

  add_to_tree(start_vertex, mst_tree.root());

  using candidate_edge = detail::prim_candidate_edge<WEIGHT_T>;
  std::priority_queue<candidate_edge, std::vector<candidate_edge>,
                      std::greater<>>
      to_explore{};

  const auto push_edges_from{[&graph, &in_tree, &to_explore](vertex_id_t from) {
    for (const auto neighbor : graph.get_neighbors(from)) {
      if (!in_tree(neighbor)) {
        to_explore.push(candidate_edge{
            from, neighbor, get_weight(graph.get_edge(from, neighbor))});
      }
    }
  }};

  push_edges_from(start_vertex);

  while (!to_explore.empty() && vertices_in_tree < vertex_count) {
    const auto candidate{to_explore.top()};
    to_explore.pop();

    // The target vertex may already have been added to the tree via a
    // cheaper edge found later than this one - skip this stale entry rather
    // than removing it from the queue up front (lazy deletion).
    if (in_tree(candidate.to)) {
      continue;
    }

    auto* parent_node{tree_node_for_vertex[candidate.from]};
    auto* child_node{parent_node->add_child(candidate.weight, candidate.to)};
    add_to_tree(candidate.to, child_node);

    push_edges_from(candidate.to);
  }

  if (vertices_in_tree < vertex_count) {
    // The graph is not connected
    return std::nullopt;
  }

  return mst_tree;
}

};  // namespace graaf::algorithm
