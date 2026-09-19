#include <graaflib/algorithm/ranking/pagerank.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

#include <limits>
#include <numeric>
#include <stdexcept>
#include <unordered_map>

namespace graaf::algorithm {
namespace {
template <typename T>
struct TypedPageRank : public testing::Test {
  using graph_t = T;
};

TYPED_TEST_SUITE(TypedPageRank, utils::fixtures::minimal_directed_graph_type);

// Ranks are compared against exact values, so the tests request a much
// tighter tolerance than the default to keep the iterative error well below
// the comparison threshold.
constexpr double tight_tolerance{1.0e-12};
constexpr std::size_t generous_iterations{1000};
constexpr double comparison_threshold{1.0e-9};

[[nodiscard]] double total_rank(
    const std::unordered_map<vertex_id_t, double>& ranks) {
  return std::accumulate(
      ranks.begin(), ranks.end(), 0.0,
      [](double sum, const auto& entry) { return sum + entry.second; });
}

};  // namespace

TYPED_TEST(TypedPageRank, EmptyGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // WHEN
  const auto ranks{pagerank(graph)};

  // THEN
  ASSERT_TRUE(ranks.has_value());
  EXPECT_TRUE(ranks->empty());
}

TYPED_TEST(TypedPageRank, SingleVertex) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id{graph.add_vertex(10)};

  // WHEN
  const auto ranks{pagerank(graph)};

  // THEN
  ASSERT_TRUE(ranks.has_value());
  ASSERT_EQ(ranks->size(), 1);
  EXPECT_DOUBLE_EQ(ranks->at(vertex_id), 1.0);
}

TYPED_TEST(TypedPageRank, CycleHasUniformRanks) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_3, 200);
  graph.add_edge(vertex_id_3, vertex_id_1, 300);

  // WHEN
  const auto ranks{pagerank(graph)};

  // THEN
  ASSERT_TRUE(ranks.has_value());
  for (const auto vertex_id : {vertex_id_1, vertex_id_2, vertex_id_3}) {
    EXPECT_NEAR(ranks->at(vertex_id), 1.0 / 3.0, comparison_threshold);
  }
}

TYPED_TEST(TypedPageRank, SmallGraphMatchesHandComputedRanks) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_1, vertex_id_3, 200);
  graph.add_edge(vertex_id_2, vertex_id_3, 300);
  graph.add_edge(vertex_id_3, vertex_id_1, 400);

  // WHEN
  const auto ranks{pagerank(graph, 0.85, tight_tolerance, generous_iterations)};

  // THEN - exact solution of the PageRank equations with d = 0.85
  ASSERT_TRUE(ranks.has_value());
  EXPECT_NEAR(ranks->at(vertex_id_1), 686.0 / 1769.0, comparison_threshold);
  EXPECT_NEAR(ranks->at(vertex_id_2), 380.0 / 1769.0, comparison_threshold);
  EXPECT_NEAR(ranks->at(vertex_id_3), 703.0 / 1769.0, comparison_threshold);
}

TYPED_TEST(TypedPageRank, DanglingVertexRedistributesItsRank) {
  // GIVEN - a star whose leaves all point to a center without outgoing edges
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto center{graph.add_vertex(10)};
  const auto leaf_1{graph.add_vertex(20)};
  const auto leaf_2{graph.add_vertex(30)};
  const auto leaf_3{graph.add_vertex(40)};
  graph.add_edge(leaf_1, center, 100);
  graph.add_edge(leaf_2, center, 200);
  graph.add_edge(leaf_3, center, 300);

  // WHEN
  const auto ranks{pagerank(graph, 0.85, tight_tolerance, generous_iterations)};

  // THEN - exact solution of the PageRank equations with d = 0.85
  ASSERT_TRUE(ranks.has_value());
  EXPECT_NEAR(ranks->at(center), 71.0 / 131.0, comparison_threshold);
  for (const auto leaf : {leaf_1, leaf_2, leaf_3}) {
    EXPECT_NEAR(ranks->at(leaf), 20.0 / 131.0, comparison_threshold);
  }
  EXPECT_NEAR(total_rank(*ranks), 1.0, comparison_threshold);
}

TYPED_TEST(TypedPageRank, GraphWithoutEdgesHasUniformRanks) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};

  // WHEN
  const auto ranks{pagerank(graph)};

  // THEN
  ASSERT_TRUE(ranks.has_value());
  for (const auto vertex_id :
       {vertex_id_1, vertex_id_2, vertex_id_3, vertex_id_4}) {
    EXPECT_DOUBLE_EQ(ranks->at(vertex_id), 0.25);
  }
}

TYPED_TEST(TypedPageRank, SymmetricDisconnectedComponents) {
  // GIVEN - two identical two-cycles
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_1, 200);
  graph.add_edge(vertex_id_3, vertex_id_4, 300);
  graph.add_edge(vertex_id_4, vertex_id_3, 400);

  // WHEN
  const auto ranks{pagerank(graph)};

  // THEN
  ASSERT_TRUE(ranks.has_value());
  for (const auto vertex_id :
       {vertex_id_1, vertex_id_2, vertex_id_3, vertex_id_4}) {
    EXPECT_NEAR(ranks->at(vertex_id), 0.25, comparison_threshold);
  }
}

TYPED_TEST(TypedPageRank, AsymmetricDisconnectedComponents) {
  // GIVEN - a two-cycle next to a single edge ending in a dangling vertex
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto source{graph.add_vertex(30)};
  const auto sink{graph.add_vertex(40)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_1, 200);
  graph.add_edge(source, sink, 300);

  // WHEN
  const auto ranks{pagerank(graph, 0.85, tight_tolerance, generous_iterations)};

  // THEN
  ASSERT_TRUE(ranks.has_value());
  EXPECT_NEAR(total_rank(*ranks), 1.0, comparison_threshold);
  EXPECT_NEAR(ranks->at(vertex_id_1), ranks->at(vertex_id_2),
              comparison_threshold);
  EXPECT_GT(ranks->at(sink), ranks->at(source));
  EXPECT_GT(ranks->at(vertex_id_1), ranks->at(source));
}

TYPED_TEST(TypedPageRank, SelfLoop) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  graph.add_edge(vertex_id_1, vertex_id_1, 100);
  graph.add_edge(vertex_id_2, vertex_id_1, 200);

  // WHEN
  const auto ranks{pagerank(graph)};

  // THEN
  ASSERT_TRUE(ranks.has_value());
  EXPECT_NEAR(total_rank(*ranks), 1.0, comparison_threshold);
  EXPECT_GT(ranks->at(vertex_id_1), ranks->at(vertex_id_2));
}

TYPED_TEST(TypedPageRank, NonContiguousVertexIds) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto removed_vertex_id{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  graph.add_edge(vertex_id_1, vertex_id_3, 100);
  graph.add_edge(vertex_id_3, vertex_id_1, 200);
  graph.remove_vertex(removed_vertex_id);

  // WHEN
  const auto ranks{pagerank(graph)};

  // THEN
  ASSERT_TRUE(ranks.has_value());
  ASSERT_EQ(ranks->size(), 2);
  EXPECT_FALSE(ranks->contains(removed_vertex_id));
  EXPECT_NEAR(ranks->at(vertex_id_1), 0.5, comparison_threshold);
  EXPECT_NEAR(ranks->at(vertex_id_3), 0.5, comparison_threshold);
}

TYPED_TEST(TypedPageRank, ZeroDampingFactorGivesUniformRanks) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);

  // WHEN
  const auto ranks{pagerank(graph, 0.0)};

  // THEN
  ASSERT_TRUE(ranks.has_value());
  EXPECT_DOUBLE_EQ(ranks->at(vertex_id_1), 0.5);
  EXPECT_DOUBLE_EQ(ranks->at(vertex_id_2), 0.5);
}

TYPED_TEST(TypedPageRank, OscillatingRanksDoNotConverge) {
  // GIVEN - without teleportation, rank bounces between the two cycle
  // vertices forever
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_2, vertex_id_1, 200);
  graph.add_edge(vertex_id_3, vertex_id_1, 300);

  // WHEN
  const auto ranks{pagerank(graph, 1.0)};

  // THEN
  EXPECT_FALSE(ranks.has_value());
}

TYPED_TEST(TypedPageRank, IterationLimitReached) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_1, vertex_id_3, 200);
  graph.add_edge(vertex_id_2, vertex_id_3, 300);
  graph.add_edge(vertex_id_3, vertex_id_1, 400);

  // WHEN
  const auto ranks{pagerank(graph, 0.85, 1.0e-6, 1)};

  // THEN
  EXPECT_FALSE(ranks.has_value());
}

TYPED_TEST(TypedPageRank, InvalidParametersThrow) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  [[maybe_unused]] const auto vertex_id{graph.add_vertex(10)};
  constexpr auto nan{std::numeric_limits<double>::quiet_NaN()};

  // WHEN - THEN
  EXPECT_THROW((void)pagerank(graph, -0.1), std::invalid_argument);
  EXPECT_THROW((void)pagerank(graph, 1.1), std::invalid_argument);
  EXPECT_THROW((void)pagerank(graph, nan), std::invalid_argument);
  EXPECT_THROW((void)pagerank(graph, 0.85, 0.0), std::invalid_argument);
  EXPECT_THROW((void)pagerank(graph, 0.85, -1.0e-6), std::invalid_argument);
  EXPECT_THROW((void)pagerank(graph, 0.85, nan), std::invalid_argument);
  EXPECT_THROW((void)pagerank(graph, 0.85, 1.0e-6, 0), std::invalid_argument);
}

}  // namespace graaf::algorithm
