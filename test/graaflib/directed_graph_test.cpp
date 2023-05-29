#include <graaflib/directed_graph.h>
#include <gtest/gtest.h>

namespace graaf {

TEST(DirectedGraphTest, DirectedGraphIsNoUndirectedGraph) {
  // GIVEN - WHEN
  directed_graph<int, int> graph{};

  // THEN
  ASSERT_TRUE(graph.is_directed());
  ASSERT_FALSE(graph.is_undirected());
}

TEST(DirectedGraphTest, EdgeCount) {
  // GIVEN
  directed_graph<int, int> graph{};
  ASSERT_EQ(graph.edge_count(), 0);

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, 100);

  // THEN
  ASSERT_EQ(graph.edge_count(), 1);
  ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));
  ASSERT_FALSE(graph.has_edge(vertex_id_2, vertex_id_1));
  ASSERT_EQ(graph.get_edge(vertex_id_1, vertex_id_2), 100);
}

TEST(DirectedGraphTest, GetNeighbors) {
  // GIVEN
  directed_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};

  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_1, vertex_id_3, 200);

  // WHEN - THEN
  const auto neighbors_vertex_1{graph.get_neighbors(vertex_id_1)};
  ASSERT_EQ(neighbors_vertex_1.size(), 2);
  ASSERT_TRUE(neighbors_vertex_1.contains(vertex_id_2));
  ASSERT_TRUE(neighbors_vertex_1.contains(vertex_id_3));

  // WHEN - THEN
  // The graph is directed so vertex 2 has no neighbors
  const auto neighbors_vertex_2{graph.get_neighbors(vertex_id_2)};
  ASSERT_TRUE(neighbors_vertex_2.empty());

  // WHEN - THEN
  // The graph is directed so vertex 3 has no neighbors
  const auto neighbors_vertex_3{graph.get_neighbors(vertex_id_3)};
  ASSERT_TRUE(neighbors_vertex_3.empty());
}

TEST(DirectedGraphTest, VertexOutDegree) {
  // GIVEN
  directed_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_3, 200);
  graph.add_edge(vertex_id_2, vertex_id_4, 300);

  // THEN
  ASSERT_EQ(graph.get_vertex_outdegree(vertex_id_1), 1);
  ASSERT_EQ(graph.get_vertex_outdegree(vertex_id_2), 2);
  ASSERT_EQ(graph.get_vertex_outdegree(vertex_id_3), 0);
  ASSERT_EQ(graph.get_vertex_outdegree(vertex_id_4), 0);
}

TEST(DirectedGraphTest, VertexInDegree) {
  // GIVEN
  directed_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_1, vertex_id_3, 200);
  graph.add_edge(vertex_id_3, vertex_id_4, 300);
  graph.add_edge(vertex_id_2, vertex_id_4, 400);

  // THEN
  ASSERT_EQ(graph.get_vertex_indegree(vertex_id_1), 0);
  ASSERT_EQ(graph.get_vertex_indegree(vertex_id_2), 1);
  ASSERT_EQ(graph.get_vertex_indegree(vertex_id_3), 1);
  ASSERT_EQ(graph.get_vertex_indegree(vertex_id_4), 2);
}

}  // namespace graaf