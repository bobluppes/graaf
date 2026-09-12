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
bool tree<VERTEX_T, EDGE_T>::tree_node::operator==(
    const tree_node& other) const {
  if (!(value == other.value) || children.size() != other.children.size()) {
    return false;
  }

  // Children are compared as an unordered collection: add_child order can
  // differ between two otherwise-identical trees (e.g. depending on
  // iteration order of the graph the tree was built from), so we match each
  // of our children against a not-yet-matched child of `other` rather than
  // comparing children.at(i) pairwise.
  std::vector<bool> other_child_matched(other.children.size(), false);
  for (const auto& link : children) {
    bool found_match{false};
    for (std::size_t i{0}; i < other.children.size(); ++i) {
      if (other_child_matched[i]) {
        continue;
      }

      const auto& other_link{other.children[i]};
      if (link.value == other_link.value && *link.child == *other_link.child) {
        other_child_matched[i] = true;
        found_match = true;
        break;
      }
    }

    if (!found_match) {
      return false;
    }
  }

  return true;
}

}  // namespace graaf
