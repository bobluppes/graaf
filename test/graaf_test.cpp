#include <gtest/gtest.h>

#include "../src/graaf.h"

TEST(GraafTest, SimpleGraafSize) {
    const graaf::graaf<int> graph{
        {{0, 10}, {1, 11}, {2, 12}},
        {{0, 1}, {1, 2}}
    };
    EXPECT_EQ(graph.number_of_vertices(), 3);
}

