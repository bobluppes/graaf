#include <graaflib/tree.h>
#include <gtest/gtest.h>

namespace graaf {

TEST(TreeTest, CanConstructWithRootNode) {
  // GIVEN
  using tree_t = tree<int, int>;
  constexpr const int ROOT_VAL{42};

  // WHEN
  const tree_t tree{ROOT_VAL};

  // THEN
  ASSERT_NE(tree.root(), nullptr);
  ASSERT_EQ(tree.root()->value, ROOT_VAL);
  ASSERT_EQ(tree.root()->parent, nullptr);
  ASSERT_EQ(tree.root()->children.size(), 0);
}

TEST(TreeTest, CanConstructWithChild) {
  // GIVEN
  using tree_t = tree<int, int>;
  constexpr const int EDGE_VAL{33};
  constexpr const int CHILD_VAL{42};

  tree_t tree{42};

  // WHEN
  const auto& child{tree.root()->add_child(EDGE_VAL, CHILD_VAL)};

  // THEN
  const auto& root{tree.root()};
  ASSERT_EQ(root->children.size(), 1);
  ASSERT_EQ(root->children.front().value, EDGE_VAL);
  ASSERT_EQ(root->children.front().child, child);

  ASSERT_EQ(child->value, CHILD_VAL);
  ASSERT_EQ(child->parent, root.get());
  ASSERT_EQ(child->children.size(), 0);
}

}  // namespace graaf
