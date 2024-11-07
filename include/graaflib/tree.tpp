#pragma once

#include "tree.h"

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
tree<VERTEX_T, EDGE_T>::node_ptr_t& tree<VERTEX_T, EDGE_T>::add_child(
    node_ptr_t& parent, EDGE_T edge_val, VERTEX_T child_val) {
  auto child{std::make_unique<tree_node>(std::move(child_val), parent.get(),
                                         std::vector<child_link>{})};
  parent->children.emplace_back(std::move(edge_val), std::move(child));
  return parent->children.back().child;
}

}  // namespace graaf
