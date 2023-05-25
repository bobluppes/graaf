#include <graaflib/algorithm/graph_traversal.h>

#include <graaflib/directed_graph.h>
#include <graaflib/undirected_graph.h>
#include <graaflib/types.h>

#include <vector>
#include <unordered_set>

#include <gtest/gtest.h>

namespace graaf::algorithm {

  template<typename T>
  struct TypedGraphTraversalTest : public testing::Test
  {
      using graph_t = T;
  };

  using graph_types = testing::Types<directed_graph<int, int>, undirected_graph<int, int>>;
  TYPED_TEST_CASE(TypedGraphTraversalTest, graph_types);

  TYPED_TEST(TypedGraphTraversalTest, MinimalGraph) {
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph{};

    const auto vertex_1{graph.add_vertex(10)};

    using vertex_vector_t = std::vector<vertex_id_t>;
    vertex_vector_t visited_vertices{};
    const auto record_vertex_callback{
        [&visited_vertices](vertex_id_t vertex_id) {
          visited_vertices.push_back(vertex_id);
        }};

    // WHEN
    traverse<search_strategy::DFS>(graph, vertex_1, record_vertex_callback);

    // THEN
    const vertex_vector_t expected_vertices{vertex_1};
    ASSERT_EQ(visited_vertices, expected_vertices);
  }

  TYPED_TEST(TypedGraphTraversalTest, SimpleGraph) {
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph{};

    const auto vertex_1{graph.add_vertex(10)};
    const auto vertex_2{graph.add_vertex(20)};

    // We add an edge from the vertex where we start the traversal
    // so it does not matter whether this is a directed or undirected graph
    graph.add_edge(vertex_1, vertex_2, 100);

    using vertex_vector_t = std::vector<vertex_id_t>;
    vertex_vector_t visited_vertices{};
    const auto record_vertex_callback{
        [&visited_vertices](vertex_id_t vertex_id) {
          visited_vertices.push_back(vertex_id);
        }};

    // WHEN
    traverse<search_strategy::DFS>(graph, vertex_1, record_vertex_callback);

    // THEN
    const vertex_vector_t expected_vertices{vertex_1, vertex_2};
    ASSERT_EQ(visited_vertices, expected_vertices);
  }

  TEST(GraphTraversalTest, DirectedGraphEdgeWrongDirection) {
    directed_graph<int, int> graph{};

    const auto vertex_1{graph.add_vertex(10)};
    const auto vertex_2{graph.add_vertex(20)};

    // The direction of the edge is from 2 -> 1
    graph.add_edge(vertex_2, vertex_1, 100);

    using vertex_vector_t = std::vector<vertex_id_t>;
    vertex_vector_t visited_vertices{};
    const auto record_vertex_callback{
        [&visited_vertices](vertex_id_t vertex_id) {
          visited_vertices.push_back(vertex_id);
        }};

    // WHEN - here vertex 1 has no neighbors due to the edge direction
    traverse<search_strategy::DFS>(graph, vertex_1, record_vertex_callback);

    // THEN
    const vertex_vector_t expected_vertices{vertex_1};
    ASSERT_EQ(visited_vertices, expected_vertices);
  }

  TYPED_TEST(TypedGraphTraversalTest, MoreComplexGraph) {
    // GIVEN
    using graph_t = typename TestFixture::graph_t;
    graph_t graph{};

    const auto vertex_1{graph.add_vertex(10)};
    const auto vertex_2{graph.add_vertex(20)};
    const auto vertex_3{graph.add_vertex(30)};
    const auto vertex_4{graph.add_vertex(40)};
    const auto vertex_5{graph.add_vertex(50)};

    // All edges are in the search direction, so the graph specialization does not matter
    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_1, vertex_3, 200);
    graph.add_edge(vertex_3, vertex_4, 300);
    graph.add_edge(vertex_3, vertex_5, 400);

    // We use a set here since the order of neighbor traversal is undefined
    using vertex_set_t = std::unordered_multiset<vertex_id_t>;
    vertex_set_t visited_vertices{};
    const auto record_vertex_callback{
        [&visited_vertices](vertex_id_t vertex_id) {
          visited_vertices.insert(vertex_id);
        }};

    // WHEN
    traverse<search_strategy::DFS>(graph, vertex_1, record_vertex_callback);

    // THEN
    const vertex_set_t expected_vertices{vertex_1, vertex_2, vertex_3, vertex_4, vertex_5};
    ASSERT_EQ(visited_vertices, expected_vertices);
  }

  TEST(GraphTraversalTest, MoreComplexDirectedGraphEdgeWrongDirection) {
    // GIVEN
    directed_graph<int, int> graph{};

    const auto vertex_1{graph.add_vertex(10)};
    const auto vertex_2{graph.add_vertex(20)};
    const auto vertex_3{graph.add_vertex(30)};
    const auto vertex_4{graph.add_vertex(40)};
    const auto vertex_5{graph.add_vertex(50)};

    // All edges are in the search direction, so the graph specialization does not matter
    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_1, vertex_3, 200);
    graph.add_edge(vertex_3, vertex_4, 300);
    graph.add_edge(vertex_5, vertex_3, 400);  // The direction here is from 5 -> 3

    // We use a set here since the order of neighbor traversal is undefined
    using vertex_set_t = std::unordered_multiset<vertex_id_t>;
    vertex_set_t visited_vertices{};
    const auto record_vertex_callback{
        [&visited_vertices](vertex_id_t vertex_id) {
          visited_vertices.insert(vertex_id);
        }};

    // WHEN
    traverse<search_strategy::DFS>(graph, vertex_1, record_vertex_callback);

    // THEN
    const vertex_set_t expected_vertices{vertex_1, vertex_2, vertex_3, vertex_4};
    ASSERT_EQ(visited_vertices, expected_vertices);
  }

} // namespace graaf::algorithm