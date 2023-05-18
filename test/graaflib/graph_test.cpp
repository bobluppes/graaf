#include <graaflib/directed_graph.h>
#include <graaflib/undirected_graph.h>

#include <gtest/gtest.h>

/**
 * Tests which test the common functionality of the graph
 * class go here. Any test specific to a graph specification
 * should go in the respective test files.
*/

namespace graaf {

    template<typename T>
    struct GraphTest : public testing::Test
    {
        using graph_t = T;
    };

    using graph_types = testing::Types<directed_graph<int, int>, undirected_graph<int, int>>;
    TYPED_TEST_CASE(GraphTest, graph_types);

    TYPED_TEST(GraphTest, VertexCount) {
        // GIVEN
        using graph_t = typename TestFixture::graph_t;
        graph_t graph{};
        ASSERT_EQ(graph.vertex_count(), 0);

        // WHEN - THEN
        const auto vertex_id_1{graph.add_vertex(10)};
        ASSERT_EQ(graph.vertex_count(), 1);
        ASSERT_TRUE(graph.has_vertex(vertex_id_1));
        ASSERT_EQ(graph.get_vertex(vertex_id_1), 10);

        // WHEN - THEN
        const auto vertex_id_2{graph.add_vertex(20)};
        ASSERT_EQ(graph.vertex_count(), 2);
        ASSERT_TRUE(graph.has_vertex(vertex_id_2));
        ASSERT_EQ(graph.get_vertex(vertex_id_2), 20);
    }

    TYPED_TEST(GraphTest, RemoveVertex) {
        // GIVEN
        using graph_t = typename TestFixture::graph_t;
        graph_t graph{};
        const auto vertex_id_1{graph.add_vertex(10)};
        const auto vertex_id_2{graph.add_vertex(20)};

        ASSERT_EQ(graph.vertex_count(), 2);

        // WHEN - THEN
        graph.remove_vertex(vertex_id_1);
        ASSERT_EQ(graph.vertex_count(), 1);
        ASSERT_FALSE(graph.has_vertex(vertex_id_1));
        ASSERT_TRUE(graph.has_vertex(vertex_id_2));

        // WHEN - THEN
        graph.remove_vertex(vertex_id_2);
        ASSERT_EQ(graph.vertex_count(), 0);
        ASSERT_FALSE(graph.has_vertex(vertex_id_1));
        ASSERT_FALSE(graph.has_vertex(vertex_id_2));
    }

    TYPED_TEST(GraphTest, RemoveEdge) {
        // GIVEN
        using graph_t = typename TestFixture::graph_t;
        graph_t graph{};

        const auto vertex_id_1{graph.add_vertex(10)};
        const auto vertex_id_2{graph.add_vertex(20)};

        graph.add_edge(vertex_id_1, vertex_id_2, 100);
        ASSERT_EQ(graph.edge_count(), 1);
        ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));

        // WHEN
        graph.remove_edge(vertex_id_1, vertex_id_2);

        // THEN
        ASSERT_EQ(graph.edge_count(), 0);
        ASSERT_FALSE(graph.has_edge(vertex_id_1, vertex_id_2));

        // Removing an edge does not remove the vertices
        ASSERT_EQ(graph.vertex_count(), 2);
        ASSERT_TRUE(graph.has_vertex(vertex_id_1));
        ASSERT_TRUE(graph.has_vertex(vertex_id_2));
    }

}