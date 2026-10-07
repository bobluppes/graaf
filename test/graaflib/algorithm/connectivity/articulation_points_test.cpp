#include <graaflib/algorithm/connectivity/articulation_points.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

#include <algorithm>

namespace graaf::algorithm {

template <typename T>
struct ArticulationPointsTest : public testing::Test {
  using graph_t = T;
};

TYPED_TEST_SUITE(ArticulationPointsTest,
                 utils::fixtures::minimal_undirected_graph_type);

// Empty graph: no articulation points.
TYPED_TEST(ArticulationPointsTest, EmptyGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // WHEN
  const auto result = articulation_points(graph);

  // THEN
  ASSERT_TRUE(result.empty());
}

// Single vertex: no articulation points.
TYPED_TEST(ArticulationPointsTest, SingleVertex) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  graph.add_vertex(0);

  // WHEN
  const auto result = articulation_points(graph);

  // THEN
  ASSERT_TRUE(result.empty());
}

// Two vertices connected by one edge: neither is an articulation point.
TYPED_TEST(ArticulationPointsTest, TwoVerticesWithEdge) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto v1{graph.add_vertex(0)};
  const auto v2{graph.add_vertex(1)};
  graph.add_edge(v1, v2, 1);

  // WHEN
  const auto result = articulation_points(graph);

  // THEN
  ASSERT_TRUE(result.empty());
}

// Cycle: no articulation points.
TYPED_TEST(ArticulationPointsTest, Cycle) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto v1{graph.add_vertex(0)};
  const auto v2{graph.add_vertex(1)};
  const auto v3{graph.add_vertex(2)};
  graph.add_edge(v1, v2, 1);
  graph.add_edge(v2, v3, 1);
  graph.add_edge(v3, v1, 1);

  // WHEN
  const auto result = articulation_points(graph);

  // THEN
  ASSERT_TRUE(result.empty());
}

// Star tree: the center is an articulation point, the leaves are not.
TYPED_TEST(ArticulationPointsTest, StarTree) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto center{graph.add_vertex(0)};
  const auto leaf1{graph.add_vertex(1)};
  const auto leaf2{graph.add_vertex(2)};
  const auto leaf3{graph.add_vertex(3)};
  graph.add_edge(center, leaf1, 1);
  graph.add_edge(center, leaf2, 1);
  graph.add_edge(center, leaf3, 1);

  // WHEN
  const auto result = articulation_points(graph);

  // THEN
  const std::vector<vertex_id_t> expected{center};
  ASSERT_EQ(result, expected);
}

// Linear chain 0-1-2: the middle vertex is an articulation point.
TYPED_TEST(ArticulationPointsTest, LinearChain) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto v1{graph.add_vertex(0)};
  const auto v2{graph.add_vertex(1)};
  const auto v3{graph.add_vertex(2)};
  graph.add_edge(v1, v2, 1);
  graph.add_edge(v2, v3, 1);

  // WHEN
  const auto result = articulation_points(graph);

  // THEN
  const std::vector<vertex_id_t> expected{v2};
  ASSERT_EQ(result, expected);
}

// Disconnected graph: each connected component is evaluated independently.
TYPED_TEST(ArticulationPointsTest, DisconnectedGraph) {
  // GIVEN
  // Component 1: chain 0-1-2, vertex 1 is an articulation point.
  // Component 2: edge 3-4, no articulation points.
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto v0{graph.add_vertex(0)};
  const auto v1{graph.add_vertex(1)};
  const auto v2{graph.add_vertex(2)};
  const auto v3{graph.add_vertex(3)};
  const auto v4{graph.add_vertex(4)};
  graph.add_edge(v0, v1, 1);
  graph.add_edge(v1, v2, 1);
  graph.add_edge(v3, v4, 1);

  // WHEN
  const auto result = articulation_points(graph);

  // THEN
  const std::vector<vertex_id_t> expected{v1};
  ASSERT_EQ(result, expected);
}

}  // namespace graaf::algorithm