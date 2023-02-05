#include <graaflib/graph.h>

#include <gtest/gtest.h>

namespace graaf {

    TEST(GraafTest, SimpleGraafSize) {
        const graph<int> graph{
            {{0, 10}, {1, 11}, {2, 12}},
            {{0, 1}, {1, 2}}
        };
    EXPECT_EQ(graph.vertex_count(), 3);
}

}

