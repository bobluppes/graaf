#pragma once

#include <algorithm>
#include <tuple>

#include "tree.h"

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
tree<VERTEX_T, EDGE_T>::tree_node* tree<VERTEX_T, EDGE_T>::tree_node::add_child(
    EDGE_T edge_val, VERTEX_T child_val) {
  auto child{std::make_unique<tree_node>(std::move(child_val), this,
                                         std::vector<child_link>{})};
  children.emplace_back(std::move(edge_val), std::move(child));
  return children.back().child.get();
}

template <typename VERTEX_T, typename EDGE_T>
bool tree<VERTEX_T, EDGE_T>::tree_node::operator==(
    const tree_node& other) const {
  // Two nodes are equal if they hold the same value and have the same
  // (order-independent) set of descendants, connected by the same edge
  // values. We check this by flattening each side into its list of
  // (parent, edge, child) triples and comparing them as sorted, unordered
  // collections - add_child order can differ between two otherwise-identical
  // trees (e.g. depending on iteration order of the graph the tree was built
  // from), so we can't compare children pairwise by position.
  //
  // Flattening only visits each node once via an explicit worklist (no
  // recursion, so no risk of overflowing the call stack on a deep tree, e.g.
  // the tree produced by running Prim's MST on a long path-shaped graph),
  // and it relies on vertex values being unique within a tree - true for any
  // tree built from a graph traversal, since a vertex is visited at most
  // once. Two nodes at different positions sharing the same value would
  // otherwise not be distinguishable from one another once flattened.
  if (!(value == other.value)) {
    return false;
  }

  const auto flatten{[](const tree_node& root) {
    std::vector<std::tuple<VERTEX_T, EDGE_T, VERTEX_T>> edges{};
    std::vector<const tree_node*> to_visit{&root};

    while (!to_visit.empty()) {
      const auto* current{to_visit.back()};
      to_visit.pop_back();

      for (const auto& link : current->children) {
        edges.emplace_back(current->value, link.value, link.child->value);
        to_visit.push_back(link.child.get());
      }
    }

    std::ranges::sort(edges);
    return edges;
  }};

  return flatten(*this) == flatten(other);
}

}  // namespace graaf
