#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>
#include <utils/scenarios/scenarios.h>

#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace graaf::algorithm
{

namespace
{

    template<typename T>
    struct TypedGraphTraversalTestBFS : public testing::Test
    {
        using graph_t = T;
    };

    TYPED_TEST_SUITE(TypedGraphTraversalTestBFS, utils::fixtures::minimal_graph_types);

    using seen_edges_t = std::unordered_multiset<edge_id_t, edge_id_hash>;
    using edge_order_t = std::unordered_map<edge_id_t, std::size_t, edge_id_hash>;

    /**
     * @brief Callback to record the traversed edges and their order.
     */
    struct record_edge_callback
    {
        seen_edges_t& seen_edges;
        edge_order_t& edge_order;
        mutable std::size_t edge_order_supplier {0};

        record_edge_callback(seen_edges_t& seen_edges, edge_order_t& edge_order)
            : seen_edges {seen_edges}
            , edge_order {edge_order}
        {}

        void operator()(edge_id_t const& edge) const
        {
            seen_edges.insert(edge);
            edge_order[edge] = edge_order_supplier++;
        }
    };

} // namespace

TYPED_TEST(TypedGraphTraversalTestBFS, MinimalGraphBFS)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    auto const vertex_1 {graph.add_vertex(10)};

    seen_edges_t seen_edges {};
    edge_order_t edge_order {};

    // WHEN
    breadth_first_traverse(
        graph, vertex_1, record_edge_callback {seen_edges, edge_order});

    // THEN
    seen_edges_t const expected_edges {};
    ASSERT_EQ(seen_edges, expected_edges);
}

TYPED_TEST(TypedGraphTraversalTestBFS, SimpleGraphBFS)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};

    // We add an edge from the vertex where we start the traversal
    // so it does not matter whether this is a directed or undirected graph
    graph.add_edge(vertex_1, vertex_2, 100);

    seen_edges_t seen_edges {};
    edge_order_t edge_order {};

    // WHEN
    breadth_first_traverse(
        graph, vertex_1, record_edge_callback {seen_edges, edge_order});

    seen_edges_t const expected_edges {
        {vertex_1, vertex_2}
    };
    ASSERT_EQ(seen_edges, expected_edges);
}

TEST(GraphTraversalTest, DirectedGraphEdgeWrongDirectionBFS)
{
    directed_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};

    // The direction of the edge is from 2 -> 1
    graph.add_edge(vertex_2, vertex_1, 100);

    seen_edges_t seen_edges {};
    edge_order_t edge_order {};

    // WHEN - here vertex 1 has no neighbors due to the edge direction
    breadth_first_traverse(
        graph, vertex_1, record_edge_callback {seen_edges, edge_order});

    // THEN - there was no edge to traverse
    seen_edges_t const expected_edges {};
    ASSERT_EQ(seen_edges, expected_edges);
}

TYPED_TEST(TypedGraphTraversalTestBFS, MoreComplexGraphBFS)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    auto const [graph, vertex_ids] {utils::scenarios::create_tree_scenario<graph_t>()};

    seen_edges_t seen_edges {};
    edge_order_t edge_order {};

    // WHEN
    breadth_first_traverse(
        graph, vertex_ids[0], record_edge_callback {seen_edges, edge_order});

    // THEN
    seen_edges_t const expected_edges {
        {vertex_ids[0], vertex_ids[1]},
        {vertex_ids[0], vertex_ids[2]},
        {vertex_ids[2], vertex_ids[3]},
        {vertex_ids[2], vertex_ids[4]}
    };
    ASSERT_EQ(seen_edges, expected_edges);

    // We do BFS, so all immediate neighbors must be traversed first before going
    // deeper in the graph
    ASSERT_TRUE(edge_order.at({vertex_ids[0], vertex_ids[1]}) <
                    edge_order.at({vertex_ids[2], vertex_ids[3]}) &&
                edge_order.at({vertex_ids[0], vertex_ids[1]}) <
                    edge_order.at({vertex_ids[2], vertex_ids[4]}));
    ASSERT_TRUE(edge_order.at({vertex_ids[0], vertex_ids[2]}) <
                    edge_order.at({vertex_ids[2], vertex_ids[3]}) &&
                edge_order.at({vertex_ids[0], vertex_ids[2]}) <
                    edge_order.at({vertex_ids[2], vertex_ids[4]}));
}

TYPED_TEST(TypedGraphTraversalTestBFS, MoreComplexGraphBFSImmediateTermination)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    auto const [graph, vertex_ids] {utils::scenarios::create_tree_scenario<graph_t>()};

    seen_edges_t seen_edges {};
    edge_order_t edge_order {};

    // Always returns true such that the search immediately terminates
    auto const immediate_termination_strategy {[](vertex_id_t const& /*vertex*/)
                                               {
                                                   return true;
                                               }};

    // WHEN
    breadth_first_traverse(graph,
                           vertex_ids[0],
                           record_edge_callback {seen_edges, edge_order},
                           immediate_termination_strategy);

    // THEN
    seen_edges_t const expected_edges {};
    ASSERT_EQ(seen_edges, expected_edges);
}

TYPED_TEST(TypedGraphTraversalTestBFS, MoreComplexGraphBFSTermination)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    auto const [graph, vertex_ids] {utils::scenarios::create_tree_scenario<graph_t>()};

    seen_edges_t seen_edges {};
    edge_order_t edge_order {};

    auto const termination_strategy {[target = vertex_ids[2]](vertex_id_t const& vertex)
                                     {
                                         return vertex == target;
                                     }};

    // WHEN
    breadth_first_traverse(graph,
                           vertex_ids[0],
                           record_edge_callback {seen_edges, edge_order},
                           termination_strategy);

    // THEN - Since there is no clear iteration order between the neighbors of the
    // 0-th vertex, there are two options for which edges we traversed
    seen_edges_t const expected_edges_option_1 {
        {vertex_ids[0], vertex_ids[1]},
        {vertex_ids[0], vertex_ids[2]}
    };
    seen_edges_t const expected_edges_option_2 {
        {vertex_ids[0], vertex_ids[2]}
    };
    ASSERT_TRUE(seen_edges == expected_edges_option_1 ||
                seen_edges == expected_edges_option_2);
}

TYPED_TEST(TypedGraphTraversalTestBFS, MoreComplexGraphBFSLaterTermination)
{
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    auto const [graph, vertex_ids] {utils::scenarios::create_tree_scenario<graph_t>()};

    seen_edges_t seen_edges {};
    edge_order_t edge_order {};

    // Here we terminate deeper in the tree
    auto const termination_strategy {[target = vertex_ids[3]](vertex_id_t const& vertex)
                                     {
                                         return vertex == target;
                                     }};

    // WHEN
    breadth_first_traverse(graph,
                           vertex_ids[0],
                           record_edge_callback {seen_edges, edge_order},
                           termination_strategy);

    // THEN - Since there is no clear iteration order between the neighbors of the
    // 0-th vertex, but we must have AT_LEAST seen the following edges
    seen_edges_t const expected_edges {
        {vertex_ids[0], vertex_ids[2]},
        {vertex_ids[2], vertex_ids[3]}
    };
    for(auto const& expected_edge: expected_edges)
    {
        ASSERT_TRUE(seen_edges.contains(expected_edge));
    }
}

TEST(GraphTraversalTest, MoreComplexDirectedGraphEdgeWrongDirectionBFS)
{
    // GIVEN
    directed_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(50)};

    // All edges are in the search direction, so the graph specialization does not
    // matter
    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_1, vertex_3, 200);
    graph.add_edge(vertex_3, vertex_4, 300);
    graph.add_edge(vertex_5, vertex_3, 400); // The direction here is from 5 -> 3

    seen_edges_t seen_edges {};
    edge_order_t edge_order {};

    // WHEN
    breadth_first_traverse(
        graph, vertex_1, record_edge_callback {seen_edges, edge_order});

    // THEN
    seen_edges_t const expected_edges {
        {vertex_1, vertex_2},
        {vertex_1, vertex_3},
        {vertex_3, vertex_4}
    };
    ASSERT_EQ(seen_edges, expected_edges);
}

} // namespace graaf::algorithm
