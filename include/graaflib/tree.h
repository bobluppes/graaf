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

  struct tree_node {
    // TODO(b.luppes): we are leaking implementation details regarding memory
    // management of children using std::unique_ptr. Consider providing a
    // non-owning view into the children.
    VERTEX_T value{};
    tree_node* parent{};  // raw pointer to break cyclic dependency
    std::vector<child_link> children{};

    [[nodiscard]] tree_node* add_child(EDGE_T edge_val, VERTEX_T child_val);
  };

  struct child_link {
    EDGE_T value{};
    std::unique_ptr<tree_node> child{};
  };

 private:
  std::unique_ptr<tree_node> root_{};
};

}  // namespace graaf

#include "tree.tpp"
