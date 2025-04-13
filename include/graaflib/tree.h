#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <memory>
#include <vector>

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
class tree {
 public:
  struct tree_node;
  using node_ptr_t = std::unique_ptr<tree_node>;

  struct child_link {
    EDGE_T value{};
    node_ptr_t child{};
  };

  struct tree_node {
    VERTEX_T value{};
    tree_node* parent{};  // raw pointer to break cyclic dependency
    std::vector<child_link> children{};

    [[nodiscard]] node_ptr_t& add_child(EDGE_T edge_val, VERTEX_T child_val);
  };

  explicit tree(VERTEX_T root_val)
      : root_{std::make_unique<tree_node>(std::move(root_val), nullptr,
                                          std::vector<child_link>{})} {}

  [[nodiscard]] node_ptr_t& root() { return root_; }
  [[nodiscard]] const node_ptr_t& root() const { return root_; }

 private:
  node_ptr_t root_{};
};

}  // namespace graaf

#include "tree.tpp"
