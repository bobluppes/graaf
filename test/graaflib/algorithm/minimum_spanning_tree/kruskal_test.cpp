#include <fmt/core.h>
#include <graaflib/algorithm/minimum_spanning_tree/kruskal.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>
#include <utils/scenarios/scenarios.h>

#include <utility>

namespace graaf::algorithm
{

template<typename T>
struct MSTTest : public testing::Test
{
    using edge_t = typename T::second_type;
};

TYPED_TEST_SUITE(MSTTest, utils::fixtures::weighted_graph_types);

TYPED_TEST(MSTTest, SparseGraph)
{
    undirected_graph<int, int> graph {};
    auto const vertex_1 = graph.add_vertex(1);
    auto const vertex_2 = graph.add_vertex(2);
    auto const vertex_3 = graph.add_vertex(3);
    auto const vertex_4 = graph.add_vertex(4);

    graph.add_edge(vertex_3, vertex_1, 4);
    graph.add_edge(vertex_2, vertex_4, 6);
    graph.add_edge(vertex_3, vertex_4, 5);
    graph.add_edge(vertex_1, vertex_2, 15);

    auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
    std::vector<edge_id_t> expected_mst {
        {vertex_1, vertex_3},
        {vertex_3, vertex_4},
        {vertex_2, vertex_4}
    };

    ASSERT_EQ(expected_mst, mst);
}

TYPED_TEST(MSTTest, TwoComponents)
{
    undirected_graph<int, float> graph {};

    auto const vertex_1 = graph.add_vertex(1);
    auto const vertex_2 = graph.add_vertex(2);
    auto const vertex_3 = graph.add_vertex(3);
    auto const vertex_4 = graph.add_vertex(4);

    auto const vertex_5 = graph.add_vertex(5);
    auto const vertex_6 = graph.add_vertex(6);
    auto const vertex_7 = graph.add_vertex(7);
    auto const vertex_8 = graph.add_vertex(8);
    auto const vertex_9 = graph.add_vertex(9);

    graph.add_edge(vertex_3, vertex_1, 0.3f);
    graph.add_edge(vertex_2, vertex_4, 0.14f);
    graph.add_edge(vertex_3, vertex_4, -5.3f);
    graph.add_edge(vertex_1, vertex_2, 223.0f);

    graph.add_edge(vertex_5, vertex_6, 2.0f);
    graph.add_edge(vertex_7, vertex_8, 4.0f);
    graph.add_edge(vertex_9, vertex_8, -23.0f);
    graph.add_edge(vertex_6, vertex_9, 3.0f);
    graph.add_edge(vertex_8, vertex_6, 0.15f);

    auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
    std::vector<edge_id_t> expected_mst {
        {vertex_8, vertex_9},
        {vertex_3, vertex_4},
        {vertex_2, vertex_4},
        {vertex_6, vertex_8},
        {vertex_1, vertex_3},
        {vertex_5, vertex_6},
        {vertex_7, vertex_8}
    };

    ASSERT_EQ(expected_mst, mst);
}

TYPED_TEST(MSTTest, EqualEdgeWeight)
{
    undirected_graph<int, int> graph {};
    auto const vertex_1 = graph.add_vertex(1);
    auto const vertex_2 = graph.add_vertex(2);
    auto const vertex_3 = graph.add_vertex(3);
    auto const vertex_4 = graph.add_vertex(4);

    graph.add_edge(vertex_3, vertex_1, 5);
    graph.add_edge(vertex_2, vertex_4, 5);
    graph.add_edge(vertex_3, vertex_4, 5);
    graph.add_edge(vertex_1, vertex_2, 5);
    graph.add_edge(vertex_4, vertex_1, 5);

    auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
    std::vector<edge_id_t> expected_mst {
        {vertex_1, vertex_2},
        {vertex_1, vertex_3},
        {vertex_1, vertex_4}
    };

    ASSERT_EQ(expected_mst, mst);
}

TYPED_TEST(MSTTest, CompleteGraph)
{
    undirected_graph<int, int> graph {};
    auto const vertex_1 = graph.add_vertex(1);
    auto const vertex_2 = graph.add_vertex(2);
    auto const vertex_3 = graph.add_vertex(3);
    auto const vertex_4 = graph.add_vertex(4);

    graph.add_edge(vertex_1, vertex_2, 35);
    graph.add_edge(vertex_1, vertex_3, 4);
    graph.add_edge(vertex_1, vertex_4, 45);
    graph.add_edge(vertex_2, vertex_4, 6);
    graph.add_edge(vertex_2, vertex_3, 55);
    graph.add_edge(vertex_3, vertex_4, 5);

    auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
    std::vector<edge_id_t> expected_mst {
        {vertex_1, vertex_3},
        {vertex_3, vertex_4},
        {vertex_2, vertex_4}
    };

    ASSERT_EQ(expected_mst, mst);
}

TYPED_TEST(MSTTest, NullGraph)
{
    undirected_graph<int, float> graph {};

    auto const vertex_1 = graph.add_vertex(1);
    auto const vertex_2 = graph.add_vertex(2);
    auto const vertex_3 = graph.add_vertex(3);
    auto const vertex_4 = graph.add_vertex(4);

    auto mst            = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
    std::vector<edge_id_t> example_mst {
        {vertex_3, vertex_4},
        {vertex_2, vertex_4},
        {vertex_1, vertex_3}
    };

    ASSERT_NE(example_mst, mst);
}

struct custom_vertex
{
    int vertex_ {};
    std::string name {};
};

struct custom_edge : public graaf::weighted_edge<int>
{
  public:
    int weight_ {};

    [[nodiscard]]
    int get_weight() const noexcept override
    {
        return weight_;
    }

    custom_edge(int weight)
        : weight_ {weight} {};
    custom_edge() {};
    ~custom_edge() {};

    // Providing '<' and '!=' operators for sorting edges
    bool operator<(custom_edge const& e) const noexcept
    {
        return this->weight_ < e.weight_;
    }

    bool operator!=(custom_edge const& e) const noexcept
    {
        return this->weight_ != e.weight_;
    }
};

TYPED_TEST(MSTTest, CustomEdgeVertexOneComponentGraph)
{
    undirected_graph<custom_vertex, custom_edge> graph {};

    auto const vertex_1 = graph.add_vertex(custom_vertex {1, "Custom vertex 1"});
    auto const vertex_2 = graph.add_vertex(custom_vertex {2, "Custom vertex 2"});
    auto const vertex_3 = graph.add_vertex(custom_vertex {3, "Custom vertex 3"});
    auto const vertex_4 = graph.add_vertex(custom_vertex {4, "Custom vertex 4"});

    graph.add_edge(vertex_3, vertex_1, 4);
    graph.add_edge(vertex_2, vertex_4, 6);
    graph.add_edge(vertex_3, vertex_4, 5);
    graph.add_edge(vertex_1, vertex_2, 16);

    auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
    std::vector<edge_id_t> expected_mst {
        {vertex_1, vertex_3},
        {vertex_3, vertex_4},
        {vertex_2, vertex_4}
    };

    ASSERT_EQ(expected_mst, mst);
}

} // namespace graaf::algorithm
