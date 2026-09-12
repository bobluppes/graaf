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
  const auto* child{tree.root()->add_child(EDGE_VAL, CHILD_VAL)};

  // THEN
  const auto* root{tree.root()};
  ASSERT_EQ(root->children.size(), 1);
  ASSERT_EQ(root->children.front().value, EDGE_VAL);
  ASSERT_EQ(root->children.front().child.get(), child);

  ASSERT_EQ(child->value, CHILD_VAL);
  ASSERT_EQ(child->parent, root);
  ASSERT_EQ(child->children.size(), 0);
}

TEST(TreeTest, EqualSingleNodeTreesAreEqual) {
  // GIVEN
  using tree_t = tree<int, int>;

  // WHEN / THEN
  ASSERT_TRUE(tree_t{42} == tree_t{42});
}

TEST(TreeTest, SingleNodeTreesWithDifferentValuesAreNotEqual) {
  // GIVEN
  using tree_t = tree<int, int>;

  // WHEN / THEN
  ASSERT_FALSE(tree_t{42} == tree_t{1337});
}

TEST(TreeTest, TreesWithDifferentNumberOfChildrenAreNotEqual) {
  // GIVEN
  using tree_t = tree<int, int>;

  tree_t lhs{1};
  static_cast<void>(lhs.root()->add_child(10, 2));

  tree_t rhs{1};
  static_cast<void>(rhs.root()->add_child(10, 2));
  static_cast<void>(rhs.root()->add_child(20, 3));

  // WHEN / THEN
  ASSERT_FALSE(lhs == rhs);
}

TEST(TreeTest, TreesWithDifferentEdgeValuesAreNotEqual) {
  // GIVEN
  using tree_t = tree<int, int>;

  tree_t lhs{1};
  static_cast<void>(lhs.root()->add_child(10, 2));

  tree_t rhs{1};
  static_cast<void>(rhs.root()->add_child(99, 2));

  // WHEN / THEN
  ASSERT_FALSE(lhs == rhs);
}

TEST(TreeTest, TreesWithChildrenAddedInDifferentOrderAreEqual) {
  // GIVEN - Equality does not depend on the order children were added in
  using tree_t = tree<int, int>;

  tree_t lhs{1};
  static_cast<void>(lhs.root()->add_child(10, 2));
  static_cast<void>(lhs.root()->add_child(20, 3));

  tree_t rhs{1};
  static_cast<void>(rhs.root()->add_child(20, 3));
  static_cast<void>(rhs.root()->add_child(10, 2));

  // WHEN / THEN
  ASSERT_TRUE(lhs == rhs);
}

TEST(TreeTest, TreesDifferingDeepInTheHierarchyAreNotEqual) {
  // GIVEN
  using tree_t = tree<int, int>;

  tree_t lhs{1};
  auto* lhs_child{lhs.root()->add_child(10, 2)};
  static_cast<void>(lhs_child->add_child(100, 4));

  tree_t rhs{1};
  auto* rhs_child{rhs.root()->add_child(10, 2)};
  static_cast<void>(rhs_child->add_child(200, 4));

  // WHEN / THEN
  ASSERT_FALSE(lhs == rhs);
}

TEST(TreeTest, DeeplyNestedIdenticalTreesAreEqual) {
  // GIVEN
  using tree_t = tree<int, int>;

  tree_t lhs{1};
  auto* lhs_child{lhs.root()->add_child(10, 2)};
  static_cast<void>(lhs_child->add_child(100, 4));

  tree_t rhs{1};
  auto* rhs_child{rhs.root()->add_child(10, 2)};
  static_cast<void>(rhs_child->add_child(100, 4));

  // WHEN / THEN
  ASSERT_TRUE(lhs == rhs);
}

TEST(TreeTest, ForestIsACollectionOfTrees) {
  // GIVEN
  using tree_t = tree<int, int>;
  using forest_t = forest<int, int>;

  // WHEN
  forest_t forest{};
  forest.push_back(tree_t{1});
  forest.push_back(tree_t{2});

  // THEN
  ASSERT_EQ(forest.size(), 2);
  ASSERT_EQ(forest[0].root()->value, 1);
  ASSERT_EQ(forest[1].root()->value, 2);
}

}  // namespace graaf
