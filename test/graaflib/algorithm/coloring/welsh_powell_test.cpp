#include <graaflib/algorithm/coloring/welsh_powell.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

#include <unordered_map>
#include <unordered_set>

namespace graaf::algorithm {

namespace {

// A coloring is proper iff no two vertices connected by an edge share the
// same color. Note that graph::get_neighbors() returns an unordered_set, so
// the exact colors assigned to individual vertices are not guaranteed to be
// stable across STL implementations/platforms - only this invariant is.
template <typename GRAPH>
bool is_proper_coloring(const GRAPH& graph,
                        const std::unordered_map<vertex_id_t, int>& coloring) {
  for (const auto& [edge_id, edge] : graph.get_edges()) {
    const auto [u, v]{edge_id};
    if (coloring.at(u) == coloring.at(v)) {
      return false;
    }
  }
  return true;
}

}  // namespace

template <typename T>
struct WelshPowellTest : public testing::Test {
  using graph_t = T;
};

TYPED_TEST_SUITE(WelshPowellTest,
                 utils::fixtures::minimal_undirected_graph_type);

// Test case for an empty graph
TYPED_TEST(WelshPowellTest, EmptyGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // WHEN
  auto coloring = welsh_powell_coloring(graph);

  // THEN
  // Check if the obtained coloring is empty (no vertices to color)
  ASSERT_TRUE(coloring.empty());
}

TYPED_TEST(WelshPowellTest, BasicGraphColoring) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};

  // adding edges to our graph
  graph.add_edge(vertex_1, vertex_2, 1);
  graph.add_edge(vertex_2, vertex_3, 1);

  // WHEN
  auto coloring = welsh_powell_coloring(graph);

  // THEN
  ASSERT_EQ(coloring.size(), 3);
  ASSERT_TRUE(is_proper_coloring(graph, coloring));
}

TYPED_TEST(WelshPowellTest, GraphWithNoEdges) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};

  // WHEN
  auto coloring = welsh_powell_coloring(graph);

  std::unordered_map<vertex_id_t, int> expected_coloring = {
      {0, 0},  // Each vertex is assigned the same color
      {1, 0},
      {2, 0},
      {3, 0}};

  // THEN
  // Check if the obtained coloring matches the expected coloring
  ASSERT_EQ(coloring, expected_coloring);
}

// Test with a complete graph
TYPED_TEST(WelshPowellTest, CompleteGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(1)};
  const auto vertex_2{graph.add_vertex(2)};
  const auto vertex_3{graph.add_vertex(3)};
  const auto vertex_4{graph.add_vertex(4)};

  graph.add_edge(vertex_1, vertex_2, 1);
  graph.add_edge(vertex_1, vertex_3, 1);
  graph.add_edge(vertex_1, vertex_4, 1);
  graph.add_edge(vertex_2, vertex_3, 1);
  graph.add_edge(vertex_2, vertex_4, 1);
  graph.add_edge(vertex_3, vertex_4, 1);

  // WHEN
  auto coloring = welsh_powell_coloring(graph);

  // THEN
  ASSERT_TRUE(is_proper_coloring(graph, coloring));

  // A complete graph on 4 vertices requires exactly 4 distinct colors, since
  // every vertex is adjacent to every other vertex.
  std::unordered_set<int> distinct_colors;
  for (const auto& [vertex_id, color] : coloring) {
    distinct_colors.insert(color);
  }
  ASSERT_EQ(distinct_colors.size(), 4);
}

TYPED_TEST(WelshPowellTest, DisconnectedComponents) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  // graph vertices
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  // Create disconnected components
  graph.add_edge(vertex_1, vertex_2,
                 1);  // Component 1: Vertex 1 and 2 are connected
  graph.add_edge(vertex_3, vertex_4,
                 1);  // Component 2: Vertex 3 and 4 are
                      // Component 3: connected Vertex 5 is disconnected
  // WHEN
  auto coloring = welsh_powell_coloring(graph);

  // THEN
  ASSERT_TRUE(is_proper_coloring(graph, coloring));
}

}  // namespace graaf::algorithm