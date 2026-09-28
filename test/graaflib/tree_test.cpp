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

TEST(TreeTest, TotalWeightOfRootOnlyTreeIsZero) {
  // GIVEN
  using tree_t = tree<int, int>;
  tree_t tree{42};

  // WHEN / THEN
  ASSERT_EQ(tree.total_weight(), 0);
}

TEST(TreeTest, TotalWeightSumsAllEdgeValues) {
  // GIVEN
  // clang-format off
  //       42
  //     /    \
  //   100    200
  //   /       /  \
  // 300      400  500
  // clang-format on
  using tree_t = tree<int, int>;
  tree_t tree{42};
  auto* child_1{tree.root()->add_child(100, 1)};
  auto* child_2{tree.root()->add_child(200, 2)};
  [[maybe_unused]] auto* child_3{child_1->add_child(300, 3)};
  [[maybe_unused]] auto* child_4{child_2->add_child(400, 4)};
  [[maybe_unused]] auto* child_5{child_2->add_child(500, 5)};

  // WHEN / THEN
  ASSERT_EQ(tree.total_weight(), 100 + 200 + 300 + 400 + 500);
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
