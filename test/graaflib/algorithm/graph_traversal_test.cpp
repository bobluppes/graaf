#include <graaflib/algorithm/graph_traversal.h>
#include <graaflib/directed_graph.h>
#include <graaflib/types.h>
#include <graaflib/undirected_graph.h>
#include <gtest/gtest.h>

#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace graaf::algorithm {

namespace {

template <typename T>
struct TypedGraphTraversalTest : public testing::Test {
  using graph_t = T;
};

using graph_types =
    testing::Types<directed_graph<int, int>, undirected_graph<int, int>>;
TYPED_TEST_CASE(TypedGraphTraversalTest, graph_types);

using seen_vertices_t = std::unordered_multiset<vertex_id_t>;
using vertex_order_t = std::unordered_map<vertex_id_t, std::size_t>;

/**
 * @brief Callback to record the traversed vertex ids and their order.
 */
struct record_vertex_callback {
  seen_vertices_t& seen_vertices;
  vertex_order_t& vertex_order;
  mutable std::size_t vertex_order_supplier{0};

  record_vertex_callback(seen_vertices_t& seen_vertices,
                         vertex_order_t& vertex_order)
      : seen_vertices{seen_vertices}, vertex_order{vertex_order} {}

  void operator()(const vertex_id_t vertex) const {
    seen_vertices.insert(vertex);
    vertex_order[vertex] = vertex_order_supplier++;
  }
};

}  // namespace

TYPED_TEST(TypedGraphTraversalTest, MinimalGraphDFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN
  traverse<search_strategy::DFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN
  const seen_vertices_t expected_vertices{vertex_1};
  ASSERT_EQ(seen_vertices, expected_vertices);
}

TYPED_TEST(TypedGraphTraversalTest, MinimalGraphBFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN
  traverse<search_strategy::BFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN
  const seen_vertices_t expected_vertices{vertex_1};
  ASSERT_EQ(seen_vertices, expected_vertices);
}

TYPED_TEST(TypedGraphTraversalTest, SimpleGraphDFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // We add an edge from the vertex where we start the traversal
  // so it does not matter whether this is a directed or undirected graph
  graph.add_edge(vertex_1, vertex_2, 100);

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN
  traverse<search_strategy::DFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN - The order of traversal between neighbors is undefined
  const seen_vertices_t expected_vertices{vertex_1, vertex_2};
  ASSERT_EQ(seen_vertices, expected_vertices);
}

TYPED_TEST(TypedGraphTraversalTest, SimpleGraphBFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // We add an edge from the vertex where we start the traversal
  // so it does not matter whether this is a directed or undirected graph
  graph.add_edge(vertex_1, vertex_2, 100);

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN
  traverse<search_strategy::BFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN - The order of traversal between neighbors is undefined
  const seen_vertices_t expected_vertices{vertex_1, vertex_2};
  ASSERT_EQ(seen_vertices, expected_vertices);
}

TEST(GraphTraversalTest, DirectedGraphEdgeWrongDirectionDFS) {
  directed_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // The direction of the edge is from 2 -> 1
  graph.add_edge(vertex_2, vertex_1, 100);

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN - here vertex 1 has no neighbors due to the edge direction
  traverse<search_strategy::DFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN
  const seen_vertices_t expected_vertices{vertex_1};
  ASSERT_EQ(seen_vertices, expected_vertices);
}

TEST(GraphTraversalTest, DirectedGraphEdgeWrongDirectionBFS) {
  directed_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // The direction of the edge is from 2 -> 1
  graph.add_edge(vertex_2, vertex_1, 100);

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN - here vertex 1 has no neighbors due to the edge direction
  traverse<search_strategy::BFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN
  const seen_vertices_t expected_vertices{vertex_1};
  ASSERT_EQ(seen_vertices, expected_vertices);
}

TYPED_TEST(TypedGraphTraversalTest, MoreComplexGraphDFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  // All edges are in the search direction, so the graph specialization does not
  // matter
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_1, vertex_3, 200);
  graph.add_edge(vertex_3, vertex_4, 300);
  graph.add_edge(vertex_3, vertex_5, 400);

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN
  traverse<search_strategy::DFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN
  const seen_vertices_t expected_vertices{vertex_1, vertex_2, vertex_3,
                                          vertex_4, vertex_5};
  ASSERT_EQ(seen_vertices, expected_vertices);

  // We do DFS, so while the ordering between neighbors is undefined,
  // the order within one branch should be preserved
  ASSERT_TRUE(vertex_order.at(vertex_2) > vertex_order.at(vertex_1));
  ASSERT_TRUE(vertex_order.at(vertex_3) > vertex_order.at(vertex_1));
  ASSERT_TRUE(vertex_order.at(vertex_4) > vertex_order.at(vertex_3));
  ASSERT_TRUE(vertex_order.at(vertex_5) > vertex_order.at(vertex_3));
}

TYPED_TEST(TypedGraphTraversalTest, MoreComplexGraphBFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  // All edges are in the search direction, so the graph specialization does not
  // matter
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_1, vertex_3, 200);
  graph.add_edge(vertex_3, vertex_4, 300);
  graph.add_edge(vertex_3, vertex_5, 400);

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN
  traverse<search_strategy::BFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN
  const seen_vertices_t expected_vertices{vertex_1, vertex_2, vertex_3,
                                          vertex_4, vertex_5};
  ASSERT_EQ(seen_vertices, expected_vertices);

  // We do BFS, so all immediate neighbors must be traversed first before going
  // deeper in the graph
  ASSERT_TRUE(vertex_order.at(vertex_2) < vertex_order.at(vertex_4) &&
              vertex_order.at(vertex_3) < vertex_order.at(vertex_4));
  ASSERT_TRUE(vertex_order.at(vertex_2) < vertex_order.at(vertex_5) &&
              vertex_order.at(vertex_3) < vertex_order.at(vertex_5));
}

TEST(GraphTraversalTest, MoreComplexDirectedGraphEdgeWrongDirectionDFS) {
  // GIVEN
  directed_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  // All edges are in the search direction, so the graph specialization does not
  // matter
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_1, vertex_3, 200);
  graph.add_edge(vertex_3, vertex_4, 300);
  graph.add_edge(vertex_5, vertex_3, 400);  // The direction here is from 5 -> 3

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN
  traverse<search_strategy::DFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN
  const seen_vertices_t expected_vertices{vertex_1, vertex_2, vertex_3,
                                          vertex_4};
  ASSERT_EQ(seen_vertices, expected_vertices);
}

TEST(GraphTraversalTest, MoreComplexDirectedGraphEdgeWrongDirectionBFS) {
  // GIVEN
  directed_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  // All edges are in the search direction, so the graph specialization does not
  // matter
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_1, vertex_3, 200);
  graph.add_edge(vertex_3, vertex_4, 300);
  graph.add_edge(vertex_5, vertex_3, 400);  // The direction here is from 5 -> 3

  seen_vertices_t seen_vertices{};
  vertex_order_t vertex_order{};

  // WHEN
  traverse<search_strategy::BFS>(
      graph, vertex_1, record_vertex_callback{seen_vertices, vertex_order});

  // THEN
  const seen_vertices_t expected_vertices{vertex_1, vertex_2, vertex_3,
                                          vertex_4};
  ASSERT_EQ(seen_vertices, expected_vertices);
}

}  // namespace graaf::algorithm