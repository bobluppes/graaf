#include <graaflib/algorithm/strongly_connected_components/common.h>
#include <graaflib/algorithm/strongly_connected_components/kosaraju.h>
#include <gtest/gtest.h>
#include <utils/scenarios/scenarios.h>

namespace graaf::algorithm
{

namespace
{

    bool are_set_vectors_equal(sccs_t const& vec1, sccs_t const& vec2)
    {
        // Make copies of the input vectors to avoid modifying the originals
        sccs_t sorted_vec1 = vec1;
        sccs_t sorted_vec2 = vec2;

        // Sort the inner vectors within each vector
        for(std::vector<vertex_id_t>& inner_vec: sorted_vec1)
        {
            std::sort(inner_vec.begin(), inner_vec.end());
        }
        for(std::vector<vertex_id_t>& inner_vec: sorted_vec2)
        {
            std::sort(inner_vec.begin(), inner_vec.end());
        }

        // Sort the outer vectors
        std::sort(sorted_vec1.begin(), sorted_vec1.end());
        std::sort(sorted_vec2.begin(), sorted_vec2.end());

        // Compare the sorted vectors for equality
        return sorted_vec1 == sorted_vec2;
    }

} // namespace

TEST(KosarajuTest, EmptySCCS)
{
    // GIVEN
    directed_graph<int, int> graph {};

    // WHEN
    sccs_t sccs = kosarajus_strongly_connected_components(graph);

    // THEN
    ASSERT_TRUE(sccs.empty());
}

TEST(KosarajuTest, EqualOutputSCCS)
{
    // GIVEN
    directed_graph<int, int> graph {};
    auto const vertex_id_1 = graph.add_vertex(1, 1);
    auto const vertex_id_2 = graph.add_vertex(2, 2);
    auto const vertex_id_3 = graph.add_vertex(3, 3);
    auto const vertex_id_4 = graph.add_vertex(4, 4);
    auto const vertex_id_5 = graph.add_vertex(5, 5);
    auto const vertex_id_6 = graph.add_vertex(6, 6);
    auto const vertex_id_7 = graph.add_vertex(7, 7);
    auto const vertex_id_8 = graph.add_vertex(8, 8);

    graph.add_edge(vertex_id_1, vertex_id_2, 1);
    graph.add_edge(vertex_id_2, vertex_id_3, 1);
    graph.add_edge(vertex_id_3, vertex_id_4, 1);
    graph.add_edge(vertex_id_3, vertex_id_1, 1);
    graph.add_edge(vertex_id_4, vertex_id_5, 1);
    graph.add_edge(vertex_id_5, vertex_id_8, 1);
    graph.add_edge(vertex_id_5, vertex_id_6, 1);
    graph.add_edge(vertex_id_6, vertex_id_7, 1);
    graph.add_edge(vertex_id_7, vertex_id_8, 1);
    graph.add_edge(vertex_id_7, vertex_id_5, 1);

    // WHEN
    sccs_t sccs          = kosarajus_strongly_connected_components(graph);
    sccs_t expected_sccs = {
        {1, 2, 3},
        {4},
        {5, 6, 7},
        {8}
    };

    // THEN
    ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TEST(KosarajuTest, KiteStructureEqualOutputSCCS)
{
    // GIVEN
    directed_graph<int, int> graph {};
    auto const vertex_id_1 = graph.add_vertex(1, 1);
    auto const vertex_id_2 = graph.add_vertex(2, 2);
    auto const vertex_id_3 = graph.add_vertex(3, 3);
    auto const vertex_id_4 = graph.add_vertex(4, 4);

    graph.add_edge(vertex_id_1, vertex_id_2, 1);
    graph.add_edge(vertex_id_2, vertex_id_3, 1);
    graph.add_edge(vertex_id_3, vertex_id_1, 1);
    graph.add_edge(vertex_id_2, vertex_id_4, 1);

    // WHEN
    sccs_t sccs          = kosarajus_strongly_connected_components(graph);
    sccs_t expected_sccs = {
        {1, 2, 3},
        {4}
    };

    // THEN
    ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TEST(KosarajuTest, TreeScenario)
{
    // GIVEN
    auto const [graph, vertex_ids] =
        utils::scenarios::create_tree_scenario<directed_graph<int, int>>();

    // WHEN
    sccs_t sccs          = kosarajus_strongly_connected_components(graph);
    sccs_t expected_sccs = {{0}, {1}, {2}, {3}, {4}};

    // THEN
    ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TEST(KosarajuTest, SimpleGraphScenario)
{
    // GIVEN
    auto const [graph, vertex_ids] =
        utils::scenarios::create_simple_graph_scenario<directed_graph<int, int>>();

    // WHEN
    sccs_t sccs          = kosarajus_strongly_connected_components(graph);
    sccs_t expected_sccs = {
        {2, 1, 0},
        {3},
        {4}
    };

    // THEN
    ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TEST(KosarajuTest, FullyConnectedGraphScenario)
{
    // GIVEN
    auto const [graph, vertex_ids] =
        utils::scenarios::create_fully_connected_graph_scenario<
            directed_graph<int, int>>();

    // WHEN
    sccs_t sccs          = kosarajus_strongly_connected_components(graph);
    sccs_t expected_sccs = {{0}, {1}, {2}, {3}, {4}};

    // THEN
    ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TEST(KosarajuTest, DisconnectedGraphScenario)
{
    // GIVEN
    auto const [graph, vertex_ids] =
        utils::scenarios::create_disconnected_graph_scenario<directed_graph<int, int>>();

    // WHEN
    sccs_t sccs          = kosarajus_strongly_connected_components(graph);
    sccs_t expected_sccs = {
        {0},
        {1},
        {2},
        {5, 4, 3}
    };

    // THEN
    ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

} // namespace graaf::algorithm
