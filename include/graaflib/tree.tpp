#pragma once

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
EDGE_T tree<VERTEX_T, EDGE_T>::total_weight() const {
  return accumulate_weight(root_.get());
}

template <typename VERTEX_T, typename EDGE_T>
EDGE_T tree<VERTEX_T, EDGE_T>::accumulate_weight(const tree_node* node) {
  EDGE_T total{};
  for (const auto& link : node->children) {
    total += link.value + accumulate_weight(link.child.get());
  }
  return total;
}

}  // namespace graaf
