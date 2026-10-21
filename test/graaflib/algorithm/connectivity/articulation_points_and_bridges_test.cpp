#include <graaflib/algorithm/connectivity/articulation_points.h>
#include <graaflib/algorithm/connectivity/bridges.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

#include <algorithm>
#include <cstddef>
#include <random>
#include <tuple>
#include <unordered_set>
#include <vector>

namespace graaf::algorithm {
namespace {
template <typename T>
struct TypedCutStructureTest : public testing::Test {
  using graph_t = T;
};

TYPED_TEST_SUITE(TypedCutStructureTest,
                 utils::fixtures::minimal_undirected_graph_type);

template <typename GRAPH_T>
[[nodiscard]] std::size_t count_components(const GRAPH_T& graph) {
  std::unordered_set<vertex_id_t> seen{};
  std::size_t components{0};
  for (const auto& [start, _] : graph.get_vertices()) {
    if (seen.contains(start)) {
      continue;
    }
    ++components;
    std::vector<vertex_id_t> to_visit{start};
    seen.insert(start);
    while (!to_visit.empty()) {
      const auto vertex{to_visit.back()};
      to_visit.pop_back();
      for (const auto neighbor : graph.get_neighbors(vertex)) {
        if (seen.insert(neighbor).second) {
          to_visit.push_back(neighbor);
        }
      }
    }
  }
  return components;
}

template <typename GRAPH_T>
[[nodiscard]] std::vector<vertex_id_t> brute_force_articulation_points(
    const GRAPH_T& graph) {
  const auto components{count_components(graph)};
  std::vector<vertex_id_t> result{};
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    auto without_vertex{graph};
    without_vertex.remove_vertex(vertex_id);
    if (count_components(without_vertex) > components) {
      result.push_back(vertex_id);
    }
  }
  std::sort(result.begin(), result.end());
  return result;
}

template <typename GRAPH_T>
[[nodiscard]] std::vector<edge_id_t> brute_force_bridges(const GRAPH_T& graph) {
  const auto components{count_components(graph)};
  std::vector<edge_id_t> result{};
  for (const auto& [edge_id, _] : graph.get_edges()) {
    if (edge_id.first == edge_id.second) {
      continue;
    }
    auto without_edge{graph};
    without_edge.remove_edge(edge_id.first, edge_id.second);
    if (count_components(without_edge) > components) {
      result.push_back(edge_id);
    }
  }
  std::sort(result.begin(), result.end());
  return result;
}

}  // namespace

TYPED_TEST(TypedCutStructureTest, EmptyGraph) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  const graph_t graph{};

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_TRUE(cut_vertices.empty());
  EXPECT_TRUE(cut_edges.empty());
}

TYPED_TEST(TypedCutStructureTest, SingleVertex) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  std::ignore = graph.add_vertex(10);

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_TRUE(cut_vertices.empty());
  EXPECT_TRUE(cut_edges.empty());
}

TYPED_TEST(TypedCutStructureTest, SingleEdge) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  graph.add_edge(vertex_1, vertex_2, 100);

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_TRUE(cut_vertices.empty());
  EXPECT_EQ(cut_edges, (std::vector<edge_id_t>{{vertex_1, vertex_2}}));
}

TYPED_TEST(TypedCutStructureTest, CycleHasNoCutStructure) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  std::vector<vertex_id_t> vertices{};
  for (int i{0}; i < 5; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }
  for (std::size_t i{0}; i < vertices.size(); ++i) {
    graph.add_edge(vertices[i], vertices[(i + 1) % vertices.size()], 100);
  }

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_TRUE(cut_vertices.empty());
  EXPECT_TRUE(cut_edges.empty());
}

TYPED_TEST(TypedCutStructureTest, EveryEdgeOfATreeIsABridge) {
  // GIVEN
  //      0
  //     / \
  //    1   2
  //   / \   \
  //  3   4   5
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  std::vector<vertex_id_t> vertices{};
  for (int i{0}; i < 6; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }
  graph.add_edge(vertices[0], vertices[1], 100);
  graph.add_edge(vertices[0], vertices[2], 100);
  graph.add_edge(vertices[1], vertices[3], 100);
  graph.add_edge(vertices[1], vertices[4], 100);
  graph.add_edge(vertices[2], vertices[5], 100);

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_EQ(cut_vertices,
            (std::vector<vertex_id_t>{vertices[0], vertices[1], vertices[2]}));
  EXPECT_EQ(cut_edges, (std::vector<edge_id_t>{{vertices[0], vertices[1]},
                                               {vertices[0], vertices[2]},
                                               {vertices[1], vertices[3]},
                                               {vertices[1], vertices[4]},
                                               {vertices[2], vertices[5]}}));
}

TYPED_TEST(TypedCutStructureTest,
           RootWithASingleChildIsNotAnArticulationPoint) {
  // GIVEN
  // A path, so the vertex the search starts from has exactly one child
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_3, 100);

  // WHEN
  const auto cut_vertices{articulation_points(graph)};

  // THEN
  EXPECT_EQ(cut_vertices, (std::vector<vertex_id_t>{vertex_2}));
}

TYPED_TEST(TypedCutStructureTest, TwoCyclesSharingAVertex) {
  // GIVEN
  //  0 --- 1       3 --- 4
  //   \   /         \   /
  //     2 ----------- 2
  // i.e. the triangles {0, 1, 2} and {2, 3, 4} only share vertex 2
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  std::vector<vertex_id_t> vertices{};
  for (int i{0}; i < 5; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }
  graph.add_edge(vertices[0], vertices[1], 100);
  graph.add_edge(vertices[1], vertices[2], 100);
  graph.add_edge(vertices[2], vertices[0], 100);
  graph.add_edge(vertices[2], vertices[3], 100);
  graph.add_edge(vertices[3], vertices[4], 100);
  graph.add_edge(vertices[4], vertices[2], 100);

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_EQ(cut_vertices, (std::vector<vertex_id_t>{vertices[2]}));
  EXPECT_TRUE(cut_edges.empty());
}

TYPED_TEST(TypedCutStructureTest, TwoCyclesJoinedByABridge) {
  // GIVEN
  // The triangles {0, 1, 2} and {3, 4, 5}, joined by the edge 2 - 3
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  std::vector<vertex_id_t> vertices{};
  for (int i{0}; i < 6; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }
  graph.add_edge(vertices[0], vertices[1], 100);
  graph.add_edge(vertices[1], vertices[2], 100);
  graph.add_edge(vertices[2], vertices[0], 100);
  graph.add_edge(vertices[3], vertices[4], 100);
  graph.add_edge(vertices[4], vertices[5], 100);
  graph.add_edge(vertices[5], vertices[3], 100);
  graph.add_edge(vertices[2], vertices[3], 100);

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_EQ(cut_vertices, (std::vector<vertex_id_t>{vertices[2], vertices[3]}));
  EXPECT_EQ(cut_edges, (std::vector<edge_id_t>{{vertices[2], vertices[3]}}));
}

TYPED_TEST(TypedCutStructureTest, DisconnectedGraph) {
  // GIVEN
  // A path 0 - 1 - 2, a triangle {3, 4, 5} and an isolated vertex 6
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  std::vector<vertex_id_t> vertices{};
  for (int i{0}; i < 7; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }
  graph.add_edge(vertices[0], vertices[1], 100);
  graph.add_edge(vertices[1], vertices[2], 100);
  graph.add_edge(vertices[3], vertices[4], 100);
  graph.add_edge(vertices[4], vertices[5], 100);
  graph.add_edge(vertices[5], vertices[3], 100);

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_EQ(cut_vertices, (std::vector<vertex_id_t>{vertices[1]}));
  EXPECT_EQ(cut_edges, (std::vector<edge_id_t>{{vertices[0], vertices[1]},
                                               {vertices[1], vertices[2]}}));
}

TYPED_TEST(TypedCutStructureTest, SelfLoopIsIgnored) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_2, vertex_2, 100);

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_TRUE(cut_vertices.empty());
  EXPECT_EQ(cut_edges, (std::vector<edge_id_t>{{vertex_1, vertex_2}}));
}

TYPED_TEST(TypedCutStructureTest, RemovedVertexLeavesAGapInTheIds) {
  // GIVEN
  // A path 0 - 1 - 2 - 3 with vertex 0 removed afterwards
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  std::vector<vertex_id_t> vertices{};
  for (int i{0}; i < 4; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }
  graph.add_edge(vertices[0], vertices[1], 100);
  graph.add_edge(vertices[1], vertices[2], 100);
  graph.add_edge(vertices[2], vertices[3], 100);
  graph.remove_vertex(vertices[0]);

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_EQ(cut_vertices, (std::vector<vertex_id_t>{vertices[2]}));
  EXPECT_EQ(cut_edges, (std::vector<edge_id_t>{{vertices[1], vertices[2]},
                                               {vertices[2], vertices[3]}}));
}

TYPED_TEST(TypedCutStructureTest, LongPathDoesNotOverflowTheStack) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  constexpr std::size_t path_length{200'000};
  std::vector<vertex_id_t> vertices{};
  vertices.reserve(path_length);
  for (std::size_t i{0}; i < path_length; ++i) {
    vertices.push_back(graph.add_vertex(static_cast<int>(i)));
  }
  for (std::size_t i{0}; i + 1 < path_length; ++i) {
    graph.add_edge(vertices[i], vertices[i + 1], 100);
  }

  // WHEN
  const auto cut_vertices{articulation_points(graph)};
  const auto cut_edges{bridges(graph)};

  // THEN
  EXPECT_EQ(cut_vertices.size(), path_length - 2);
  EXPECT_EQ(cut_edges.size(), path_length - 1);
}

TYPED_TEST(TypedCutStructureTest, MatchesBruteForceOnRandomGraphs) {
  using graph_t = typename TestFixture::graph_t;
  std::mt19937 rng{42};
  constexpr int graph_count{200};

  for (int graph_index{0}; graph_index < graph_count; ++graph_index) {
    // GIVEN
    std::uniform_int_distribution<int> vertex_count_dist{1, 12};
    std::uniform_real_distribution<double> edge_probability_dist{0.05, 0.5};
    const auto vertex_count{vertex_count_dist(rng)};
    const auto edge_probability{edge_probability_dist(rng)};
    std::bernoulli_distribution has_edge{edge_probability};

    graph_t graph{};
    for (int i{0}; i < vertex_count; ++i) {
      std::ignore = graph.add_vertex(i);
    }
    for (vertex_id_t lhs{0}; lhs < static_cast<vertex_id_t>(vertex_count);
         ++lhs) {
      for (vertex_id_t rhs{lhs + 1};
           rhs < static_cast<vertex_id_t>(vertex_count); ++rhs) {
        if (has_edge(rng)) {
          graph.add_edge(lhs, rhs, 100);
        }
      }
    }

    // WHEN
    const auto cut_vertices{articulation_points(graph)};
    const auto cut_edges{bridges(graph)};

    // THEN
    EXPECT_EQ(cut_vertices, brute_force_articulation_points(graph))
        << "graph " << graph_index;
    EXPECT_EQ(cut_edges, brute_force_bridges(graph)) << "graph " << graph_index;
  }
}

}  // namespace graaf::algorithm
