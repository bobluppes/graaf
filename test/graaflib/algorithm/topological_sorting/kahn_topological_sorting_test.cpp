#include <graaflib/algorithm/topological_sorting/kahn_topological_sorting.h>
#include <gtest/gtest.h>
#include <utils/assertions/topological_order_assertions.h>
#include <utils/fixtures/fixtures.h>

#include <algorithm>
#include <vector>

namespace graaf::algorithm {
namespace {

using utils::assertions::is_topological_order;

template <typename T>
struct TypedKahnTopologicalSort : public testing::Test {
  using graph_t = T;
};

TYPED_TEST_SUITE(TypedKahnTopologicalSort,
                 utils::fixtures::minimal_directed_graph_type);

};  // namespace

TYPED_TEST(TypedKahnTopologicalSort, EmptyGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};

  // THEN
  ASSERT_EQ(std::vector<vertex_id_t>{}, sorted_vertices);
}

TYPED_TEST(TypedKahnTopologicalSort, SingleVertex) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};
  const std::vector<vertex_id_t> expected_vertices{vertex_1};

  // THEN
  ASSERT_EQ(expected_vertices, sorted_vertices);
}

TYPED_TEST(TypedKahnTopologicalSort, ShortGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  graph.add_edge(vertex_1, vertex_2, 25);
  graph.add_edge(vertex_2, vertex_3, 35);
  graph.add_edge(vertex_3, vertex_4, 45);

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};
  const std::vector<vertex_id_t> expected_vertices{vertex_1, vertex_2, vertex_3,
                                                   vertex_4};

  // THEN
  // A chain admits exactly one topological order
  ASSERT_EQ(expected_vertices, sorted_vertices);
}

TYPED_TEST(TypedKahnTopologicalSort, RhombusShapeGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  graph.add_edge(vertex_1, vertex_2, 25);
  graph.add_edge(vertex_1, vertex_3, 35);
  graph.add_edge(vertex_3, vertex_4, 45);
  graph.add_edge(vertex_2, vertex_4, 55);

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};

  // THEN
  ASSERT_TRUE(sorted_vertices.has_value());
  ASSERT_TRUE(is_topological_order(graph, *sorted_vertices));
  ASSERT_EQ(vertex_1, sorted_vertices->front());
  ASSERT_EQ(vertex_4, sorted_vertices->back());
}

TYPED_TEST(TypedKahnTopologicalSort, SimpleGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};
  const auto vertex_6{graph.add_vertex(60)};
  const auto vertex_7{graph.add_vertex(70)};

  graph.add_edge(vertex_1, vertex_5, 1);
  graph.add_edge(vertex_5, vertex_3, 2);
  graph.add_edge(vertex_3, vertex_7, 3);
  graph.add_edge(vertex_1, vertex_4, 4);
  graph.add_edge(vertex_1, vertex_2, 5);
  graph.add_edge(vertex_4, vertex_2, 6);
  graph.add_edge(vertex_2, vertex_6, 7);
  graph.add_edge(vertex_6, vertex_3, 8);

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};

  // THEN
  ASSERT_TRUE(sorted_vertices.has_value());
  ASSERT_TRUE(is_topological_order(graph, *sorted_vertices));
  ASSERT_EQ(vertex_1, sorted_vertices->front());
  ASSERT_EQ(vertex_7, sorted_vertices->back());
}

TYPED_TEST(TypedKahnTopologicalSort, DisconnectedGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // Component one: a chain
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // Component two: a fork
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};
  const auto vertex_6{graph.add_vertex(60)};

  graph.add_edge(vertex_1, vertex_2, 15);
  graph.add_edge(vertex_2, vertex_3, 25);
  graph.add_edge(vertex_4, vertex_5, 35);
  graph.add_edge(vertex_4, vertex_6, 45);

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};

  // THEN
  ASSERT_TRUE(sorted_vertices.has_value());
  ASSERT_EQ(graph.vertex_count(), sorted_vertices->size());
  ASSERT_TRUE(is_topological_order(graph, *sorted_vertices));
}

TYPED_TEST(TypedKahnTopologicalSort, DisconnectedGraphWithIsolatedVertices) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // Two vertices without any edges at all
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  graph.add_edge(vertex_1, vertex_2, 15);

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};

  // THEN
  ASSERT_TRUE(sorted_vertices.has_value());
  ASSERT_EQ(4, sorted_vertices->size());
  ASSERT_TRUE(is_topological_order(graph, *sorted_vertices));
  ASSERT_NE(sorted_vertices->end(),
            std::ranges::find(*sorted_vertices, vertex_3));
  ASSERT_NE(sorted_vertices->end(),
            std::ranges::find(*sorted_vertices, vertex_4));
}

TYPED_TEST(TypedKahnTopologicalSort, CycleGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  graph.add_edge(vertex_1, vertex_2, 25);
  graph.add_edge(vertex_2, vertex_3, 35);
  graph.add_edge(vertex_3, vertex_4, 45);
  graph.add_edge(vertex_4, vertex_1, 55);

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};

  // THEN
  ASSERT_EQ(std::nullopt, sorted_vertices);
}

TYPED_TEST(TypedKahnTopologicalSort, SelfLoop) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  graph.add_edge(vertex_1, vertex_1, -1);
  graph.add_edge(vertex_1, vertex_2, 15);

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};

  // THEN
  ASSERT_EQ(std::nullopt, sorted_vertices);
}

TYPED_TEST(TypedKahnTopologicalSort, CycleInOneComponentOnly) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // An acyclic component...
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // ...next to a cyclic one
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  graph.add_edge(vertex_1, vertex_2, 15);
  graph.add_edge(vertex_3, vertex_4, 25);
  graph.add_edge(vertex_4, vertex_3, 35);

  // WHEN
  const auto sorted_vertices{kahn_topological_sort(graph)};

  // THEN
  // A cycle anywhere in the graph makes a topological order impossible
  ASSERT_EQ(std::nullopt, sorted_vertices);
}

};  // namespace graaf::algorithm
