#include <graaflib/algorithm/graph_traversal.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

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

template <typename GRAPH_T>
struct scenario {
  GRAPH_T graph{};

  // This vector decouples the test scenario from the graphs internal id
  // generation logic. The first element in this vector is the first vertex and
  // so on...
  std::vector<vertex_id_t> vertex_ids{};
};

template <typename GRAPH_T>
[[nodiscard]] scenario<GRAPH_T> create_complex_scenario() {
  std::vector<vertex_id_t> vertex_ids{};
  vertex_ids.reserve(5);

  GRAPH_T graph{};

  vertex_ids.push_back(graph.add_vertex(10));
  vertex_ids.push_back(graph.add_vertex(20));
  vertex_ids.push_back(graph.add_vertex(30));
  vertex_ids.push_back(graph.add_vertex(40));
  vertex_ids.push_back(graph.add_vertex(50));

  // All edges are in the search direction, so the graph specialization does not
  // matter
  graph.add_edge(vertex_ids[0], vertex_ids[1], 100);
  graph.add_edge(vertex_ids[0], vertex_ids[2], 200);
  graph.add_edge(vertex_ids[2], vertex_ids[3], 300);
  graph.add_edge(vertex_ids[2], vertex_ids[4], 400);

  return {std::move(graph), std::move(vertex_ids)};
}

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
  const auto [graph, vertex_ids]{create_complex_scenario<graph_t>()};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  depth_first_traverse(graph, vertex_ids[0],
                       record_edge_callback{seen_edges, edge_order});

  // THEN
  const seen_edges_t expected_edges{{vertex_ids[0], vertex_ids[1]},
                                    {vertex_ids[0], vertex_ids[2]},
                                    {vertex_ids[2], vertex_ids[3]},
                                    {vertex_ids[2], vertex_ids[4]}};
  ASSERT_EQ(seen_edges, expected_edges);

  // We do DFS, so while the ordering between neighbors is undefined,
  // the order within one branch should be preserved
  ASSERT_TRUE(edge_order.at({vertex_ids[2], vertex_ids[3]}) >
              edge_order.at({vertex_ids[0], vertex_ids[2]}));
  ASSERT_TRUE(edge_order.at({vertex_ids[2], vertex_ids[4]}) >
              edge_order.at({vertex_ids[0], vertex_ids[2]}));
}

TYPED_TEST(TypedGraphTraversalTest, MoreComplexGraphBFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const auto [graph, vertex_ids]{create_complex_scenario<graph_t>()};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // WHEN
  breadth_first_traverse(graph, vertex_ids[0],
                         record_edge_callback{seen_edges, edge_order});

  // THEN
  const seen_edges_t expected_edges{{vertex_ids[0], vertex_ids[1]},
                                    {vertex_ids[0], vertex_ids[2]},
                                    {vertex_ids[2], vertex_ids[3]},
                                    {vertex_ids[2], vertex_ids[4]}};
  ASSERT_EQ(seen_edges, expected_edges);

  // We do BFS, so all immediate neighbors must be traversed first before going
  // deeper in the graph
  ASSERT_TRUE(edge_order.at({vertex_ids[0], vertex_ids[1]}) <
                  edge_order.at({vertex_ids[2], vertex_ids[3]}) &&
              edge_order.at({vertex_ids[0], vertex_ids[1]}) <
                  edge_order.at({vertex_ids[2], vertex_ids[4]}));
  ASSERT_TRUE(edge_order.at({vertex_ids[0], vertex_ids[2]}) <
                  edge_order.at({vertex_ids[2], vertex_ids[3]}) &&
              edge_order.at({vertex_ids[0], vertex_ids[2]}) <
                  edge_order.at({vertex_ids[2], vertex_ids[4]}));
}

TYPED_TEST(TypedGraphTraversalTest, MoreComplexGraphDFSImmediateTermination) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const auto [graph, vertex_ids]{create_complex_scenario<graph_t>()};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // Always returns true such that the search immediately terminates
  const auto immediate_termination_strategy{
      [](const vertex_id_t& /*vertex*/) { return true; }};

  // WHEN
  depth_first_traverse(graph, vertex_ids[0],
                       record_edge_callback{seen_edges, edge_order},
                       immediate_termination_strategy);

  // THEN
  const seen_edges_t expected_edges{};
  ASSERT_EQ(seen_edges, expected_edges);
}

TYPED_TEST(TypedGraphTraversalTest, MoreComplexGraphBFSImmediateTermination) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const auto [graph, vertex_ids]{create_complex_scenario<graph_t>()};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // Always returns true such that the search immediately terminates
  const auto immediate_termination_strategy{
      [](const vertex_id_t& /*vertex*/) { return true; }};

  // WHEN
  breadth_first_traverse(graph, vertex_ids[0],
                         record_edge_callback{seen_edges, edge_order},
                         immediate_termination_strategy);

  // THEN
  const seen_edges_t expected_edges{};
  ASSERT_EQ(seen_edges, expected_edges);
}

TYPED_TEST(TypedGraphTraversalTest, MoreComplexGraphDFSTermination) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const auto [graph, vertex_ids]{create_complex_scenario<graph_t>()};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  const auto termination_strategy{
      [target = vertex_ids[2]](const vertex_id_t& vertex) {
        return vertex == target;
      }};

  // WHEN
  breadth_first_traverse(graph, vertex_ids[0],
                         record_edge_callback{seen_edges, edge_order},
                         termination_strategy);

  // THEN - Since there is no clear iteration order between the neighbors of the
  // 0-th vertex, there are two options for which edges we traversed
  const seen_edges_t expected_edges_option_1{{vertex_ids[0], vertex_ids[1]},
                                             {vertex_ids[0], vertex_ids[2]}};
  const seen_edges_t expected_edges_option_2{{vertex_ids[0], vertex_ids[2]}};
  ASSERT_TRUE(seen_edges == expected_edges_option_1 ||
              seen_edges == expected_edges_option_2);
}

TYPED_TEST(TypedGraphTraversalTest, MoreComplexGraphDFSLaterTermination) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const auto [graph, vertex_ids]{create_complex_scenario<graph_t>()};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  // Here we terminate deeper in the tree
  const auto termination_strategy{
      [target = vertex_ids[3]](const vertex_id_t& vertex) {
        return vertex == target;
      }};

  // WHEN
  breadth_first_traverse(graph, vertex_ids[0],
                         record_edge_callback{seen_edges, edge_order},
                         termination_strategy);

  // THEN - Since there is no clear iteration order between the neighbors of the
  // 0-th vertex, but we must have AT_LEAST seen the following edges
  const seen_edges_t expected_edges{{vertex_ids[0], vertex_ids[2]},
                                    {vertex_ids[2], vertex_ids[3]}};
  for (const auto& expected_edge : expected_edges) {
    ASSERT_TRUE(seen_edges.contains(expected_edge));
  }
}

TYPED_TEST(TypedGraphTraversalTest, MoreComplexGraphBFSTermination) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const auto [graph, vertex_ids]{create_complex_scenario<graph_t>()};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  const auto termination_strategy{
      [target = vertex_ids[2]](const vertex_id_t& vertex) {
        return vertex == target;
      }};

  // WHEN
  breadth_first_traverse(graph, vertex_ids[0],
                         record_edge_callback{seen_edges, edge_order},
                         termination_strategy);

  // THEN - Since there is no clear iteration order between the neighbors of the
  // 0-th vertex, there are two options for which edges we traversed
  const seen_edges_t expected_edges_option_1{{vertex_ids[0], vertex_ids[1]},
                                             {vertex_ids[0], vertex_ids[2]}};
  const seen_edges_t expected_edges_option_2{{vertex_ids[0], vertex_ids[2]}};
  ASSERT_TRUE(seen_edges == expected_edges_option_1 ||
              seen_edges == expected_edges_option_2);
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