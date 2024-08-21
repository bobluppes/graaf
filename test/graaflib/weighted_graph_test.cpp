#include <graaflib/graph.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

#include <type_traits>
#include <utility>

namespace graaf
{

template<typename T>
struct WeightedGraphTest : public testing::Test
{
    using graph_t = typename T::first_type;
    using edge_t  = typename T::second_type;
};

TYPED_TEST_SUITE(WeightedGraphTest, utils::fixtures::weighted_graph_types);

TYPED_TEST(WeightedGraphTest, AddWeightedEdge)
{
    // GIVEN
    using graph_t  = typename TestFixture::graph_t;
    using edge_t   = typename TestFixture::edge_t;
    using weight_t = decltype(get_weight(std::declval<edge_t>()));

    graph_t graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};

    // WHEN
    graph.add_edge(vertex_id_1, vertex_id_2, edge_t {static_cast<weight_t>(3)});

    // THEN
    ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));
    ASSERT_EQ(get_weight(graph.get_edge(vertex_id_1, vertex_id_2)),
              static_cast<weight_t>(3));
}

template<typename T>
struct UnitWeightedGraphTest : public testing::Test
{
    using graph_t = typename T::first_type;
    using edge_t  = typename T::second_type;
};

TYPED_TEST_SUITE(UnitWeightedGraphTest, utils::fixtures::unit_weighted_graph_types);

TYPED_TEST(UnitWeightedGraphTest, AddUnitWeightedEdge)
{
    // GIVEN
    using graph_t  = typename TestFixture::graph_t;
    using edge_t   = typename TestFixture::edge_t;
    using weight_t = decltype(get_weight(std::declval<edge_t>()));

    graph_t graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};

    // WHEN
    graph.add_edge(vertex_id_1, vertex_id_2, edge_t {});

    // THEN
    ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));

    // By default each edge has a unit weight
    ASSERT_EQ(get_weight(graph.get_edge(vertex_id_1, vertex_id_2)),
              static_cast<weight_t>(1));
}

template<typename T>
struct UnweightedGraphTest : public testing::Test
{
    using graph_t = typename T::first_type;
    using edge_t  = typename T::second_type;
};

TYPED_TEST_SUITE(UnweightedGraphTest, utils::fixtures::unweighted_graph_types);

TYPED_TEST(UnweightedGraphTest, AddUnweightedEdge)
{
    // GIVEN
    using graph_t  = typename TestFixture::graph_t;
    using edge_t   = typename TestFixture::edge_t;
    using weight_t = decltype(get_weight(std::declval<edge_t>()));

    graph_t graph {};

    auto const vertex_id_1 {graph.add_vertex(10)};
    auto const vertex_id_2 {graph.add_vertex(20)};

    // WHEN
    graph.add_edge(vertex_id_1, vertex_id_2, edge_t {static_cast<weight_t>(42)});

    // THEN
    ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));

    // By default each edge has a unit weight
    ASSERT_EQ(graph.get_edge(vertex_id_1, vertex_id_2).val, static_cast<weight_t>(42));
}

} // namespace graaf
