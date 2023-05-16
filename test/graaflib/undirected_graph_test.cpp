#include <graaflib/undirected_graph.h>

#include <gtest/gtest.h>

namespace graaf {

    TEST(UndirectedGraphTest, SimpleGraafSize) {
        undirected_graph<int, float> test_graph{};
        test_graph.add_vertex(1);
        test_graph.add_vertex(2);
        test_graph.add_vertex(3);
        EXPECT_EQ(test_graph.vertex_count(), 3);
    }
    
}