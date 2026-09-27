#include <graaflib/graph.h>
#include <gtest/gtest.h>
#include <utils/assertions/topological_order_assertions.h>
#include <utils/fixtures/fixtures.h>

namespace graaf::utils::assertions {
namespace {

template <typename T>
struct TypedTopologicalOrderAssertions : public testing::Test {
  using graph_t = T;
};

TYPED_TEST_SUITE(TypedTopologicalOrderAssertions,
                 fixtures::minimal_directed_graph_type);

}  // namespace

TYPED_TEST(TypedTopologicalOrderAssertions, AcceptsValidOrder) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  graph.add_edge(vertex_1, vertex_2, 100);

  // WHEN - THEN
  EXPECT_TRUE(is_topological_order(graph, {vertex_1, vertex_2}));
}

TYPED_TEST(TypedTopologicalOrderAssertions, RejectsWrongSize) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  graph.add_edge(vertex_1, vertex_2, 100);

  // WHEN - THEN
  EXPECT_FALSE(is_topological_order(graph, {vertex_1}));
}

TYPED_TEST(TypedTopologicalOrderAssertions, RejectsDuplicate) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  graph.add_edge(vertex_1, vertex_2, 100);

  // WHEN - THEN
  EXPECT_FALSE(is_topological_order(graph, {vertex_1, vertex_1}));
}

TYPED_TEST(TypedTopologicalOrderAssertions, RejectsMissingVertex) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // A vertex of the graph is replaced by an id that is not in it, which keeps
  // the size right and every entry unique
  const vertex_id_t absent_vertex{vertex_1 + vertex_2 + 1};

  // WHEN - THEN
  EXPECT_FALSE(is_topological_order(graph, {vertex_1, absent_vertex}));
}

TYPED_TEST(TypedTopologicalOrderAssertions, RejectsBackwardEdge) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  graph.add_edge(vertex_1, vertex_2, 100);

  // WHEN - THEN
  EXPECT_FALSE(is_topological_order(graph, {vertex_2, vertex_1}));
}

}  // namespace graaf::utils::assertions
