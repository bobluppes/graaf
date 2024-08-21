#include <graaflib/graph.h>
#include <graaflib/properties/vertex_properties.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

namespace graaf::properties
{

TEST(DirectedGraphPropertiesTest, VertexOutDegree)
{
    // GIVEN
    directed_graph<int, int> graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};
    auto const vertex_id_3 {graph.add_vertex(30)};
    auto const vertex_id_4 {graph.add_vertex(40)};

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

TEST(DirectedGraphPropertiesTest, VertexInDegree)
{
    // GIVEN
    directed_graph<int, int> graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};
    auto const vertex_id_3 {graph.add_vertex(30)};
    auto const vertex_id_4 {graph.add_vertex(40)};

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

TEST(DirectedGraphPropertiesTest, VertexDegree)
{
    // GIVEN
    directed_graph<int, int> graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};
    auto const vertex_id_3 {graph.add_vertex(30)};
    auto const vertex_id_4 {graph.add_vertex(40)};

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

TEST(UndirectedGraphPropertiesTest, VertexOutDegree)
{
    // GIVEN
    undirected_graph<int, int> graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};
    auto const vertex_id_3 {graph.add_vertex(30)};
    auto const vertex_id_4 {graph.add_vertex(40)};

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

TEST(UndirectedGraphPropertiesTest, VertexInDegree)
{
    // GIVEN
    undirected_graph<int, int> graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};
    auto const vertex_id_3 {graph.add_vertex(30)};
    auto const vertex_id_4 {graph.add_vertex(40)};

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

TEST(UndirectedGraphPropertiesTest, VertexDegree)
{
    // GIVEN
    undirected_graph<int, int> graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};
    auto const vertex_id_3 {graph.add_vertex(30)};
    auto const vertex_id_4 {graph.add_vertex(40)};

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

} // namespace graaf::properties
