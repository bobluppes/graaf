#include <graaflib/graph.h>
#include <gtest/gtest.h>

#include <algorithm>

namespace graaf {

TEST(UndirectedGraphTest, DirectedGraphIsNoUndirectedGraph) {
  // GIVEN - WHEN
  undirected_graph<int, int> graph{};

  // THEN
  ASSERT_FALSE(graph.is_directed());
  ASSERT_TRUE(graph.is_undirected());
}

TEST(UndirectedGraphTest, EdgeCount) {
  // GIVEN
  undirected_graph<int, int> graph{};
  ASSERT_EQ(graph.edge_count(), 0);

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, 100);

  // THEN
  ASSERT_EQ(graph.edge_count(), 1);
  ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));
  ASSERT_TRUE(graph.has_edge(vertex_id_2, vertex_id_1));
  ASSERT_EQ(get_weight(graph.get_edge(vertex_id_1, vertex_id_2)), 100);
}

TEST(UndirectedGraphTest, GetNeighbors) {
  // GIVEN
  undirected_graph<int, int> graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};

  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_1, vertex_id_3, 200);

  // WHEN - THEN
  const auto neighbors_vertex_1{graph.get_neighbors(vertex_id_1)};
  ASSERT_EQ(neighbors_vertex_1.size(), 2);
  ASSERT_NE(std::ranges::find(neighbors_vertex_1, vertex_id_2),
            neighbors_vertex_1.end());
  ASSERT_NE(std::ranges::find(neighbors_vertex_1, vertex_id_3),
            neighbors_vertex_1.end());

  // WHEN - THEN
  // The edges are undirected, so vertex 2 has a neighbor
  const auto neighbors_vertex_2{graph.get_neighbors(vertex_id_2)};
  ASSERT_EQ(neighbors_vertex_2.size(), 1);
  ASSERT_NE(std::ranges::find(neighbors_vertex_2, vertex_id_1),
            neighbors_vertex_2.end());

  // WHEN - THEN
  // The edges are undirected, so vertex 3 has a neighbor
  const auto neighbors_vertex_3{graph.get_neighbors(vertex_id_3)};
  ASSERT_EQ(neighbors_vertex_3.size(), 1);
  ASSERT_NE(std::ranges::find(neighbors_vertex_3, vertex_id_1),
            neighbors_vertex_3.end());
}

TEST(UndirectedGraphTest, SelfLoopIsASingleNeighbor) {
  // GIVEN
  undirected_graph<int, int> graph{};
  const auto vertex_id{graph.add_vertex(10)};

  // WHEN
  graph.add_edge(vertex_id, vertex_id, 100);

  // THEN
  ASSERT_EQ(graph.get_neighbors(vertex_id),
            (std::vector<vertex_id_t>{vertex_id}));

  // WHEN
  graph.remove_edge(vertex_id, vertex_id);

  // THEN
  ASSERT_TRUE(graph.get_neighbors(vertex_id).empty());
}

}  // namespace graaf