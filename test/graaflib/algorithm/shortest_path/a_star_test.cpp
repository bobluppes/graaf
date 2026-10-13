#include <fmt/core.h>
#include <graaflib/algorithm/shortest_path/a_star.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

#include <limits>
#include <random>

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
  // The heuristic returns the same value for every vertex, so it is
  // consistent (it trivially satisfies the triangle inequality) and does not
  // break optimality: the shortest path (1 -> 3 directly, cost 4) is still
  // found.
  const graph_path<weight_t> expected_path{{vertex_id_1, vertex_id_3}, 4};
  ASSERT_EQ(path, expected_path);
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
                  std::to_string(weight_t{-1}), vertex_id_1, vertex_id_2));
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
  // The heuristic only affects the order in which vertices are explored, not
  // the cost reported for the resulting path: total_weight must always be
  // the true accumulated edge weight, never inflated by the heuristic value.
  ASSERT_TRUE(path_with_underestimating_heuristic.has_value());
  ASSERT_TRUE(path_with_overestimating_heuristic.has_value());

  constexpr weight_t expected_total_weight{3};
  ASSERT_EQ(path_with_underestimating_heuristic->total_weight,
            expected_total_weight);
  ASSERT_EQ(path_with_overestimating_heuristic->total_weight,
            expected_total_weight);
}

TEST(AStarDenseStorageTest, GrowsAcrossHolesAndUpdatesDiscoveredVertices) {
  graph<int, int, graph_type::DIRECTED> graph;
  std::vector<vertex_id_t> ids;
  for (int i{0}; i < 257; ++i) {
    ids.push_back(graph.add_vertex(0));
  }
  const auto start{ids[7]};
  const auto via{ids[65]};
  const auto target{ids[256]};
  for (const auto id : ids) {
    if (id != start && id != via && id != target) {
      graph.remove_vertex(id);
    }
  }
  graph.add_edge(start, target, 20);
  graph.add_edge(start, via, 2);
  graph.add_edge(via, target, 3);

  const auto heuristic{
      [target](vertex_id_t id) { return id == target ? 0 : 1; }};
  const auto path{a_star_search(graph, start, target, heuristic)};
  const graph_path<int> expected{{start, via, target}, 5};
  ASSERT_EQ(path, expected);
}

TEST(AStarDenseStorageTest, HandlesLargeAbsentIdsWithoutIndexedAllocation) {
  graph<int, int, graph_type::DIRECTED> graph;
  const auto start{graph.add_vertex(0)};
  const auto absent{std::numeric_limits<vertex_id_t>::max()};
  int heuristic_calls{0};
  const auto heuristic{[&](vertex_id_t) {
    ++heuristic_calls;
    return 0;
  }};

  EXPECT_FALSE(a_star_search(graph, absent, start, heuristic));
  EXPECT_FALSE(a_star_search(graph, start, absent, heuristic));
  const graph_path<int> trivial{{absent}, 0};
  EXPECT_EQ(a_star_search(graph, absent, absent, heuristic), trivial);
  EXPECT_EQ(heuristic_calls, 3);
}

TEST(AStarDenseStorageTest, DisconnectedTargetDoesNotAppearDiscovered) {
  graph<int, int, graph_type::UNDIRECTED> graph;
  const auto start{graph.add_vertex(0)};
  const auto target{graph.add_vertex(0)};
  vertex_id_t neighbor{};
  std::vector<vertex_id_t> removed;
  for (int i{0}; i < 63; ++i) {
    neighbor = graph.add_vertex(0);
    removed.push_back(neighbor);
  }
  removed.pop_back();
  for (const auto id : removed) {
    graph.remove_vertex(id);
  }
  graph.add_edge(start, neighbor, 0);
  graph.add_edge(neighbor, neighbor, 0);

  EXPECT_FALSE(
      a_star_search(graph, start, target, [](vertex_id_t) { return 0; }));
}

TEST(AStarDenseStorageTest, MatchesIndependentAllPairsDistances) {
  // Floyd-Warshall supplies an independent oracle. Sparse ids exercise lazy
  // growth, and zero weights and cycles exercise repeated discovery.
  constexpr std::size_t vertex_count{12};
  constexpr int infinity{100000};
  std::mt19937 generator{463};
  for (int sample{0}; sample < 24; ++sample) {
    graph<int, int, graph_type::DIRECTED> graph;
    std::vector<vertex_id_t> ids;
    std::vector<std::vector<int>> distances(
        vertex_count, std::vector<int>(vertex_count, infinity));
    for (std::size_t i{0}; i < vertex_count; ++i) {
      [[maybe_unused]] const auto gap_1{graph.add_vertex(0)};
      [[maybe_unused]] const auto gap_2{graph.add_vertex(0)};
      ids.push_back(graph.add_vertex(0));
      distances[i][i] = 0;
    }
    for (vertex_id_t id{0}; id < 3 * vertex_count; ++id) {
      if (id % 3 != 2) {
        graph.remove_vertex(id);
      }
    }
    for (std::size_t from{0}; from < vertex_count; ++from) {
      for (std::size_t to{0}; to < vertex_count; ++to) {
        if (from != to && generator() % 5 == 0) {
          const auto weight{static_cast<int>(generator() % 10)};
          graph.add_edge(ids[from], ids[to], weight);
          distances[from][to] = weight;
        }
      }
    }
    for (std::size_t via{0}; via < vertex_count; ++via) {
      for (std::size_t from{0}; from < vertex_count; ++from) {
        for (std::size_t to{0}; to < vertex_count; ++to) {
          distances[from][to] = std::min(
              distances[from][to], distances[from][via] + distances[via][to]);
        }
      }
    }
    for (std::size_t from{0}; from < vertex_count; ++from) {
      for (std::size_t to{0}; to < vertex_count; ++to) {
        SCOPED_TRACE(testing::Message() << "sample=" << sample
                                        << " from=" << from << " to=" << to);
        const auto path{a_star_search(graph, ids[from], ids[to],
                                      [](vertex_id_t) { return 0; })};
        if (distances[from][to] == infinity) {
          EXPECT_FALSE(path);
          continue;
        }
        ASSERT_TRUE(path);
        EXPECT_EQ(path->total_weight, distances[from][to]);
        EXPECT_EQ(path->vertices.front(), ids[from]);
        EXPECT_EQ(path->vertices.back(), ids[to]);
        int total{0};
        auto current{path->vertices.begin()};
        for (auto next{std::next(current)}; next != path->vertices.end();
             ++current, ++next) {
          ASSERT_TRUE(graph.has_edge(*current, *next));
          total += graph.get_edge(*current, *next);
        }
        EXPECT_EQ(total, path->total_weight);
      }
    }
  }
}

}  // namespace graaf::algorithm
