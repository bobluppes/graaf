#include <graaflib/metrics/metrics.h>

#include <gtest/gtest.h>

#include <graaflib/graph.h>

namespace graaf::metrics {

    TEST(MetricsTest, DensityTest) {
        const graph<int> graph{
            {{0, 10}, {1, 11}, {2, 12}},
            {{0, 1}, {1, 2}}
        };
        EXPECT_FLOAT_EQ(density(graph), (1.0 / 3));
    };

}