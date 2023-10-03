#include <graaflib/algorithm/graph_traversal/depth_first_search.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>
#include <utils/scenarios/scenarios.h>
#include <utils/fixtures/fixtures.h>

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace graaf::algorithm {

namespace {

template <typename T>
struct TypedGraphTraversalTestDFS : public testing::Test {
  using graph_t = T;
};

TYPED_TEST_SUITE(TypedGraphTraversalTestDFS, utils::fixtures::minimal_graph_types);

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

TYPED_TEST(TypedGraphTraversalTestDFS, MinimalGraphDFS) {
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

TYPED_TEST(TypedGraphTraversalTestDFS, SimpleGraphDFS) {
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

TYPED_TEST(TypedGraphTraversalTestDFS, MoreComplexGraphDFS) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const auto [graph,
              vertex_ids]{utils::scenarios::create_tree_scenario<graph_t>()};

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

TYPED_TEST(TypedGraphTraversalTestDFS, MoreComplexGraphDFSTermination) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const auto [graph,
              vertex_ids]{utils::scenarios::create_tree_scenario<graph_t>()};

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  const auto termination_strategy{
      [target = vertex_ids[2]](const vertex_id_t& vertex) {
        return vertex == target;
      }};

  // WHEN
  depth_first_traverse(graph, vertex_ids[0],
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

TYPED_TEST(TypedGraphTraversalTestDFS,
           MoreComplexGraphDFSImmediateTermination) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const auto [graph,
              vertex_ids]{utils::scenarios::create_tree_scenario<graph_t>()};

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

}  // namespace graaf::algorithm