#include <graaflib/directed_graph.h>

#include <gtest/gtest.h>

namespace graaf {

    TEST(DirectedGraphTest, SimpleGraafSize) {
        const directed_graph<int> test_graph{
            {{0, {0, 10}}, {1, {1, 11}}, {2, {2, 12}}},
            {{0, 1}, {1, 2}}
        };
        EXPECT_EQ(test_graph.vertex_count(), 3);
    }

}