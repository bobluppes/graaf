#include <graaflib/graph.h>
#include <gtest/gtest.h>

namespace graaf
{

/**
 * DIRECTED GRAPH
 */

TEST(GraphTraitsTest, DirectedGraphPrimitiveType)
{
    // GIVEN - WHEN
    directed_graph<int, int> graph {};

    // THEN The graph is directed
    ASSERT_TRUE(graph.is_directed());
    ASSERT_FALSE(graph.is_undirected());
}

TEST(GraphTraitsTest, DirectedGraphNonPrimitiveType)
{
    // GIVEN - WHEN
    struct my_edge
    {};

    directed_graph<int, my_edge> graph {};

    // THEN The graph is directed
    ASSERT_TRUE(graph.is_directed());
    ASSERT_FALSE(graph.is_undirected());
}

/**
 * UNDIRECTED GRAPH
 */

TEST(GraphTraitsTest, UndirectedGraphPrimitiveType)
{
    // GIVEN - WHEN
    undirected_graph<int, int> graph {};

    // THEN The graph is undirected
    ASSERT_TRUE(graph.is_undirected());
    ASSERT_FALSE(graph.is_directed());
}

TEST(GraphTraitsTest, UndirectedGraphNonPrimitiveType)
{
    // GIVEN - WHEN
    struct my_edge
    {};

    undirected_graph<int, my_edge> graph {};

    // THEN The graph is undirected
    ASSERT_TRUE(graph.is_undirected());
    ASSERT_FALSE(graph.is_directed());
}

} // namespace graaf
