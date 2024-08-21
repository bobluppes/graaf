#include <fmt/core.h>
#include <graaflib/algorithm/clique_detection/bron_kerbosch.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

#include <random>

namespace graaf::algorithm
{
void sort_vectors(std::vector<std::vector<vertex_id_t>>& vec1,
                  std::vector<std::vector<vertex_id_t>>& vec2)
{
    // Sort 1D vectors
    for(std::vector<vertex_id_t>& inner_vec: vec1)
    {
        std::sort(inner_vec.begin(), inner_vec.end());
    }
    for(std::vector<vertex_id_t>& inner_vec: vec2)
    {
        std::sort(inner_vec.begin(), inner_vec.end());
    }

    // Sort 2D vectors
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());
}

namespace
{
    template<typename T>
    struct BronKerbosch : public testing::Test
    {
        using graph_t = T;
    };

    using graph_types = testing::Types<undirected_graph<int, int>>;

    TYPED_TEST_SUITE(BronKerbosch, graph_types);
} // namespace

TYPED_TEST(BronKerbosch, ThreeCliques)
{
    undirected_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(1)};
    auto const vertex_2 {graph.add_vertex(2)};
    auto const vertex_3 {graph.add_vertex(3)};
    auto const vertex_4 {graph.add_vertex(4)};
    auto const vertex_5 {graph.add_vertex(5)};

    graph.add_edge(vertex_1, vertex_2, 1);
    graph.add_edge(vertex_1, vertex_3, 1);
    graph.add_edge(vertex_3, vertex_2, 1);
    graph.add_edge(vertex_3, vertex_4, 1);

    auto cliques = bron_kerbosch(graph);
    std::vector<std::vector<vertex_id_t>> expected_cliques {
        {vertex_1, vertex_2, vertex_3},
        {vertex_3, vertex_4},
        {vertex_5}
    };

    sort_vectors(cliques, expected_cliques);

    ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, OneClique)
{
    undirected_graph<int, int> graph {};

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

    auto cliques = bron_kerbosch(graph);
    std::vector<std::vector<vertex_id_t>> expected_cliques {
        {vertex_1, vertex_2, vertex_3, vertex_4}
    };

    sort_vectors(cliques, expected_cliques);
    ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, FourCliques)
{
    undirected_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(1)};
    auto const vertex_2 {graph.add_vertex(2)};
    auto const vertex_3 {graph.add_vertex(3)};
    auto const vertex_4 {graph.add_vertex(4)};
    auto const vertex_5 {graph.add_vertex(5)};
    auto const vertex_6 {graph.add_vertex(6)};
    auto const vertex_7 {graph.add_vertex(7)};

    graph.add_edge(vertex_1, vertex_2, 1);
    graph.add_edge(vertex_1, vertex_3, 1);
    graph.add_edge(vertex_2, vertex_3, 1);

    graph.add_edge(vertex_4, vertex_5, 1);
    graph.add_edge(vertex_5, vertex_6, 1);
    graph.add_edge(vertex_6, vertex_7, 1);

    auto cliques = bron_kerbosch(graph);
    std::vector<std::vector<vertex_id_t>> expected_cliques {
        {vertex_1, vertex_2, vertex_3},
        {vertex_4, vertex_5},
        {vertex_6, vertex_7},
        {vertex_6, vertex_5}
    };

    sort_vectors(cliques, expected_cliques);
    ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, GraphPentogram)
{
    undirected_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(1)};
    auto const vertex_2 {graph.add_vertex(2)};
    auto const vertex_3 {graph.add_vertex(3)};
    auto const vertex_4 {graph.add_vertex(4)};
    auto const vertex_5 {graph.add_vertex(5)};
    auto const vertex_6 {graph.add_vertex(6)};
    auto const vertex_7 {graph.add_vertex(7)};

    graph.add_edge(vertex_1, vertex_2, 1);
    graph.add_edge(vertex_1, vertex_7, 1);
    graph.add_edge(vertex_1, vertex_4, 1);
    graph.add_edge(vertex_4, vertex_7, 1);
    graph.add_edge(vertex_2, vertex_7, 1);
    graph.add_edge(vertex_2, vertex_3, 1);
    graph.add_edge(vertex_3, vertex_7, 1);
    graph.add_edge(vertex_3, vertex_6, 1);
    graph.add_edge(vertex_6, vertex_7, 1);
    graph.add_edge(vertex_5, vertex_6, 1);
    graph.add_edge(vertex_5, vertex_7, 1);
    graph.add_edge(vertex_4, vertex_5, 1);

    auto cliques = bron_kerbosch(graph);
    std::vector<std::vector<vertex_id_t>> expected_cliques {
        {vertex_1, vertex_2, vertex_7},
        {vertex_1, vertex_4, vertex_7},
        {vertex_2, vertex_3, vertex_7},
        {vertex_3, vertex_6, vertex_7},
        {vertex_4, vertex_5, vertex_7},
        {vertex_5, vertex_6, vertex_7}
    };
    sort_vectors(cliques, expected_cliques);

    ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, GraphTriangle)
{
    undirected_graph<int, int> graph {};

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

    auto cliques = bron_kerbosch(graph);
    std::vector<std::vector<vertex_id_t>> expected_cliques {
        {vertex_1, vertex_2, vertex_3, vertex_4}
    };
    sort_vectors(cliques, expected_cliques);

    ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, GraphCone)
{
    undirected_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(1)};
    auto const vertex_2 {graph.add_vertex(2)};
    auto const vertex_3 {graph.add_vertex(3)};
    auto const vertex_4 {graph.add_vertex(4)};
    auto const vertex_5 {graph.add_vertex(4)};

    // Bottom
    graph.add_edge(vertex_1, vertex_2, 1);
    graph.add_edge(vertex_1, vertex_3, 1);
    graph.add_edge(vertex_1, vertex_4, 1);
    graph.add_edge(vertex_2, vertex_3, 1);
    graph.add_edge(vertex_2, vertex_4, 1);
    graph.add_edge(vertex_3, vertex_4, 1);

    // Top
    graph.add_edge(vertex_5, vertex_1, 1);
    graph.add_edge(vertex_5, vertex_2, 1);
    graph.add_edge(vertex_5, vertex_3, 1);
    graph.add_edge(vertex_5, vertex_4, 1);

    auto cliques = bron_kerbosch(graph);
    std::vector<std::vector<vertex_id_t>> expected_cliques {
        {vertex_1, vertex_2, vertex_3, vertex_4, vertex_5}
    };
    sort_vectors(cliques, expected_cliques);

    ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, GraphEightSideStar)
{
    undirected_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(1)};
    auto const vertex_2 {graph.add_vertex(2)};
    auto const vertex_3 {graph.add_vertex(3)};
    auto const vertex_4 {graph.add_vertex(4)};
    auto const vertex_5 {graph.add_vertex(5)};
    auto const vertex_6 {graph.add_vertex(6)};
    auto const vertex_7 {graph.add_vertex(7)};
    auto const vertex_8 {graph.add_vertex(8)};
    auto const vertex_9 {graph.add_vertex(9)};
    auto const vertex_10 {graph.add_vertex(10)};
    auto const vertex_11 {graph.add_vertex(11)};
    auto const vertex_12 {graph.add_vertex(12)};
    auto const vertex_13 {graph.add_vertex(13)};
    auto const vertex_14 {graph.add_vertex(14)};
    auto const vertex_15 {graph.add_vertex(15)};
    auto const vertex_16 {graph.add_vertex(16)};

    graph.add_edge(vertex_1, vertex_2, 1);
    graph.add_edge(vertex_1, vertex_15, 1);
    graph.add_edge(vertex_2, vertex_15, 1);

    graph.add_edge(vertex_2, vertex_4, 1);
    graph.add_edge(vertex_2, vertex_3, 1);
    graph.add_edge(vertex_3, vertex_4, 1);

    graph.add_edge(vertex_4, vertex_6, 1);
    graph.add_edge(vertex_4, vertex_5, 1);
    graph.add_edge(vertex_5, vertex_6, 1);

    graph.add_edge(vertex_6, vertex_7, 1);
    graph.add_edge(vertex_6, vertex_8, 1);
    graph.add_edge(vertex_7, vertex_8, 1);

    graph.add_edge(vertex_8, vertex_9, 1);
    graph.add_edge(vertex_8, vertex_10, 1);
    graph.add_edge(vertex_9, vertex_10, 1);

    graph.add_edge(vertex_10, vertex_11, 1);
    graph.add_edge(vertex_10, vertex_12, 1);
    graph.add_edge(vertex_11, vertex_12, 1);

    graph.add_edge(vertex_12, vertex_13, 1);
    graph.add_edge(vertex_12, vertex_14, 1);
    graph.add_edge(vertex_13, vertex_14, 1);

    graph.add_edge(vertex_14, vertex_15, 1);
    graph.add_edge(vertex_14, vertex_16, 1);
    graph.add_edge(vertex_15, vertex_16, 1);

    auto cliques = bron_kerbosch(graph);
    std::vector<std::vector<vertex_id_t>> expected_cliques {
        { vertex_1,  vertex_2, vertex_15},
        { vertex_2,  vertex_3,  vertex_4},
        { vertex_5,  vertex_4,  vertex_6},
        { vertex_7,  vertex_6,  vertex_8},
        { vertex_8,  vertex_9, vertex_10},
        {vertex_10, vertex_11, vertex_12},
        {vertex_12, vertex_13, vertex_14},
        {vertex_14, vertex_15, vertex_16},
    };
    sort_vectors(cliques, expected_cliques);

    ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, DensePyramidGraph)
{
    undirected_graph<int, int> graph {};

    auto const vertex_1 = graph.add_vertex(10);
    auto const vertex_2 = graph.add_vertex(20);
    auto const vertex_3 = graph.add_vertex(30);
    auto const vertex_4 = graph.add_vertex(40);
    auto const vertex_5 = graph.add_vertex(50);
    auto const vertex_6 = graph.add_vertex(60);
    auto const vertex_7 = graph.add_vertex(70);

    graph.add_edge(vertex_1, vertex_2, 1);
    graph.add_edge(vertex_6, vertex_7, 1);
    graph.add_edge(vertex_1, vertex_7, 1);
    graph.add_edge(vertex_2, vertex_7, 1);
    graph.add_edge(vertex_1, vertex_6, 1);
    graph.add_edge(vertex_2, vertex_6, 1);

    graph.add_edge(vertex_2, vertex_3, 1);
    graph.add_edge(vertex_2, vertex_5, 1);
    graph.add_edge(vertex_3, vertex_6, 1);
    graph.add_edge(vertex_5, vertex_6, 1);
    graph.add_edge(vertex_3, vertex_5, 1);

    graph.add_edge(vertex_3, vertex_4, 1);
    graph.add_edge(vertex_5, vertex_4, 1);

    auto cliques = bron_kerbosch(graph);
    std::vector<std::vector<vertex_id_t>> expected_cliques {
        {vertex_1, vertex_2, vertex_6, vertex_7},
        {vertex_2, vertex_6, vertex_3, vertex_5},
        {vertex_3, vertex_4, vertex_5}
    };
    sort_vectors(cliques, expected_cliques);

    ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, GraphTwoLines)
{
    undirected_graph<int, int> graph {};

    auto const vertex_1 = graph.add_vertex(10);
    auto const vertex_2 = graph.add_vertex(20);
    auto const vertex_3 = graph.add_vertex(30);
    auto const vertex_4 = graph.add_vertex(40);
    auto const vertex_5 = graph.add_vertex(50);
    auto const vertex_6 = graph.add_vertex(60);
    auto const vertex_7 = graph.add_vertex(70);
    auto const vertex_8 = graph.add_vertex(80);

    graph.add_edge(vertex_2, vertex_1, 1);
    graph.add_edge(vertex_2, vertex_3, 1);
    graph.add_edge(vertex_3, vertex_4, 1);

    graph.add_edge(vertex_5, vertex_6, 1);
    graph.add_edge(vertex_6, vertex_7, 1);

    auto cliques = bron_kerbosch(graph);
    std::vector<std::vector<vertex_id_t>> expected_cliques {
        {vertex_1, vertex_2},
        {vertex_2, vertex_3},
        {vertex_3, vertex_4},
        {vertex_5, vertex_6},
        {vertex_6, vertex_7},
        {vertex_8}
    };

    sort_vectors(cliques, expected_cliques);

    ASSERT_EQ(cliques, expected_cliques);
}
}; // namespace graaf::algorithm
