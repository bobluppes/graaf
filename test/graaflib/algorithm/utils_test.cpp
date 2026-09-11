#include <graaflib/algorithm/utils.h>
#include <gtest/gtest.h>

#include <unordered_set>

/**
 * Tests which miscellaneous utility functions contained
 * in utils.h should go here. Any test relating specifically
 * to the public graph interface should instead be located in
 * graph_test.cpp.
 */

namespace graaf {

TEST(UtilsTest, Transpose) {
  // GIVEN
  using graph_t = directed_graph<int, int>;
  graph_t graph{};
  const auto vertex_id_1 = graph.add_vertex(1);
  const auto vertex_id_2 = graph.add_vertex(2);
  const auto vertex_id_3 = graph.add_vertex(3);
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_3, 200);
  graph.add_edge(vertex_id_3, vertex_id_1, 300);

  // WHEN
  graph_t transposed_graph = get_transposed_graph(graph);

  // THEN
  EXPECT_EQ(get_weight(transposed_graph.get_edge(vertex_id_2, vertex_id_1)),
            100);
  EXPECT_EQ(get_weight(transposed_graph.get_edge(vertex_id_3, vertex_id_2)),
            200);
  EXPECT_EQ(get_weight(transposed_graph.get_edge(vertex_id_1, vertex_id_3)),
            300);
}

TEST(UtilsTest, TransposePreservesIsolatedVertices) {
  // GIVEN
  using graph_t = directed_graph<int, int>;
  graph_t graph{};
  const auto vertex_id_1 = graph.add_vertex(1);
  const auto vertex_id_2 = graph.add_vertex(2);
  const auto vertex_id_3 = graph.add_vertex(3);
  graph.add_edge(vertex_id_1, vertex_id_2, 100);

  // WHEN
  graph_t transposed_graph = get_transposed_graph(graph);

  // THEN
  // Fully pin down the transposed graph: exactly the same three vertices,
  // with their original values, and exactly one edge, reversed.
  ASSERT_EQ(transposed_graph.vertex_count(), 3);
  EXPECT_EQ(transposed_graph.get_vertex(vertex_id_1), 1);
  EXPECT_EQ(transposed_graph.get_vertex(vertex_id_2), 2);
  EXPECT_EQ(transposed_graph.get_vertex(vertex_id_3), 3);

  ASSERT_EQ(transposed_graph.edge_count(), 1);
  EXPECT_TRUE(transposed_graph.has_edge(vertex_id_2, vertex_id_1));
  EXPECT_EQ(get_weight(transposed_graph.get_edge(vertex_id_2, vertex_id_1)),
            100);

  // The original-direction edge should not survive the transpose.
  EXPECT_FALSE(transposed_graph.has_edge(vertex_id_1, vertex_id_2));
}

TEST(UtilsTest, GetPredecessorsDirectedGraph) {
  // GIVEN
  using graph_t = directed_graph<int, int>;
  graph_t graph{};
  const auto vertex_a = graph.add_vertex(1);
  const auto vertex_b = graph.add_vertex(2);
  const auto vertex_c = graph.add_vertex(3);

  // a -> c, b -> c, a has no predecessors
  graph.add_edge(vertex_a, vertex_c, 100);
  graph.add_edge(vertex_b, vertex_c, 200);

  // WHEN
  const auto predecessors = get_predecessors(graph);

  // THEN
  ASSERT_TRUE(predecessors.contains(vertex_c));
  EXPECT_EQ(predecessors.at(vertex_c),
            std::unordered_set<vertex_id_t>({vertex_a, vertex_b}));
  EXPECT_FALSE(predecessors.contains(vertex_a));
  EXPECT_FALSE(predecessors.contains(vertex_b));
}

TEST(UtilsTest, GetPredecessorsUndirectedGraph) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;
  graph_t graph{};
  const auto vertex_a = graph.add_vertex(1);
  const auto vertex_b = graph.add_vertex(2);

  graph.add_edge(vertex_a, vertex_b, 100);

  // WHEN
  const auto predecessors = get_predecessors(graph);

  // THEN
  // For an undirected graph, add_edge inserts both directions, so each
  // vertex is a "predecessor" of the other.
  ASSERT_TRUE(predecessors.contains(vertex_a));
  EXPECT_EQ(predecessors.at(vertex_a),
            std::unordered_set<vertex_id_t>({vertex_b}));
  ASSERT_TRUE(predecessors.contains(vertex_b));
  EXPECT_EQ(predecessors.at(vertex_b),
            std::unordered_set<vertex_id_t>({vertex_a}));
}

}  // namespace graaf