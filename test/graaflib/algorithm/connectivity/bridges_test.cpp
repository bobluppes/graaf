#include <graaflib/algorithm/connectivity/bridges.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

#include <algorithm>

namespace graaf::algorithm {

template <typename T>
struct BridgesTest : public testing::Test {
  using graph_t = T;
};

TYPED_TEST_SUITE(BridgesTest,
                 utils::fixtures::minimal_undirected_graph_type);

// Empty graph: no bridges.
TYPED_TEST(BridgesTest, EmptyGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // WHEN
  const auto result = bridges(graph);

  // THEN
  ASSERT_TRUE(result.empty());
}

// Single vertex: no bridges.
TYPED_TEST(BridgesTest, SingleVertex) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  graph.add_vertex(0);

  // WHEN
  const auto result = bridges(graph);

  // THEN
  ASSERT_TRUE(result.empty());
}

// Two vertices connected by one edge: the edge is a bridge.
TYPED_TEST(BridgesTest, TwoVerticesWithEdge) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto v1{graph.add_vertex(0)};
  const auto v2{graph.add_vertex(1)};
  graph.add_edge(v1, v2, 1);

  // WHEN
  const auto result = bridges(graph);

  // THEN
  const bridges_t expected{{v1, v2}};
  ASSERT_EQ(result, expected);
}

// Cycle: no bridges.
TYPED_TEST(BridgesTest, Cycle) {
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
  const auto result = bridges(graph);

  // THEN
  ASSERT_TRUE(result.empty());
}

// Star tree: every edge is a bridge.
TYPED_TEST(BridgesTest, StarTree) {
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
  const auto result = bridges(graph);

  // THEN
  const bridges_t expected{{center, leaf1}, {center, leaf2}, {center, leaf3}};
  ASSERT_EQ(result, expected);
}

// Linear chain 0-1-2: every edge is a bridge.
TYPED_TEST(BridgesTest, LinearChain) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto v1{graph.add_vertex(0)};
  const auto v2{graph.add_vertex(1)};
  const auto v3{graph.add_vertex(2)};
  graph.add_edge(v1, v2, 1);
  graph.add_edge(v2, v3, 1);

  // WHEN
  const auto result = bridges(graph);

  // THEN
  const bridges_t expected{{v1, v2}, {v2, v3}};
  ASSERT_EQ(result, expected);
}

// Graph with a cycle and a pendant edge: only the pendant edge is a bridge.
TYPED_TEST(BridgesTest, CycleWithPendantEdge) {
  // GIVEN
  // Triangle 0-1-2, plus pendant vertex 3 attached to 1 via edge 1-3.
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto v0{graph.add_vertex(0)};
  const auto v1{graph.add_vertex(1)};
  const auto v2{graph.add_vertex(2)};
  const auto v3{graph.add_vertex(3)};
  graph.add_edge(v0, v1, 1);
  graph.add_edge(v1, v2, 1);
  graph.add_edge(v2, v0, 1);
  graph.add_edge(v1, v3, 1);

  // WHEN
  const auto result = bridges(graph);

  // THEN
  const bridges_t expected{{v1, v3}};
  ASSERT_EQ(result, expected);
}

// Disconnected graph: each connected component is evaluated independently.
TYPED_TEST(BridgesTest, DisconnectedGraph) {
  // GIVEN
  // Component 1: chain 0-1-2, both edges are bridges.
  // Component 2: cycle 3-4-5, no bridges.
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto v0{graph.add_vertex(0)};
  const auto v1{graph.add_vertex(1)};
  const auto v2{graph.add_vertex(2)};
  const auto v3{graph.add_vertex(3)};
  const auto v4{graph.add_vertex(4)};
  const auto v5{graph.add_vertex(5)};
  graph.add_edge(v0, v1, 1);
  graph.add_edge(v1, v2, 1);
  graph.add_edge(v3, v4, 1);
  graph.add_edge(v4, v5, 1);
  graph.add_edge(v5, v3, 1);

  // WHEN
  const auto result = bridges(graph);

  // THEN
  const bridges_t expected{{v0, v1}, {v1, v2}};
  ASSERT_EQ(result, expected);
}

}  // namespace graaf::algorithm