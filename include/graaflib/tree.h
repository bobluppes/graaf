#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <memory>
#include <vector>

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
class tree {
 public:
  // fwd
  struct tree_node;
  struct child_link;

  explicit tree(VERTEX_T root_val)
      : root_{std::make_unique<tree_node>(std::move(root_val), nullptr,
                                          std::vector<child_link>{})} {}

  [[nodiscard]] tree_node* root() { return root_.get(); }
  [[nodiscard]] const tree_node* root() const { return root_.get(); }

  /**
   * Two trees are considered equal if they have the same shape: every node
   * has the same value, the same edge value towards its parent, and the same
   * set of children (order-independent). Parent back-pointers are internal
   * bookkeeping and are not part of a tree's identity, so they are ignored.
   */
  [[nodiscard]] bool operator==(const tree& other) const {
    return *root_ == *other.root_;
  }

  struct tree_node {
    // TODO(b.luppes): we are leaking implementation details regarding memory
    // management of children using std::unique_ptr. Consider providing a
    // non-owning view into the children.
    VERTEX_T value{};
    tree_node* parent{};  // raw pointer to break cyclic dependency
    std::vector<child_link> children{};

    [[nodiscard]] tree_node* add_child(EDGE_T edge_val, VERTEX_T child_val);

    [[nodiscard]] bool operator==(const tree_node& other) const;
  };

  struct child_link {
    EDGE_T value{};
    std::unique_ptr<tree_node> child{};
  };

 private:
  std::unique_ptr<tree_node> root_{};
};

/**
 * A collection of disjoint trees, e.g. the result of an algorithm which
 * operates on a graph which is not fully connected.
 */
template <typename VERTEX_T, typename EDGE_T>
using forest = std::vector<tree<VERTEX_T, EDGE_T>>;

}  // namespace graaf

#include "tree.tpp"
