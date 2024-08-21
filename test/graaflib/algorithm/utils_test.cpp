#include <graaflib/algorithm/utils.h>
#include <gtest/gtest.h>

/**
 * Tests which miscellaneous utility functions contained
 * in utils.h should go here. Any test relating specifically
 * to the public graph interface should instead be located in
 * graph_test.cpp.
 */

namespace graaf
{

TEST(UtilsTest, Transpose)
{
    // GIVEN
    using graph_t = directed_graph<int, int>;
    graph_t graph {};
    auto const vertex_id_1 = graph.add_vertex(1);
    auto const vertex_id_2 = graph.add_vertex(2);
    auto const vertex_id_3 = graph.add_vertex(3);
    graph.add_edge(vertex_id_1, vertex_id_2, 100);
    graph.add_edge(vertex_id_2, vertex_id_3, 200);
    graph.add_edge(vertex_id_3, vertex_id_1, 300);

    // WHEN
    graph_t transposed_graph = get_transposed_graph(graph);

    // THEN
    EXPECT_EQ(get_weight(transposed_graph.get_edge(vertex_id_2, vertex_id_1)), 100);
    EXPECT_EQ(get_weight(transposed_graph.get_edge(vertex_id_3, vertex_id_2)), 200);
    EXPECT_EQ(get_weight(transposed_graph.get_edge(vertex_id_1, vertex_id_3)), 300);
}

} // namespace graaf
