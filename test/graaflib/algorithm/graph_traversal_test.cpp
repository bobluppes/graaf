#include <graaflib/algorithm/graph_traversal.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
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
TYPED_TEST_SUITE(TypedGraphTraversalTest, graph_types);

using seen_edges_t = std::unordered_multiset<edge_id_t, edge_id_hash>;
using edge_order_t = std::unordered_map<edge_id_t, std::size_t, edge_id_hash>;

/**
 * @brief Callback to record the traversed edges and their order.
 */
struct record_edge_callback {
  seen_edges_t& seen_edges;
  edge_order_t& edge_order;
  mutable std::size_t edge_order_supplier{0};

  record_edge_callback(seen_edges_t& seen_edges, edge_order_t& edge_order)
      : seen_edges{seen_edges}, edge_order{edge_order} {}

  void operator()(const edge_id_t& edge) const {
    seen_edges.insert(edge);
    edge_order[edge] = edge_order_supplier++;
  }
};

}  // namespace

TYPED_TEST(TypedGraphTraversalTest, MinimalGraphDFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  depth_first_traverse(graph, vertex_1,
                       record_edge_callback{seen_edges, edge_order});

  // THEN
  const seen_edges_t expected_edges{};
  ASSERT_EQ(seen_edges, expected_edges);
}

TYPED_TEST(TypedGraphTraversalTest, MinimalGraphBFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  breadth_first_traverse(graph, vertex_1,
                         record_edge_callback{seen_edges, edge_order});

  // THEN
  const seen_edges_t expected_edges{};
  ASSERT_EQ(seen_edges, expected_edges);
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

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  depth_first_traverse(graph, vertex_1,
                       record_edge_callback{seen_edges, edge_order});

  // THEN
  const seen_edges_t expected_edges{{vertex_1, vertex_2}};
  ASSERT_EQ(seen_edges, expected_edges);
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

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  breadth_first_traverse(graph, vertex_1,
                         record_edge_callback{seen_edges, edge_order});

  const seen_edges_t expected_edges{{vertex_1, vertex_2}};
  ASSERT_EQ(seen_edges, expected_edges);
}

TEST(GraphTraversalTest, DirectedGraphEdgeWrongDirectionDFS) {
  directed_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // The direction of the edge is from 2 -> 1
  graph.add_edge(vertex_2, vertex_1, 100);

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN - here vertex 1 has no neighbors due to the edge direction
  depth_first_traverse(graph, vertex_1,
                       record_edge_callback{seen_edges, edge_order});

  // THEN - there was no edge to traverse
  const seen_edges_t expected_edges{};
  ASSERT_EQ(seen_edges, expected_edges);
}

TEST(GraphTraversalTest, DirectedGraphEdgeWrongDirectionBFS) {
  directed_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // The direction of the edge is from 2 -> 1
  graph.add_edge(vertex_2, vertex_1, 100);

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN - here vertex 1 has no neighbors due to the edge direction
  breadth_first_traverse(graph, vertex_1,
                         record_edge_callback{seen_edges, edge_order});

  // THEN - there was no edge to traverse
  const seen_edges_t expected_edges{};
  ASSERT_EQ(seen_edges, expected_edges);
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

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  depth_first_traverse(graph, vertex_1,
                       record_edge_callback{seen_edges, edge_order});

  // THEN
  const seen_edges_t expected_edges{{vertex_1, vertex_2},
                                    {vertex_1, vertex_3},
                                    {vertex_3, vertex_4},
                                    {vertex_3, vertex_5}};
  ASSERT_EQ(seen_edges, expected_edges);

  // We do DFS, so while the ordering between neighbors is undefined,
  // the order within one branch should be preserved
  ASSERT_TRUE(edge_order.at({vertex_3, vertex_4}) >
              edge_order.at({vertex_1, vertex_3}));
  ASSERT_TRUE(edge_order.at({vertex_3, vertex_5}) >
              edge_order.at({vertex_1, vertex_3}));
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

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  breadth_first_traverse(graph, vertex_1,
                         record_edge_callback{seen_edges, edge_order});

  // THEN
  const seen_edges_t expected_edges{{vertex_1, vertex_2},
                                    {vertex_1, vertex_3},
                                    {vertex_3, vertex_4},
                                    {vertex_3, vertex_5}};
  ASSERT_EQ(seen_edges, expected_edges);

  // We do BFS, so all immediate neighbors must be traversed first before going
  // deeper in the graph
  ASSERT_TRUE(edge_order.at({vertex_1, vertex_2}) <
                  edge_order.at({vertex_3, vertex_4}) &&
              edge_order.at({vertex_1, vertex_2}) <
                  edge_order.at({vertex_3, vertex_5}));
  ASSERT_TRUE(edge_order.at({vertex_1, vertex_3}) <
                  edge_order.at({vertex_3, vertex_4}) &&
              edge_order.at({vertex_1, vertex_3}) <
                  edge_order.at({vertex_3, vertex_5}));
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

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  depth_first_traverse(graph, vertex_1,
                       record_edge_callback{seen_edges, edge_order});

  // THEN
  const seen_edges_t expected_edges{
      {vertex_1, vertex_2}, {vertex_1, vertex_3}, {vertex_3, vertex_4}};
  ASSERT_EQ(seen_edges, expected_edges);
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

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  breadth_first_traverse(graph, vertex_1,
                         record_edge_callback{seen_edges, edge_order});

  // THEN
  const seen_edges_t expected_edges{
      {vertex_1, vertex_2}, {vertex_1, vertex_3}, {vertex_3, vertex_4}};
  ASSERT_EQ(seen_edges, expected_edges);
}

}  // namespace graaf::algorithm