#include <graaflib/algorithm/shortest_path.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

namespace graaf::algorithm {

namespace {
template <typename T>
struct TypedShortestPathTest : public testing::Test {
  using graph_t = T;
};

using graph_types =
    testing::Types<directed_graph<int, int>, undirected_graph<int, int>>;
TYPED_TEST_SUITE(TypedShortestPathTest, graph_types);
}  // namespace

TYPED_TEST(TypedShortestPathTest, UnweightedMinimalShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};

  // WHEN
  const auto path =
      get_shortest_path<edge_strategy::UNWEIGHTED>(graph, vertex_1, vertex_1);

  // THEN
  const GraphPath<int> expected_path{{vertex_1}, 1};
  ASSERT_EQ(path, expected_path);
}

TYPED_TEST(TypedShortestPathTest, UnweightedNoAvailablePath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // WHEN
  const auto path =
      get_shortest_path<edge_strategy::UNWEIGHTED>(graph, vertex_1, vertex_2);

  // THEN
  ASSERT_FALSE(path.has_value());
}

TYPED_TEST(TypedShortestPathTest, UnweightedSimpleShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};

  // We add an edge from the vertex where we start the traversal
  // so it does not matter whether this is a directed or undirected graph
  graph.add_edge(vertex_1, vertex_2, 100);

  // WHEN
  const auto path =
      get_shortest_path<edge_strategy::UNWEIGHTED>(graph, vertex_1, vertex_2);

  // THEN
  const GraphPath<int> expected_path{{vertex_1, vertex_2}, 2};
  ASSERT_EQ(path, expected_path);
}

TYPED_TEST(TypedShortestPathTest, UnweightedMoreComplexShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  // All edges are in the search direction, so the graph specialization does not
  // matter
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 200);
  graph.add_edge(vertex_1, vertex_3, 300);
  graph.add_edge(vertex_3, vertex_4, 400);
  graph.add_edge(vertex_4, vertex_5, 500);
  graph.add_edge(vertex_3, vertex_5, 600);

  // WHEN
  const auto path =
      get_shortest_path<edge_strategy::UNWEIGHTED>(graph, vertex_1, vertex_5);

  // THEN
  const GraphPath<int> expected_path{{vertex_1, vertex_3, vertex_5}, 3};
  ASSERT_EQ(path, expected_path);
}

TYPED_TEST(TypedShortestPathTest, UnweightedCyclicShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  // All edges are in the search direction, so the graph specialization does not
  // matter
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 200);
  graph.add_edge(vertex_3, vertex_4, 300);
  graph.add_edge(vertex_4, vertex_2, 300);
  graph.add_edge(vertex_3, vertex_5, 400);

  // WHEN
  const auto path =
      get_shortest_path<edge_strategy::UNWEIGHTED>(graph, vertex_1, vertex_5);

  // THEN
  const GraphPath<int> expected_path{{vertex_1, vertex_2, vertex_3, vertex_5},
                                     4};
  ASSERT_EQ(path, expected_path);
}

TEST(ShortestPathTest, UnweightedDirectedrWrongDirectionShortestPath) {
  // GIVEN
  directed_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  // Edge between 2 and 3 is inverted, so path needs to take detour via 4
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_3, vertex_2, 200);
  graph.add_edge(vertex_3, vertex_5, 300);
  graph.add_edge(vertex_2, vertex_4, 400);
  graph.add_edge(vertex_4, vertex_3, 500);

  // WHEN
  const auto path =
      get_shortest_path<edge_strategy::UNWEIGHTED>(graph, vertex_1, vertex_5);

  // THEN
  const GraphPath<int> expected_path{
      {vertex_1, vertex_2, vertex_4, vertex_3, vertex_5}, 5};
  ASSERT_EQ(path, expected_path);
}

template <typename T>
class my_weighted_edge : public weighted_edge<T> {
 public:
  explicit my_weighted_edge(T weight) : weight_{weight} {}

  [[nodiscard]] T get_weight() const noexcept override { return weight_; }

 private:
  T weight_{};
};

template <typename T>
struct WeightedShortestPathTest : public testing::Test {
  using graph_t = typename T::first_type;
  using edge_t = typename T::second_type;
};

using weighted_graph_types = testing::Types<

    /**
     * Primitive edge type directed graph
     */
    std::pair<directed_graph<int, int>, int>,
    std::pair<directed_graph<int, unsigned long>, unsigned long>,
    std::pair<directed_graph<int, float>, float>,
    std::pair<directed_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type directed graph
     */

    std::pair<directed_graph<int, my_weighted_edge<int>>,
              my_weighted_edge<int>>,
    std::pair<directed_graph<int, my_weighted_edge<unsigned long>>,
              my_weighted_edge<unsigned long>>,
    std::pair<directed_graph<int, my_weighted_edge<float>>,
              my_weighted_edge<float>>,
    std::pair<directed_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>,

    /**
     * Primitive edge type undirected graph
     */
    std::pair<undirected_graph<int, int>, int>,
    std::pair<undirected_graph<int, unsigned long>, unsigned long>,
    std::pair<undirected_graph<int, float>, float>,
    std::pair<undirected_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type undirected graph
     */
    std::pair<undirected_graph<int, my_weighted_edge<int>>,
              my_weighted_edge<int>>,
    std::pair<undirected_graph<int, my_weighted_edge<unsigned long>>,
              my_weighted_edge<unsigned long>>,
    std::pair<undirected_graph<int, my_weighted_edge<float>>,
              my_weighted_edge<float>>,
    std::pair<undirected_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>>;

TYPED_TEST_SUITE(WeightedShortestPathTest, weighted_graph_types);

// Type traits to extract the weight type from both classes and primitives
template <typename T>
struct extract_weight {
  using type = T;
};

template <typename T>
  requires requires { typename T::weight_t; }
struct extract_weight<T> {
  using type = typename T::weight_t;
};

TYPED_TEST(WeightedShortestPathTest, WeightedMinimalShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = typename extract_weight<edge_t>::type;

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};

  // WHEN;
  const auto path = get_shortest_path<edge_strategy::WEIGHTED>(
      graph, vertex_id_1, vertex_id_1);

  // THEN
  const GraphPath<weight_t> expected_path{{vertex_id_1}, 0};
  ASSERT_EQ(path, expected_path);
}

TYPED_TEST(WeightedShortestPathTest, WeightedNoAvailablePath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = typename extract_weight<edge_t>::type;

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // WHEN;
  const auto path = get_shortest_path<edge_strategy::WEIGHTED>(
      graph, vertex_id_1, vertex_id_2);

  // THEN
  ASSERT_FALSE(path.has_value());
}

TYPED_TEST(WeightedShortestPathTest, WeightedSimpleShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = typename extract_weight<edge_t>::type;

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(3)});

  // WHEN
  const auto path = get_shortest_path<edge_strategy::WEIGHTED>(
      graph, vertex_id_1, vertex_id_2);

  // THEN
  const GraphPath<weight_t> expected_path{{vertex_id_1, vertex_id_2}, 3};
  ASSERT_EQ(path, expected_path);
}

TYPED_TEST(WeightedShortestPathTest, WeightedMoreComplexShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = typename extract_weight<edge_t>::type;

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};
  const auto vertex_id_5{graph.add_vertex(50)};

  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_2, vertex_id_3, edge_t{static_cast<weight_t>(2)});
  graph.add_edge(vertex_id_1, vertex_id_3, edge_t{static_cast<weight_t>(3)});
  graph.add_edge(vertex_id_3, vertex_id_4, edge_t{static_cast<weight_t>(4)});
  graph.add_edge(vertex_id_4, vertex_id_5, edge_t{static_cast<weight_t>(5)});
  graph.add_edge(vertex_id_3, vertex_id_5, edge_t{static_cast<weight_t>(6)});

  // WHEN
  const auto path = get_shortest_path<edge_strategy::WEIGHTED>(
      graph, vertex_id_1, vertex_id_5);

  // THEN
  const GraphPath<weight_t> expected_path{
      {vertex_id_1, vertex_id_3, vertex_id_5}, 9};
  ASSERT_EQ(path, expected_path);
}

TYPED_TEST(WeightedShortestPathTest, WeightedCyclicShortestPath) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = typename extract_weight<edge_t>::type;

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};
  const auto vertex_id_4{graph.add_vertex(40)};
  const auto vertex_id_5{graph.add_vertex(50)};

  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_2, vertex_id_3, edge_t{static_cast<weight_t>(2)});
  graph.add_edge(vertex_id_3, vertex_id_4, edge_t{static_cast<weight_t>(3)});
  graph.add_edge(vertex_id_4, vertex_id_2, edge_t{static_cast<weight_t>(4)});
  graph.add_edge(vertex_id_3, vertex_id_5, edge_t{static_cast<weight_t>(5)});

  // WHEN
  const auto path = get_shortest_path<edge_strategy::WEIGHTED>(
      graph, vertex_id_1, vertex_id_5);

  // THEN
  const GraphPath<weight_t> expected_path{
      {vertex_id_1, vertex_id_2, vertex_id_3, vertex_id_5}, 8};
  ASSERT_EQ(path, expected_path);
}

}  // namespace graaf::algorithm