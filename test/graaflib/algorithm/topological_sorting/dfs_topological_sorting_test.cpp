#include <fmt/core.h>
#include <graaflib/algorithm/topological_sorting/dfs_topological_sorting.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

namespace graaf::algorithm {
namespace {
template <typename T>
struct TypedTopologicalSort : public testing::Test {
  using graph_t = T;
};

using graph_types = testing::Types<directed_graph<int, int>>;
TYPED_TEST_SUITE(TypedTopologicalSort, graph_types);

};  // namespace

TYPED_TEST(TypedTopologicalSort, ShortGraph) {
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

  // WHEN;
  auto sorted_vertices = dfs_topological_sort(graph);
  std::vector<vertex_id_t> expected_vertices{vertex_1, vertex_2, vertex_3,
                                             vertex_4};

  // THEN
  ASSERT_EQ(expected_vertices, sorted_vertices);
}

TYPED_TEST(TypedTopologicalSort, RhombusShapeGraph) {
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

  // WHEN;
  auto sorted_vertices = dfs_topological_sort(graph);
  std::vector<vertex_id_t> expected_vertices_1{vertex_1, vertex_2, vertex_3,
                                               vertex_4};
  std::vector<vertex_id_t> expected_vertices_2{vertex_1, vertex_3, vertex_2,
                                               vertex_4};

  // THEN
  ASSERT_TRUE(expected_vertices_1 == sorted_vertices ||
              expected_vertices_2 == sorted_vertices);
}

TYPED_TEST(TypedTopologicalSort, CycleGraph) {
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

  // WHEN;
  auto sorted_vertices = dfs_topological_sort(graph);
  const auto expected_vertices = std::nullopt;

  // THEN
  ASSERT_EQ(expected_vertices, sorted_vertices);
}

TYPED_TEST(TypedTopologicalSort, GraphWithParallelEdge) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  graph.add_edge(vertex_1, vertex_2, 25);
  graph.add_edge(vertex_3, vertex_4, 35);
  graph.add_edge(vertex_4, vertex_1, 45);
  graph.add_edge(vertex_1, vertex_4, 55);

  // WHEN
  auto sorted_vertices = dfs_topological_sort(graph);
  const auto expected_vertices = std::nullopt;

  // THEN
  ASSERT_EQ(expected_vertices, sorted_vertices);
}

TYPED_TEST(TypedTopologicalSort, SelfLoop) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  graph.add_edge(vertex_1, vertex_1, -1);
  graph.add_edge(vertex_2, vertex_2, -1);
  graph.add_edge(vertex_1, vertex_2, 15);
  graph.add_edge(vertex_3, vertex_4, 25);

  // WHEN;
  auto sorted_vertices = dfs_topological_sort(graph);
  const auto expected_vertices = std::nullopt;

  // THEN
  ASSERT_EQ(expected_vertices, sorted_vertices);
}

TYPED_TEST(TypedTopologicalSort, SimpleGraph) {
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

  // WHEN;
  auto sorted_vertices = dfs_topological_sort(graph);
  std::vector<vertex_id_t> expected_vertices_1{
      vertex_1, vertex_4, vertex_2, vertex_6, vertex_5, vertex_3, vertex_7};
  std::vector<vertex_id_t> expected_vertices_2{
      vertex_1, vertex_2, vertex_4, vertex_6, vertex_5, vertex_3, vertex_7};
  std::vector<vertex_id_t> expected_vertices_3{
      vertex_1, vertex_2, vertex_4, vertex_5, vertex_6, vertex_3, vertex_7};
  std::vector<vertex_id_t> expected_vertices_4{
      vertex_1, vertex_5, vertex_4, vertex_2, vertex_6, vertex_3, vertex_7};
  std::vector<vertex_id_t> expected_vertices_5{
      vertex_1, vertex_5, vertex_2, vertex_4, vertex_6, vertex_3, vertex_7};
  std::vector<vertex_id_t> expected_vertices_6{
      vertex_1, vertex_2, vertex_5, vertex_4, vertex_6, vertex_3, vertex_7};
  std::vector<vertex_id_t> expected_vertices_7{
      vertex_1, vertex_4, vertex_2, vertex_5, vertex_6, vertex_3, vertex_7};
  std::vector<vertex_id_t> expected_vertices_8{
      vertex_1, vertex_4, vertex_5, vertex_2, vertex_6, vertex_3, vertex_7};

  // THEN
  ASSERT_TRUE((expected_vertices_1 == sorted_vertices) ||
              (expected_vertices_2 == sorted_vertices) ||
              (expected_vertices_3 == sorted_vertices) ||
              (expected_vertices_4 == sorted_vertices) ||
              (expected_vertices_5 == sorted_vertices) ||
              (expected_vertices_6 == sorted_vertices) ||
              (expected_vertices_7 == sorted_vertices) ||
              (expected_vertices_8 == sorted_vertices));
}

TYPED_TEST(TypedTopologicalSort, SixSortResults) {
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

  graph.add_edge(vertex_1, vertex_2, 1);
  graph.add_edge(vertex_2, vertex_3, 2);
  graph.add_edge(vertex_1, vertex_4, 3);
  graph.add_edge(vertex_4, vertex_5, 4);
  graph.add_edge(vertex_1, vertex_6, 5);
  graph.add_edge(vertex_6, vertex_7, 6);

  // WHEN;
  auto sorted_vertices = dfs_topological_sort(graph);
  std::vector<vertex_id_t> expected_vertices_1{
      vertex_1, vertex_2, vertex_3, vertex_4, vertex_5, vertex_6, vertex_7};
  std::vector<vertex_id_t> expected_vertices_2{
      vertex_1, vertex_2, vertex_3, vertex_6, vertex_7, vertex_4, vertex_5};
  std::vector<vertex_id_t> expected_vertices_3{
      vertex_1, vertex_6, vertex_7, vertex_2, vertex_3, vertex_4, vertex_5};
  std::vector<vertex_id_t> expected_vertices_4{
      vertex_1, vertex_6, vertex_7, vertex_4, vertex_5, vertex_2, vertex_3};
  std::vector<vertex_id_t> expected_vertices_5{
      vertex_1, vertex_4, vertex_5, vertex_6, vertex_7, vertex_2, vertex_3};
  std::vector<vertex_id_t> expected_vertices_6{
      vertex_1, vertex_4, vertex_5, vertex_2, vertex_3, vertex_6, vertex_7};

  // THEN
  ASSERT_TRUE((expected_vertices_1 == sorted_vertices) ||
              (expected_vertices_2 == sorted_vertices) ||
              (expected_vertices_3 == sorted_vertices) ||
              (expected_vertices_4 == sorted_vertices) ||
              (expected_vertices_4 == sorted_vertices) ||
              (expected_vertices_6 == sorted_vertices));
}

};  // namespace graaf::algorithm