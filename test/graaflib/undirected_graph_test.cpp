#include <graaflib/graph.h>
#include <gtest/gtest.h>

namespace graaf
{

TEST(UndirectedGraphTest, DirectedGraphIsNoUndirectedGraph)
{
    // GIVEN - WHEN
    undirected_graph<int, int> graph {};

    // THEN
    ASSERT_FALSE(graph.is_directed());
    ASSERT_TRUE(graph.is_undirected());
}

TEST(UndirectedGraphTest, EdgeCount)
{
    // GIVEN
    undirected_graph<int, int> graph {};
    ASSERT_EQ(graph.edge_count(), 0);

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};

    // WHEN
    graph.add_edge(vertex_id_1, vertex_id_2, 100);

    // THEN
    ASSERT_EQ(graph.edge_count(), 1);
    ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));
    ASSERT_TRUE(graph.has_edge(vertex_id_2, vertex_id_1));
    ASSERT_EQ(get_weight(graph.get_edge(vertex_id_1, vertex_id_2)), 100);
}

TEST(UndirectedGraphTest, GetNeighbors)
{
    // GIVEN
    undirected_graph<int, int> graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};
    auto const vertex_id_3 {graph.add_vertex(30)};

    graph.add_edge(vertex_id_1, vertex_id_2, 100);
    graph.add_edge(vertex_id_1, vertex_id_3, 200);

    // WHEN - THEN
    auto const neighbors_vertex_1 {graph.get_neighbors(vertex_id_1)};
    ASSERT_EQ(neighbors_vertex_1.size(), 2);
    ASSERT_TRUE(neighbors_vertex_1.contains(vertex_id_2));
    ASSERT_TRUE(neighbors_vertex_1.contains(vertex_id_3));

    // WHEN - THEN
    // The edges are undirected, so vertex 2 has a neighbor
    auto const neighbors_vertex_2 {graph.get_neighbors(vertex_id_2)};
    ASSERT_EQ(neighbors_vertex_2.size(), 1);
    ASSERT_TRUE(neighbors_vertex_2.contains(vertex_id_1));

    // WHEN - THEN
    // The edges are undirected, so vertex 3 has a neighbor
    auto const neighbors_vertex_3 {graph.get_neighbors(vertex_id_3)};
    ASSERT_EQ(neighbors_vertex_3.size(), 1);
    ASSERT_TRUE(neighbors_vertex_3.contains(vertex_id_1));
}

} // namespace graaf
