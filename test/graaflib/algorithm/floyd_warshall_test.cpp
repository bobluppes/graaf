#include <graaflib/algorithm/shortest_path/floyd_warshall.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

namespace graaf::algorithm {

namespace {

template <typename T>
class my_weighted_edge : public weighted_edge<T> {
 public:
  explicit my_weighted_edge(T weight) : weight_{weight} {}

  [[nodiscard]] T get_weight() const noexcept override { return weight_; }

 private:
  T weight_{};
};

template <typename T>
struct FloydWarshallTest : public testing::Test {
  using graph_t = typename T::first_type;
  using edge_t = typename T::second_type;
};
}  // namespace

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

TYPED_TEST_SUITE(FloydWarshallTest, weighted_graph_types);

TYPED_TEST(FloydWarshallTest, UndirectedGraph) {
  // GIVEN
  undirected_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 300);
  graph.add_edge(vertex_3, vertex_1, 300);

  auto shortest_paths = floyd_warshall_shortest_paths(graph);
  std::vector<std::vector<int>> expected_paths = {
      {0, 100, 300}, {100, 0, 300}, {300, 300, 0}};

  ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DirectedGraph) {
  // GIVEN
  directed_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 300);
  graph.add_edge(vertex_3, vertex_1, 300);

  auto shortest_paths = floyd_warshall_shortest_paths(graph);
  std::vector<std::vector<int>> expected_paths = {
      {0, 100, 400}, {600, 0, 300}, {300, 400, 0}};

  ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DirectedGraphNoCycleNegativeWeight) {
  directed_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};
  const auto vertex_6{graph.add_vertex(60)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 50);
  graph.add_edge(vertex_2, vertex_4, -20);
  graph.add_edge(vertex_3, vertex_6, -3);
  graph.add_edge(vertex_4, vertex_6, 100);
  graph.add_edge(vertex_5, vertex_2, -75);

  auto NO_PATH = INT_MAX;

  auto shortest_paths = floyd_warshall_shortest_paths(graph);
  std::vector<std::vector<int>> expected_paths = {
      {0, 100, 150, 80, NO_PATH, 147},
      {NO_PATH, 0, 50, -20, NO_PATH, 47},
      {NO_PATH, NO_PATH, 0, NO_PATH, NO_PATH, -3},
      {NO_PATH, NO_PATH, NO_PATH, 0, NO_PATH, 100},
      {NO_PATH, -75, -25, -95, 0, -28},
      {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 0}};

  ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DenseDirectedGraph) {
  directed_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 10);
  graph.add_edge(vertex_2, vertex_3, 50);
  graph.add_edge(vertex_2, vertex_1, 20);
  graph.add_edge(vertex_3, vertex_2, 3);
  graph.add_edge(vertex_4, vertex_1, 10);
  graph.add_edge(vertex_4, vertex_3, 75);
  graph.add_edge(vertex_4, vertex_2, 12);
  graph.add_edge(vertex_1, vertex_4, 12);

  auto shortest_paths = floyd_warshall_shortest_paths(graph);
  std::vector<std::vector<int>> expected_paths{
      {0, 10, 60, 12}, {20, 0, 50, 32}, {23, 3, 0, 35}, {10, 12, 62, 0}};

  ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DenseUndirectedGraph) {
  undirected_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 10);
  graph.add_edge(vertex_3, vertex_2, 3);
  graph.add_edge(vertex_4, vertex_1, 10);
  graph.add_edge(vertex_4, vertex_3, 75);
  graph.add_edge(vertex_4, vertex_2, 12);
  graph.add_edge(vertex_1, vertex_4, 12);

  auto shortest_paths = floyd_warshall_shortest_paths(graph);
  std::vector<std::vector<int>> expected_paths{
      {0, 10, 13, 10}, {10, 0, 3, 12}, {13, 3, 0, 15}, {10, 12, 15, 0}};

  ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, UndirectedGraphTwoComponents) {
  undirected_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(40)};
  const auto vertex_6{graph.add_vertex(40)};
  const auto vertex_7{graph.add_vertex(40)};
  const auto vertex_8{graph.add_vertex(40)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 12);
  graph.add_edge(vertex_1, vertex_3, 11);
  graph.add_edge(vertex_1, vertex_5, 6);
  graph.add_edge(vertex_2, vertex_5, 14);
  graph.add_edge(vertex_2, vertex_4, 15);
  graph.add_edge(vertex_4, vertex_5, 9);
  graph.add_edge(vertex_4, vertex_3, 7);
  graph.add_edge(vertex_5, vertex_3, 7);

  graph.add_edge(vertex_6, vertex_7, 4);
  graph.add_edge(vertex_6, vertex_8, 2);
  graph.add_edge(vertex_7, vertex_8, 3);

  auto NO_PATH = INT_MAX;

  auto shortest_paths = floyd_warshall_shortest_paths(graph);
  std::vector<std::vector<int>> expected_paths{
      {0, 12, 11, 15, 6, NO_PATH, NO_PATH, NO_PATH},
      {12, 0, 21, 15, 14, NO_PATH, NO_PATH, NO_PATH},
      {11, 21, 0, 7, 7, NO_PATH, NO_PATH, NO_PATH},
      {15, 15, 7, 0, 9, NO_PATH, NO_PATH, NO_PATH},
      {6, 14, 7, 9, 0, NO_PATH, NO_PATH, NO_PATH},
      {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 0, 4, 2},
      {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 4, 0, 3},
      {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 2, 3, 0}};

  ASSERT_EQ(shortest_paths, expected_paths);
}

TYPED_TEST(FloydWarshallTest, DirectedGraphTwoComponents) {
  undirected_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(40)};
  const auto vertex_6{graph.add_vertex(40)};
  const auto vertex_7{graph.add_vertex(40)};
  const auto vertex_8{graph.add_vertex(40)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 12);
  graph.add_edge(vertex_1, vertex_3, 11);
  graph.add_edge(vertex_5, vertex_1, 6);
  graph.add_edge(vertex_2, vertex_5, 14);
  graph.add_edge(vertex_2, vertex_4, 15);
  graph.add_edge(vertex_5, vertex_4, 9);
  graph.add_edge(vertex_4, vertex_3, 7);
  graph.add_edge(vertex_3, vertex_5, 7);

  graph.add_edge(vertex_6, vertex_7, 4);
  graph.add_edge(vertex_6, vertex_8, 2);
  graph.add_edge(vertex_8, vertex_7, 3);

  auto NO_PATH = INT_MAX;

  auto shortest_paths = floyd_warshall_shortest_paths(graph);
  std::vector<std::vector<int>> expected_paths{
      {0, 12, 11, 15, 6, NO_PATH, NO_PATH, NO_PATH},
      {12, 0, 21, 15, 14, NO_PATH, NO_PATH, NO_PATH},
      {11, 21, 0, 7, 7, NO_PATH, NO_PATH, NO_PATH},
      {15, 15, 7, 0, 9, NO_PATH, NO_PATH, NO_PATH},
      {6, 14, 7, 9, 0, NO_PATH, NO_PATH, NO_PATH},
      {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 0, 4, 2},
      {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 4, 0, 3},
      {NO_PATH, NO_PATH, NO_PATH, NO_PATH, NO_PATH, 2, 3, 0}};

  ASSERT_EQ(shortest_paths, expected_paths);
}

}  // namespace graaf::algorithm