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

}  // namespace graaf
