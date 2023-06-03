#include <graaflib/directed_graph.h>
#include <graaflib/undirected_graph.h>
#include <gtest/gtest.h>

namespace graaf {

/**
 * DIRECTED GRAPH
 */

TEST(GraphTraitsTest, DirectedGraphUnweightedPrimitiveType) {
  // GIVEN - WHEN
  directed_graph<int, int> graph{};

  // THEN The graph is directed
  ASSERT_TRUE(graph.is_directed());
  ASSERT_FALSE(graph.is_undirected());

  // By default the graph is unweighted
  ASSERT_TRUE(graph.is_unweighted());
  ASSERT_FALSE(graph.is_weighted());
}

TEST(GraphTraitsTest, DirectedGraphWeightedPrimitiveType) {
  // GIVEN - WHEN
  directed_graph<int, int, edge_type::WEIGHTED> graph{};

  // THEN The graph is directed
  ASSERT_TRUE(graph.is_directed());
  ASSERT_FALSE(graph.is_undirected());

  // The graph is weighted
  ASSERT_TRUE(graph.is_weighted());
  ASSERT_FALSE(graph.is_unweighted());
}

TEST(GraphTraitsTest, DirectedGraphUnweightedPNonrimitiveType) {
  // GIVEN - WHEN
  struct my_edge {};

  directed_graph<int, my_edge> graph{};

  // THEN The graph is directed
  ASSERT_TRUE(graph.is_directed());
  ASSERT_FALSE(graph.is_undirected());

  // By default the graph is unweighted
  ASSERT_TRUE(graph.is_unweighted());
  ASSERT_FALSE(graph.is_weighted());
}

TEST(GraphTraitsTest, DirectedGraphWeightedNonPrimitiveType) {
  // GIVEN - WHEN
  struct my_edge : public weighted_edge<int> {};

  directed_graph<int, my_edge, edge_type::WEIGHTED> graph{};

  // THEN The graph is directed
  ASSERT_TRUE(graph.is_directed());
  ASSERT_FALSE(graph.is_undirected());

  // The graph is weighted
  ASSERT_TRUE(graph.is_weighted());
  ASSERT_FALSE(graph.is_unweighted());
}

/**
 * UNDIRECTED GRAPH
 */

TEST(GraphTraitsTest, UndirectedGraphUnweightedPrimitiveType) {
  // GIVEN - WHEN
  undirected_graph<int, int> graph{};

  // THEN The graph is undirected
  ASSERT_TRUE(graph.is_undirected());
  ASSERT_FALSE(graph.is_directed());

  // By default the graph is unweighted
  ASSERT_TRUE(graph.is_unweighted());
  ASSERT_FALSE(graph.is_weighted());
}

TEST(GraphTraitsTest, UndirectedGraphWeightedPrimitiveType) {
  // GIVEN - WHEN
  undirected_graph<int, int, edge_type::WEIGHTED> graph{};

  // THEN The graph is undirected
  ASSERT_TRUE(graph.is_undirected());
  ASSERT_FALSE(graph.is_directed());

  // The graph is weighted
  ASSERT_TRUE(graph.is_weighted());
  ASSERT_FALSE(graph.is_unweighted());
}

TEST(GraphTraitsTest, UndirectedGraphUnweightedPNonrimitiveType) {
  // GIVEN - WHEN
  struct my_edge {};

  undirected_graph<int, my_edge> graph{};

  // THEN The graph is undirected
  ASSERT_TRUE(graph.is_undirected());
  ASSERT_FALSE(graph.is_directed());

  // By default the graph is unweighted
  ASSERT_TRUE(graph.is_unweighted());
  ASSERT_FALSE(graph.is_weighted());
}

TEST(GraphTraitsTest, UndirectedGraphWeightedNonPrimitiveType) {
  // GIVEN - WHEN
  struct my_edge : public weighted_edge<int> {};

  undirected_graph<int, my_edge, edge_type::WEIGHTED> graph{};

  // THEN The graph is undirected
  ASSERT_TRUE(graph.is_undirected());
  ASSERT_FALSE(graph.is_directed());

  // The graph is weighted
  ASSERT_TRUE(graph.is_weighted());
  ASSERT_FALSE(graph.is_unweighted());
}

}  // namespace graaf