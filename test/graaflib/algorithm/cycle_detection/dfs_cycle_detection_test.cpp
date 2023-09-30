#include <graaflib/algorithm/cycle_detection/dfs_cycle_detection.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace graaf::algorithm {

namespace {

template <typename T>
struct GraphCycleTest : public testing::Test {
  using graph_t = T;
};

using graph_types =
    testing::Types<directed_graph<int, int>, undirected_graph<int, int>>;
TYPED_TEST_SUITE(GraphCycleTest, graph_types);

}  // namespace

TYPED_TEST(GraphCycleTest, DirectedGraphWithCycle) {
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

  // checking if graph contains cycles
  bool cycle = dfs_cycle_detection(graph);
  ASSERT_TRUE(cycle);
}

TYPED_TEST(GraphCycleTest, DirectedGraphWithCycleMiddle) {
  // GIVEN
  directed_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 300);
  graph.add_edge(vertex_2, vertex_1, 300);

  // checking if graph contains cycle
  bool cycle = dfs_cycle_detection(graph);
  ASSERT_TRUE(cycle);
}

TYPED_TEST(GraphCycleTest, DirectedGraphWithoutCycle) {
  // GIVEN
  directed_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 300);

  // checking if graph contains cycle
  bool cycle = dfs_cycle_detection(graph);
  ASSERT_FALSE(cycle);
}

TYPED_TEST(GraphCycleTest, UndirectedGraphWithoutCycle) {
  // GIVEN
  undirected_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 300);

  // checking if graph contains cycle
  bool cycle = dfs_cycle_detection(graph);
  ASSERT_FALSE(cycle);
}

TYPED_TEST(GraphCycleTest, UndirectedGraphWithCycle) {
  // GIVEN
  undirected_graph<int, int> graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 300);
  graph.add_edge(vertex_3, vertex_1, 400);

  // checking if graph contains cycle
  bool cycle = dfs_cycle_detection(graph);
  ASSERT_TRUE(cycle);
}

TYPED_TEST(GraphCycleTest, EmptyGraphs) {
  // GIVEN
  directed_graph<int, int> directed_graph{};
  undirected_graph<int, int> undirected_graph{};

  // checking if graph contains cycles
  bool cycle = dfs_cycle_detection(directed_graph);
  ASSERT_FALSE(cycle);

  // checking  if graph contains cycles
  cycle = dfs_cycle_detection(undirected_graph);
  ASSERT_FALSE(cycle);
}

TYPED_TEST(GraphCycleTest, DefaultGraphWithCycle) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 300);
  graph.add_edge(vertex_3, vertex_1, 400);

  // checking  if graph contains cycle
  bool cycle = dfs_cycle_detection(graph);
  ASSERT_TRUE(cycle);
}

TYPED_TEST(GraphCycleTest, DefaultGraphWithoutCycle) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 300);

  // checking if graph contains cycle
  bool cycle = dfs_cycle_detection(graph);
  ASSERT_FALSE(cycle);
}

}  // namespace graaf::algorithm
