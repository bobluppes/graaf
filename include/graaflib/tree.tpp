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
  // Two nodes are equal if they hold the same value and have the same
  // (order-independent) set of children, recursively. Children are matched
  // as an unordered collection: add_child order can differ between two
  // otherwise-identical trees (e.g. depending on iteration order of the
  // graph the tree was built from), so we match each of a node's children
  // against a not-yet-matched child of the other node, rather than comparing
  // children.at(i) pairwise.
  //
  // This is implemented iteratively, with an explicit heap-allocated stack
  // of comparison frames, rather than via direct recursion on
  // `*link.child == *other_link.child`. A plain recursive implementation
  // would use one call-stack frame per level of tree depth, which overflows
  // the (much smaller, fixed-size) call stack for deep trees - e.g. the tree
  // produced by running Prim's MST on a long path-shaped graph.
  struct frame {
    const tree_node* lhs;
    const tree_node* rhs;
    std::vector<bool> rhs_matched{};
    std::size_t lhs_child_idx{0};
    std::size_t rhs_candidate_idx{0};
    bool initialized{false};
  };

  std::vector<frame> stack{};
  stack.push_back(frame{this, &other});

  bool have_child_result{false};
  bool child_result{false};

  while (!stack.empty()) {
    frame& current{stack.back()};

    if (!current.initialized) {
      current.initialized = true;
      if (!(current.lhs->value == current.rhs->value) ||
          current.lhs->children.size() != current.rhs->children.size()) {
        child_result = false;
        have_child_result = true;
        stack.pop_back();
        continue;
      }
      current.rhs_matched.assign(current.rhs->children.size(), false);
    }

    if (have_child_result) {
      if (child_result) {
        current.rhs_matched[current.rhs_candidate_idx] = true;
        ++current.lhs_child_idx;
        current.rhs_candidate_idx = 0;
      } else {
        ++current.rhs_candidate_idx;
      }
      have_child_result = false;
    }

    if (current.lhs_child_idx >= current.lhs->children.size()) {
      // All of this node's children were matched against a child of other.
      child_result = true;
      have_child_result = true;
      stack.pop_back();
      continue;
    }

    bool found_candidate{false};
    while (current.rhs_candidate_idx < current.rhs_matched.size()) {
      if (!current.rhs_matched[current.rhs_candidate_idx] &&
          current.lhs->children[current.lhs_child_idx].value ==
              current.rhs->children[current.rhs_candidate_idx].value) {
        found_candidate = true;
        break;
      }
      ++current.rhs_candidate_idx;
    }

    if (!found_candidate) {
      child_result = false;
      have_child_result = true;
      stack.pop_back();
      continue;
    }

    stack.push_back(
        frame{current.lhs->children[current.lhs_child_idx].child.get(),
              current.rhs->children[current.rhs_candidate_idx].child.get()});
  }

  return child_result;
}

}  // namespace graaf
