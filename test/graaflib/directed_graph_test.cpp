#include <graaflib/directed_graph.h>

#include <gtest/gtest.h>

namespace graaf {

    TEST(DirectedGraphTest, SimpleGraafSize) {
        directed_graph<int, float> test_graph{};
        test_graph.add_vertex(5);
        test_graph.add_vertex(6);
        test_graph.add_vertex(7);
        EXPECT_EQ(test_graph.vertex_count(), 3);
    }

}