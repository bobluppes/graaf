#include <graaflib/algorithm/shortest_path/bfs_shortest_path.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

namespace graaf::algorithm
{

namespace
{
    template<typename T>
    struct TypedShortestPathTest : public testing::Test
    {
        using graph_t = T;
    };

    TYPED_TEST_SUITE(TypedShortestPathTest, utils::fixtures::minimal_graph_types);
} // namespace

TYPED_TEST(TypedShortestPathTest, BfsMinimalShortestPath)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    auto const vertex_1 {graph.add_vertex(10)};

    // WHEN
    auto const path = bfs_shortest_path(graph, vertex_1, vertex_1);

    // THEN
    graph_path<int> const expected_path {{vertex_1}, 0};
    ASSERT_EQ(path, expected_path);
}

TYPED_TEST(TypedShortestPathTest, BfsNoAvailablePath)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};

    // WHEN
    auto const path = bfs_shortest_path(graph, vertex_1, vertex_2);

    // THEN
    ASSERT_FALSE(path.has_value());
}

TYPED_TEST(TypedShortestPathTest, BfsSimpleShortestPath)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};

    // We add an edge from the vertex where we start the traversal
    // so it does not matter whether this is a directed or undirected graph
    graph.add_edge(vertex_1, vertex_2, 100);

    // WHEN
    auto const path = bfs_shortest_path(graph, vertex_1, vertex_2);

    // THEN
    graph_path<int> const expected_path {
        {vertex_1, vertex_2},
        1
    };
    ASSERT_EQ(path, expected_path);
}

TYPED_TEST(TypedShortestPathTest, BfsMoreComplexShortestPath)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(50)};

    // All edges are in the search direction, so the graph specialization does not
    // matter
    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_2, vertex_3, 200);
    graph.add_edge(vertex_1, vertex_3, 300);
    graph.add_edge(vertex_3, vertex_4, 400);
    graph.add_edge(vertex_4, vertex_5, 500);
    graph.add_edge(vertex_3, vertex_5, 600);

    // WHEN
    auto const path = bfs_shortest_path(graph, vertex_1, vertex_5);

    // THEN
    graph_path<int> const expected_path {
        {vertex_1, vertex_3, vertex_5},
        2
    };
    ASSERT_EQ(path, expected_path);
}

TYPED_TEST(TypedShortestPathTest, BfsCyclicShortestPath)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(50)};

    // All edges are in the search direction, so the graph specialization does not
    // matter
    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_2, vertex_3, 200);
    graph.add_edge(vertex_3, vertex_4, 300);
    graph.add_edge(vertex_4, vertex_2, 300);
    graph.add_edge(vertex_3, vertex_5, 400);

    // WHEN
    auto const path = bfs_shortest_path(graph, vertex_1, vertex_5);

    // THEN
    graph_path<int> const expected_path {
        {vertex_1, vertex_2, vertex_3, vertex_5},
        3
    };
    ASSERT_EQ(path, expected_path);
}

TEST(ShortestPathTest, BfsDirectedrWrongDirectionShortestPath)
{
    // GIVEN
    directed_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(50)};

    // Edge between 2 and 3 is inverted, so path needs to take detour via 4
    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_3, vertex_2, 200);
    graph.add_edge(vertex_3, vertex_5, 300);
    graph.add_edge(vertex_2, vertex_4, 400);
    graph.add_edge(vertex_4, vertex_3, 500);

    // WHEN
    auto const path = bfs_shortest_path(graph, vertex_1, vertex_5);

    // THEN
    graph_path<int> const expected_path {
        {vertex_1, vertex_2, vertex_4, vertex_3, vertex_5},
        4
    };
    ASSERT_EQ(path, expected_path);
}

} // namespace graaf::algorithm
