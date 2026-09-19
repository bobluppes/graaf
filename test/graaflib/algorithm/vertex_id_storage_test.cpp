#include <graaflib/algorithm/vertex_id_storage.h>
#include <gtest/gtest.h>

namespace graaf::algorithm::detail {

TEST(VertexIdSetTest, StartsEmpty) {
  vertex_id_set seen{};
  EXPECT_FALSE(seen.contains(0));
  EXPECT_FALSE(seen.contains(42));
}

TEST(VertexIdSetTest, InsertReturnsTrueOnlyOnFirstInsert) {
  vertex_id_set seen{};

  EXPECT_TRUE(seen.insert(3));
  EXPECT_TRUE(seen.contains(3));

  EXPECT_FALSE(seen.insert(3));
  EXPECT_TRUE(seen.contains(3));
}

TEST(VertexIdSetTest, InsertingALargeIdDoesNotMarkSmallerIdsAsSeen) {
  vertex_id_set seen{};

  ASSERT_TRUE(seen.insert(100));

  for (vertex_id_t id = 0; id < 100; ++id) {
    EXPECT_FALSE(seen.contains(id));
  }
  EXPECT_TRUE(seen.contains(100));
  EXPECT_FALSE(seen.contains(101));
}

TEST(VertexIdMapTest, ContainsIsFalseForUnaccessedId) {
  vertex_id_map<int> values{};
  EXPECT_FALSE(values.contains(0));
}

TEST(VertexIdMapTest, IndexOperatorDefaultConstructsAndPersists) {
  vertex_id_map<int> values{};

  EXPECT_EQ(values[5], 0);
  EXPECT_TRUE(values.contains(5));

  values[5] = 42;
  EXPECT_EQ(values[5], 42);
  EXPECT_EQ(values.at(5), 42);
}

TEST(VertexIdMapTest, AtThrowsForMissingId) {
  vertex_id_map<int> values{};
  values[2] = 10;

  ASSERT_THROW(values.at(7), std::out_of_range);

  const auto& const_values{values};
  ASSERT_THROW(const_values.at(7), std::out_of_range);
}

TEST(VertexIdMapTest, IndependentIdsDoNotInterfere) {
  vertex_id_map<int> values{};

  values[1] = 10;
  values[2] = 20;
  values[1000] = 30;

  EXPECT_EQ(values.at(1), 10);
  EXPECT_EQ(values.at(2), 20);
  EXPECT_EQ(values.at(1000), 30);
  EXPECT_FALSE(values.contains(3));
}

}  // namespace graaf::algorithm::detail
