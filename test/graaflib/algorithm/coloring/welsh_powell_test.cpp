#include <graaflib/algorithm/coloring/welsh_powell.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

#include <unordered_map>

namespace graaf::algorithm
{

template<typename T>
struct WelshPowellTest : public testing::Test
{
    using graph_t = T;
};

TYPED_TEST_SUITE(WelshPowellTest, utils::fixtures::minimal_undirected_graph_type);

// Test case for an empty graph
TYPED_TEST(WelshPowellTest, EmptyGraph)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    // WHEN
    auto coloring = welsh_powell_coloring(graph);

    // THEN
    // Check if the obtained coloring is empty (no vertices to color)
    ASSERT_TRUE(coloring.empty());
}

TYPED_TEST(WelshPowellTest, BasicGraphColoring)
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
    auto coloring                                          = welsh_powell_coloring(graph);

    // THEN
    std::unordered_map<vertex_id_t, int> expected_coloring = {
        {0, 1},
        {2, 1},
        {1, 0}
    };

    // Check if the obtained coloring matches the expected coloring
    ASSERT_EQ(coloring, expected_coloring);
}

TYPED_TEST(WelshPowellTest, GraphWithNoEdges)
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
    auto coloring                                          = welsh_powell_coloring(graph);

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
TYPED_TEST(WelshPowellTest, CompleteGraph)
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
    graph.add_edge(vertex_2, vertex_3, 1);
    graph.add_edge(vertex_2, vertex_4, 1);
    graph.add_edge(vertex_3, vertex_4, 1);

    // WHEN
    auto coloring                                          = welsh_powell_coloring(graph);

    // THEN
    std::unordered_map<vertex_id_t, int> expected_coloring = {
        {0, 3},
        {1, 2},
        {2, 1},
        {3, 0}
    };

    // Check if the obtained coloring matches the expected coloring
    ASSERT_EQ(coloring, expected_coloring);
}

TYPED_TEST(WelshPowellTest, DisconnectedComponents)
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
    auto coloring = welsh_powell_coloring(graph);

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
