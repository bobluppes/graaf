#include <graaflib/graph.h>
#include <graaflib/properties/vertex_properties.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

namespace graaf::properties {

TEST(DirectedGraphPropertiesTest, VertexOutDegree) {
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
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_1), 1);
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_2), 2);
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_3), 0);
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_4), 0);
}

TEST(DirectedGraphPropertiesTest, VertexInDegree) {
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
  ASSERT_EQ(vertex_indegree(graph, vertex_id_1), 0);
  ASSERT_EQ(vertex_indegree(graph, vertex_id_2), 1);
  ASSERT_EQ(vertex_indegree(graph, vertex_id_3), 1);
  ASSERT_EQ(vertex_indegree(graph, vertex_id_4), 2);
}

TEST(DirectedGraphPropertiesTest, VertexDegree) {
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
  ASSERT_EQ(vertex_degree(graph, vertex_id_1), 2);
  ASSERT_EQ(vertex_degree(graph, vertex_id_2), 2);
  ASSERT_EQ(vertex_degree(graph, vertex_id_3), 2);
  ASSERT_EQ(vertex_degree(graph, vertex_id_4), 2);
}

TEST(DirectedGraphPropertiesTest, VertexDegreeWithSelfLoop) {
  // GIVEN
  directed_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_1, 100);
  graph.add_edge(vertex_id_1, vertex_id_2, 200);

  // THEN
  // In a directed graph, the self-loop contributes one to the outdegree
  // and one to the indegree of vertex_id_1.
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_1), 2);
  ASSERT_EQ(vertex_indegree(graph, vertex_id_1), 1);
  ASSERT_EQ(vertex_degree(graph, vertex_id_1), 3);
}

TEST(UndirectedGraphPropertiesTest, VertexOutDegree) {
  // GIVEN
  undirected_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_3, 200);
  graph.add_edge(vertex_id_2, vertex_id_4, 300);

  // THEN
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_1), 1);
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_2), 3);
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_3), 1);
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_4), 1);
}

TEST(UndirectedGraphPropertiesTest, VertexOutDegreeWithSelfLoop) {
  // GIVEN
  undirected_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_1, 100);
  graph.add_edge(vertex_id_1, vertex_id_2, 200);

  // THEN
  // The self-loop on vertex_id_1 contributes two to its degree, per the
  // standard graph-theory convention. For an undirected graph, indegree
  // is equal to outdegree.
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_1), 3);
  ASSERT_EQ(vertex_outdegree(graph, vertex_id_2), 1);
  ASSERT_EQ(vertex_indegree(graph, vertex_id_1), 3);
  ASSERT_EQ(vertex_indegree(graph, vertex_id_2), 1);
}

TEST(UndirectedGraphPropertiesTest, VertexDegreeWithSelfLoop) {
  // GIVEN
  undirected_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_1, 100);
  graph.add_edge(vertex_id_1, vertex_id_2, 200);

  // THEN
  ASSERT_EQ(vertex_degree(graph, vertex_id_1), 3);
  ASSERT_EQ(vertex_degree(graph, vertex_id_2), 1);
}

TEST(UndirectedGraphPropertiesTest, VertexInDegree) {
  // GIVEN
  undirected_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_3, 200);
  graph.add_edge(vertex_id_2, vertex_id_4, 300);

  // THEN
  ASSERT_EQ(vertex_indegree(graph, vertex_id_1), 1);
  ASSERT_EQ(vertex_indegree(graph, vertex_id_2), 3);
  ASSERT_EQ(vertex_indegree(graph, vertex_id_3), 1);
  ASSERT_EQ(vertex_indegree(graph, vertex_id_4), 1);
}

TEST(UndirectedGraphPropertiesTest, VertexDegree) {
  // GIVEN
  undirected_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_3, 200);
  graph.add_edge(vertex_id_2, vertex_id_4, 300);

  // THEN
  ASSERT_EQ(vertex_degree(graph, vertex_id_1), 1);
  ASSERT_EQ(vertex_degree(graph, vertex_id_2), 3);
  ASSERT_EQ(vertex_degree(graph, vertex_id_3), 1);
  ASSERT_EQ(vertex_degree(graph, vertex_id_4), 1);
}

TEST(UndirectedGraphCentralityTest, EmptyGraph) {
  // GIVEN
  undirected_graph<int, int> graph{};

  // WHEN
  const auto betweenness{betweenness_centrality(graph)};
  const auto closeness{closeness_centrality(graph)};

  // THEN
  EXPECT_TRUE(betweenness.empty());
  EXPECT_TRUE(closeness.empty());
}

TEST(UndirectedGraphCentralityTest, SingleVertex) {
  // GIVEN
  undirected_graph<int, int> graph{};
  const auto vertex_id{graph.add_vertex(10)};

  // WHEN
  const auto betweenness{betweenness_centrality(graph)};
  const auto closeness{closeness_centrality(graph)};

  // THEN
  ASSERT_EQ(betweenness.size(), 1);
  ASSERT_EQ(closeness.size(), 1);
  EXPECT_DOUBLE_EQ(betweenness.at(vertex_id), 0.0);
  EXPECT_DOUBLE_EQ(closeness.at(vertex_id), 0.0);
}

TEST(UndirectedGraphCentralityTest, FourVertexPath) {
  // GIVEN
  undirected_graph<int, int> graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_3, 200);
  graph.add_edge(vertex_id_3, vertex_id_4, 300);

  // WHEN
  const auto betweenness{betweenness_centrality(graph)};
  const auto closeness{closeness_centrality(graph)};

  // THEN
  constexpr double comparison_threshold{1e-9};
  EXPECT_NEAR(betweenness.at(vertex_id_1), 0.0, comparison_threshold);
  EXPECT_NEAR(betweenness.at(vertex_id_2), 2.0, comparison_threshold);
  EXPECT_NEAR(betweenness.at(vertex_id_3), 2.0, comparison_threshold);
  EXPECT_NEAR(betweenness.at(vertex_id_4), 0.0, comparison_threshold);

  EXPECT_NEAR(closeness.at(vertex_id_1), 1.0 / 6.0, comparison_threshold);
  EXPECT_NEAR(closeness.at(vertex_id_2), 1.0 / 4.0, comparison_threshold);
  EXPECT_NEAR(closeness.at(vertex_id_3), 1.0 / 4.0, comparison_threshold);
  EXPECT_NEAR(closeness.at(vertex_id_4), 1.0 / 6.0, comparison_threshold);
}

TEST(UndirectedGraphCentralityTest, StarGraph) {
  // GIVEN
  undirected_graph<int, int> graph{};
  const auto center{graph.add_vertex(10)};
  const auto leaf_1{graph.add_vertex(20)};
  const auto leaf_2{graph.add_vertex(30)};
  const auto leaf_3{graph.add_vertex(40)};
  graph.add_edge(center, leaf_1, 100);
  graph.add_edge(center, leaf_2, 200);
  graph.add_edge(center, leaf_3, 300);

  // WHEN
  const auto betweenness{betweenness_centrality(graph)};
  const auto closeness{closeness_centrality(graph)};

  // THEN
  constexpr double comparison_threshold{1e-9};
  EXPECT_NEAR(betweenness.at(center), 3.0, comparison_threshold);
  EXPECT_DOUBLE_EQ(betweenness.at(leaf_1), 0.0);
  EXPECT_DOUBLE_EQ(betweenness.at(leaf_2), 0.0);
  EXPECT_DOUBLE_EQ(betweenness.at(leaf_3), 0.0);

  for (const auto leaf : {leaf_1, leaf_2, leaf_3}) {
    EXPECT_GT(closeness.at(center), closeness.at(leaf));
  }
  EXPECT_NEAR(closeness.at(center), 1.0 / 3.0, comparison_threshold);
  EXPECT_NEAR(closeness.at(leaf_1), 1.0 / 5.0, comparison_threshold);
}

TEST(UndirectedGraphCentralityTest, CompleteGraph) {
  // GIVEN
  undirected_graph<int, int> graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_1, vertex_id_3, 200);
  graph.add_edge(vertex_id_1, vertex_id_4, 300);
  graph.add_edge(vertex_id_2, vertex_id_3, 400);
  graph.add_edge(vertex_id_2, vertex_id_4, 500);
  graph.add_edge(vertex_id_3, vertex_id_4, 600);

  // WHEN
  const auto betweenness{betweenness_centrality(graph)};
  const auto closeness{closeness_centrality(graph)};

  // THEN
  constexpr double comparison_threshold{1e-9};
  for (const auto vertex_id :
       {vertex_id_1, vertex_id_2, vertex_id_3, vertex_id_4}) {
    EXPECT_NEAR(betweenness.at(vertex_id), 0.0, comparison_threshold);
    EXPECT_NEAR(closeness.at(vertex_id), 1.0 / 3.0, comparison_threshold);
  }
}

TEST(UndirectedGraphCentralityTest, DisconnectedGraphUsesReachableVertices) {
  // GIVEN
  undirected_graph<int, int> graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto isolated_vertex{graph.add_vertex(30)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);

  // WHEN
  const auto betweenness{betweenness_centrality(graph)};
  const auto closeness{closeness_centrality(graph)};

  // THEN
  EXPECT_DOUBLE_EQ(betweenness.at(vertex_id_1), 0.0);
  EXPECT_DOUBLE_EQ(betweenness.at(vertex_id_2), 0.0);
  EXPECT_DOUBLE_EQ(betweenness.at(isolated_vertex), 0.0);
  EXPECT_DOUBLE_EQ(closeness.at(vertex_id_1), 1.0);
  EXPECT_DOUBLE_EQ(closeness.at(vertex_id_2), 1.0);
  EXPECT_DOUBLE_EQ(closeness.at(isolated_vertex), 0.0);
}

TEST(UndirectedGraphCentralityTest, NonContiguousVertexIds) {
  // GIVEN
  undirected_graph<int, int> graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto removed_vertex_id{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  graph.remove_vertex(removed_vertex_id);
  graph.add_edge(vertex_id_1, vertex_id_3, 100);

  // WHEN
  const auto betweenness{betweenness_centrality(graph)};
  const auto closeness{closeness_centrality(graph)};

  // THEN
  ASSERT_EQ(betweenness.size(), 2);
  ASSERT_EQ(closeness.size(), 2);
  EXPECT_DOUBLE_EQ(betweenness.at(vertex_id_1), 0.0);
  EXPECT_DOUBLE_EQ(betweenness.at(vertex_id_3), 0.0);
  EXPECT_DOUBLE_EQ(closeness.at(vertex_id_1), 1.0);
  EXPECT_DOUBLE_EQ(closeness.at(vertex_id_3), 1.0);
}

TEST(DirectedGraphCentralityTest, DirectedPath) {
  // GIVEN
  directed_graph<int, int> graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_3, 200);

  // WHEN
  const auto betweenness{betweenness_centrality(graph)};
  const auto closeness{closeness_centrality(graph)};

  // THEN
  constexpr double comparison_threshold{1e-9};
  EXPECT_NEAR(betweenness.at(vertex_id_1), 0.0, comparison_threshold);
  EXPECT_NEAR(betweenness.at(vertex_id_2), 1.0, comparison_threshold);
  EXPECT_NEAR(betweenness.at(vertex_id_3), 0.0, comparison_threshold);

  EXPECT_NEAR(closeness.at(vertex_id_1), 1.0 / 3.0, comparison_threshold);
  EXPECT_NEAR(closeness.at(vertex_id_2), 1.0, comparison_threshold);
  EXPECT_NEAR(closeness.at(vertex_id_3), 0.0, comparison_threshold);
}

}  // namespace graaf::properties
