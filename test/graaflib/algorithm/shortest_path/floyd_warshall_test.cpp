#include <graaflib/algorithm/shortest_path/floyd_warshall.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

namespace graaf::algorithm
{

namespace
{

    template<typename T>
    struct FloydWarshallTest : public testing::Test
    {
        using graph_t = typename T::first_type;
        using edge_t  = typename T::second_type;
    };
} // namespace

TYPED_TEST_SUITE(FloydWarshallTest, utils::fixtures::weighted_graph_types);

TYPED_TEST(FloydWarshallTest, UndirectedGraph)
{
    // GIVEN
    undirected_graph<int, int> graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};

    // adding edges to our graph
    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_2, vertex_3, 300);
    graph.add_edge(vertex_3, vertex_1, 300);

    auto shortest_paths                          = floyd_warshall_shortest_paths(graph);
    std::vector<std::vector<int>> expected_paths = {
        {  0, 100, 300},
        {100,   0, 300},
        {300, 300,   0}
    };

    ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DirectedGraph)
{
    // GIVEN
    directed_graph<int, int> graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};

    // adding edges to our graph
    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_2, vertex_3, 300);
    graph.add_edge(vertex_3, vertex_1, 300);

    auto shortest_paths                          = floyd_warshall_shortest_paths(graph);
    std::vector<std::vector<int>> expected_paths = {
        {  0, 100, 400},
        {600,   0, 300},
        {300, 400,   0}
    };

    ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DirectedGraphNoCycleNegativeWeight)
{
    directed_graph<int, int> graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(50)};
    auto const vertex_6 {graph.add_vertex(60)};

    // adding edges to our graph
    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_2, vertex_3, 50);
    graph.add_edge(vertex_2, vertex_4, -20);
    graph.add_edge(vertex_3, vertex_6, -3);
    graph.add_edge(vertex_4, vertex_6, 100);
    graph.add_edge(vertex_5, vertex_2, -75);

    auto NO_PATH                                 = INT_MAX;

    auto shortest_paths                          = floyd_warshall_shortest_paths(graph);
    std::vector<std::vector<int>> expected_paths = {
        {      0,     100,     150,      80, NO_PATH, 147},
        {NO_PATH,       0,      50,     -20, NO_PATH,  47},
        {NO_PATH, NO_PATH,       0, NO_PATH, NO_PATH,  -3},
        {NO_PATH, NO_PATH, NO_PATH,       0, NO_PATH, 100},
        {NO_PATH,     -75,     -25,     -95,       0, -28},
        {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH,   0}
    };

    ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DenseDirectedGraph)
{
    directed_graph<int, int> graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};

    // adding edges to our graph
    graph.add_edge(vertex_1, vertex_2, 10);
    graph.add_edge(vertex_2, vertex_3, 50);
    graph.add_edge(vertex_2, vertex_1, 20);
    graph.add_edge(vertex_3, vertex_2, 3);
    graph.add_edge(vertex_4, vertex_1, 10);
    graph.add_edge(vertex_4, vertex_3, 75);
    graph.add_edge(vertex_4, vertex_2, 12);
    graph.add_edge(vertex_1, vertex_4, 12);

    auto shortest_paths = floyd_warshall_shortest_paths(graph);
    std::vector<std::vector<int>> expected_paths {
        { 0, 10, 60, 12},
        {20,  0, 50, 32},
        {23,  3,  0, 35},
        {10, 12, 62,  0}
    };

    ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DenseUndirectedGraph)
{
    undirected_graph<int, int> graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};

    // adding edges to our graph
    graph.add_edge(vertex_1, vertex_2, 10);
    graph.add_edge(vertex_3, vertex_2, 3);
    graph.add_edge(vertex_4, vertex_1, 10);
    graph.add_edge(vertex_4, vertex_3, 75);
    graph.add_edge(vertex_4, vertex_2, 12);
    graph.add_edge(vertex_1, vertex_4, 12);

    auto shortest_paths = floyd_warshall_shortest_paths(graph);
    std::vector<std::vector<int>> expected_paths {
        { 0, 10, 13, 10},
        {10,  0,  3, 12},
        {13,  3,  0, 15},
        {10, 12, 15,  0}
    };

    ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, UndirectedGraphTwoComponents)
{
    undirected_graph<int, int> graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(40)};
    auto const vertex_6 {graph.add_vertex(40)};
    auto const vertex_7 {graph.add_vertex(40)};
    auto const vertex_8 {graph.add_vertex(40)};

    // adding edges to our graph
    graph.add_edge(vertex_1, vertex_2, 12);
    graph.add_edge(vertex_1, vertex_3, 11);
    graph.add_edge(vertex_1, vertex_5, 6);
    graph.add_edge(vertex_2, vertex_5, 14);
    graph.add_edge(vertex_2, vertex_4, 15);
    graph.add_edge(vertex_4, vertex_5, 9);
    graph.add_edge(vertex_4, vertex_3, 7);
    graph.add_edge(vertex_5, vertex_3, 7);

    graph.add_edge(vertex_6, vertex_7, 4);
    graph.add_edge(vertex_6, vertex_8, 2);
    graph.add_edge(vertex_7, vertex_8, 3);

    auto NO_PATH        = INT_MAX;

    auto shortest_paths = floyd_warshall_shortest_paths(graph);
    std::vector<std::vector<int>> expected_paths {
        {      0,      12,      11,      15,       6, NO_PATH, NO_PATH, NO_PATH},
        {     12,       0,      21,      15,      14, NO_PATH, NO_PATH, NO_PATH},
        {     11,      21,       0,       7,       7, NO_PATH, NO_PATH, NO_PATH},
        {     15,      15,       7,       0,       9, NO_PATH, NO_PATH, NO_PATH},
        {      6,      14,       7,       9,       0, NO_PATH, NO_PATH, NO_PATH},
        {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH,       0,       4,       2},
        {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH,       4,       0,       3},
        {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH,       2,       3,       0}
    };

    ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DirectedGraphTwoComponents)
{
    undirected_graph<int, int> graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(40)};
    auto const vertex_6 {graph.add_vertex(40)};
    auto const vertex_7 {graph.add_vertex(40)};
    auto const vertex_8 {graph.add_vertex(40)};

    // adding edges to our graph
    graph.add_edge(vertex_1, vertex_2, 12);
    graph.add_edge(vertex_1, vertex_3, 11);
    graph.add_edge(vertex_5, vertex_1, 6);
    graph.add_edge(vertex_2, vertex_5, 14);
    graph.add_edge(vertex_2, vertex_4, 15);
    graph.add_edge(vertex_5, vertex_4, 9);
    graph.add_edge(vertex_4, vertex_3, 7);
    graph.add_edge(vertex_3, vertex_5, 7);

    graph.add_edge(vertex_6, vertex_7, 4);
    graph.add_edge(vertex_6, vertex_8, 2);
    graph.add_edge(vertex_8, vertex_7, 3);

    auto NO_PATH        = INT_MAX;

    auto shortest_paths = floyd_warshall_shortest_paths(graph);
    std::vector<std::vector<int>> expected_paths {
        {      0,      12,      11,      15,       6, NO_PATH, NO_PATH, NO_PATH},
        {     12,       0,      21,      15,      14, NO_PATH, NO_PATH, NO_PATH},
        {     11,      21,       0,       7,       7, NO_PATH, NO_PATH, NO_PATH},
        {     15,      15,       7,       0,       9, NO_PATH, NO_PATH, NO_PATH},
        {      6,      14,       7,       9,       0, NO_PATH, NO_PATH, NO_PATH},
        {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH,       0,       4,       2},
        {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH,       4,       0,       3},
        {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH,       2,       3,       0}
    };

    ASSERT_EQ(shortest_paths, expected_paths);
}

} // namespace graaf::algorithm
