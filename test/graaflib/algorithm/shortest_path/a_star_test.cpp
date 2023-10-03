#include <fmt/core.h>
#include <graaflib/algorithm/shortest_path/a_star.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

namespace graaf::algorithm {

namespace {

template <typename T>
struct AStarShortestPathTest : public testing::Test {
  using graph_t = typename T::first_type;
  using edge_t = typename T::second_type;
};

TYPED_TEST_SUITE(AStarShortestPathTest, utils::fixtures::weighted_graph_types);

template <typename T>
struct AStarShortestPathSignedTypesTest : public testing::Test {
  using graph_t = typename T::first_type;
  using edge_t = typename T::second_type;
};

TYPED_TEST_SUITE(AStarShortestPathSignedTypesTest,
                 utils::fixtures::weighted_graph_signed_types);

}  // namespace

// Graph with only one vertex.
TYPED_TEST(AStarShortestPathTest, AStarMinimalShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};

  // WHEN
  // The weight_t type annotation and static_cast are needed to avoid compiler
  // warnings.
  const auto heuristic = [](vertex_id_t vertex) -> weight_t {
    return static_cast<weight_t>(0);
  };
  const auto path = a_star_search(graph, vertex_id_1, vertex_id_1, heuristic);

  // THEN
  const graph_path<weight_t> expected_path{{vertex_id_1}, 0};
  ASSERT_EQ(path, expected_path);
}

// Find the shortest path between the only two vertices in a graph.
TYPED_TEST(AStarShortestPathTest, AStarSimpleShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(1)});

  const auto heuristic = [](vertex_id_t vertex) -> weight_t {
    return static_cast<weight_t>(0);
  };

  // WHEN
  const auto path = a_star_search(graph, vertex_id_1, vertex_id_2, heuristic);

  // THEN
  const graph_path<weight_t> expected_path{{vertex_id_1, vertex_id_2}, 1};
  ASSERT_EQ(path, expected_path);
}

// Graph where there's no path between the start and target vertices.
TYPED_TEST(AStarShortestPathTest, NoPathExistence) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  // Define start and target vertices
  vertex_id_t start_vertex = 0;
  vertex_id_t target_vertex = 5;

  // Define a heuristic function that always returns 0
  auto zero_heuristic = [](vertex_id_t vertex) -> weight_t {
    return static_cast<weight_t>(0);
  };

  // WHEN
  auto result =
      a_star_search(graph, start_vertex, target_vertex, zero_heuristic);

  // THEN
  // Check that the result is an empty optional
  ASSERT_FALSE(result.has_value());
}

// Find the shortest path between multiple possible paths in a graph.
TYPED_TEST(AStarShortestPathTest, MultiplePathsTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_1, vertex_id_3, edge_t{static_cast<weight_t>(2)});
  graph.add_edge(vertex_id_2, vertex_id_3, edge_t{static_cast<weight_t>(2)});

  // WHEN
  const auto heuristic = [](vertex_id_t vertex) -> weight_t {
    return static_cast<weight_t>(0);
  };
  const auto path = a_star_search(graph, vertex_id_1, vertex_id_3, heuristic);

  // THEN
  const graph_path<weight_t> expected_path{{vertex_id_1, vertex_id_3}, 2};
  ASSERT_EQ(path, expected_path);
}

// Suboptimal Path Test
TYPED_TEST(AStarShortestPathTest, AStarSuboptimalPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(2)});
  graph.add_edge(vertex_id_1, vertex_id_3, edge_t{static_cast<weight_t>(4)});
  graph.add_edge(vertex_id_2, vertex_id_3, edge_t{static_cast<weight_t>(3)});

  // WHEN
  const auto heuristic = [](vertex_id_t vertex) -> weight_t {
    return static_cast<weight_t>(10);  // Overestimate the remaining cost
  };
  const auto path = a_star_search(graph, vertex_id_1, vertex_id_3, heuristic);

  // THEN
  ASSERT_TRUE(path.has_value());  // Check if optional has a value
  // Note: The path might not be the shortest, but it should still be valid
}

// Negative Weight Test
TYPED_TEST(AStarShortestPathSignedTypesTest, AStarNegativeWeight) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  graph.add_edge(vertex_id_1, vertex_id_2,
                 edge_t{static_cast<weight_t>(-1)});  // Negative weight edge

  const auto heuristic = [](vertex_id_t vertex) -> weight_t {
    return static_cast<weight_t>(0);
  };

  // THEN
  // Taken from DijkstraNegativeWeight
  ASSERT_THROW(
      {
        try {
          // Call the get_edge function for non-existing vertices
          [[maybe_unused]] const auto path{
              a_star_search(graph, vertex_id_1, vertex_id_2, heuristic)};
          // If the above line doesn't throw an exception, fail the test
          FAIL()
              << "Expected std::invalid_argument exception, but no exception "
                 "was thrown.";
        } catch (const std::invalid_argument &ex) {
          // Verify that the exception message contains the expected error
          // message
          EXPECT_EQ(
              ex.what(),
              fmt::format(
                  "Negative edge weight [{}] between vertices [{}] -> [{}].",
                  -1, vertex_id_1, vertex_id_2));
          throw;
        }
      },
      std::invalid_argument);
}

// Heuristic Impact Test
TYPED_TEST(AStarShortestPathTest, AStarHeuristicImpact) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_2, vertex_id_3, edge_t{static_cast<weight_t>(2)});
  graph.add_edge(vertex_id_1, vertex_id_3, edge_t{static_cast<weight_t>(3)});
  graph.add_edge(vertex_id_1, vertex_id_4, edge_t{static_cast<weight_t>(2)});
  graph.add_edge(vertex_id_3, vertex_id_4, edge_t{static_cast<weight_t>(1)});

  const auto start_vertex = vertex_id_1;
  const auto target_vertex = vertex_id_3;

  // Define two different heuristic functions
  const auto heuristic1 = [](vertex_id_t vertex) -> weight_t {
    return static_cast<weight_t>(0);
  };  // Underestimating heuristic
  const auto heuristic2 = [](vertex_id_t vertex) -> weight_t {
    return static_cast<weight_t>(10);
  };  // Overestimating heuristic

  // WHEN
  const auto path_with_underestimating_heuristic =
      a_star_search(graph, start_vertex, target_vertex, heuristic1);
  const auto path_with_overestimating_heuristic =
      a_star_search(graph, start_vertex, target_vertex, heuristic2);

  // THEN
  // Verify that the path with the underestimating heuristic is shorter
  ASSERT_TRUE(path_with_underestimating_heuristic.has_value());
  ASSERT_TRUE(path_with_overestimating_heuristic.has_value());
  ASSERT_LT(path_with_underestimating_heuristic->total_weight,
            path_with_overestimating_heuristic->total_weight);
}

}  // namespace graaf::algorithm