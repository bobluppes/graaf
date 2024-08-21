#include <graaflib/algorithm/coloring/greedy_graph_coloring.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

#include <unordered_map>
#include <unordered_set>

namespace graaf::algorithm
{

namespace
{

    template<typename T>
    struct TypedColoringTest : public testing::Test
    {
        using graph_t = T;
        using edge_t  = typename T::second_type;
    };

    TYPED_TEST_SUITE(GraphColoringTest, utils::fixtures::minimal_graph_types);

} // namespace

template<typename T>
struct GreedyGraphColoringTest : public testing::Test
{
    using graph_t = T;
};

TYPED_TEST_SUITE(GreedyGraphColoringTest, utils::fixtures::minimal_graph_types);

// Test case for an empty graph
TYPED_TEST(GreedyGraphColoringTest, EmptyGraph)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    // WHEN
    auto coloring = greedy_graph_coloring(graph);

    // THEN
    // Check if the obtained coloring is empty (no vertices to color)
    ASSERT_TRUE(coloring.empty());
}

TYPED_TEST(GreedyGraphColoringTest, BasicGraphColoring)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};

    // adding edges to our graph
    graph.add_edge(vertex_1, vertex_2, 1);
    graph.add_edge(vertex_2, vertex_3, 1);

    // WHEN
    auto coloring                                          = greedy_graph_coloring(graph);

    // THEN
    std::unordered_map<vertex_id_t, int> expected_coloring = {
        {0, 2},
        {1, 1},
        {2, 0}
    };

    // Check if the obtained coloring matches the expected coloring
    ASSERT_EQ(coloring, expected_coloring);
}

TYPED_TEST(GreedyGraphColoringTest, GraphWithNoEdges)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};

    // WHEN
    auto coloring                                          = greedy_graph_coloring(graph);

    std::unordered_map<vertex_id_t, int> expected_coloring = {
        {0, 0}, // Each vertex is assigned the same color
        {1, 0},
        {2, 0},
        {3, 0}
    };

    // THEN
    // Check if the obtained coloring matches the expected coloring
    ASSERT_EQ(coloring, expected_coloring);
}

// Test with a complete graph
TYPED_TEST(GreedyGraphColoringTest, CompleteGraph)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(1)};
    auto const vertex_2 {graph.add_vertex(2)};
    auto const vertex_3 {graph.add_vertex(3)};
    auto const vertex_4 {graph.add_vertex(4)};

    graph.add_edge(vertex_1, vertex_2, 1);
    graph.add_edge(vertex_1, vertex_3, 1);
    graph.add_edge(vertex_1, vertex_4, 1);
    graph.add_edge(vertex_2, vertex_4, 1);
    graph.add_edge(vertex_2, vertex_3, 1);
    graph.add_edge(vertex_3, vertex_4, 1);

    // WHEN
    auto coloring = greedy_graph_coloring(graph);

    // THEN
    // Verify that each vertex is assigned a unique color
    std::unordered_set<int> color_set;
    for(auto const& entry: coloring)
    {
        int color = entry.second;
        ASSERT_FALSE(color_set.count(color) > 0); // Check if the color is unique
        color_set.insert(color);
    }
}

TYPED_TEST(GreedyGraphColoringTest, DisconnectedComponents)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    // graph vertices
    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(50)};

    // Create disconnected components
    graph.add_edge(vertex_1, vertex_2,
                   1); // Component 1: Vertex 1 and 2 are connected
    graph.add_edge(vertex_3,
                   vertex_4,
                   1); // Component 2: Vertex 3 and 4 are
                       // Component 3: connected Vertex 5 is disconnected
    // WHEN
    auto coloring = greedy_graph_coloring(graph);

    // THEN
    // Verify that for each edge, adjacent vertices have different colors
    for(auto const& [edge_id, edge]: graph.get_edges())
    {
        auto const [u, v] {edge_id};
        int color_u = coloring[u];
        int color_v = coloring[v];
        ASSERT_TRUE(color_u != color_v);
    }
}

} // namespace graaf::algorithm
