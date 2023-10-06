#include <fmt/core.h>
#include <graaflib/algorithm/clique/bron_kerbosch.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

#include <random>

namespace graaf::algorithm {
namespace {
template <typename T>
struct BronKerbosch : public testing::Test {
  using graph_t = T;
};

using graph_types = testing::Types<undirected_graph<int, int>>;
TYPED_TEST_SUITE(BronKerbosch, graph_types);

};  // namespace

void sort_vectors(std::vector<std::vector<vertex_id_t>>& vec1,
                  std::vector<std::vector<vertex_id_t>>& vec2) {
  // Sort 1D vectors
  for (std::vector<vertex_id_t>& inner_vec : vec1) {
    std::sort(inner_vec.begin(), inner_vec.end());
  }
  for (std::vector<vertex_id_t>& inner_vec : vec2) {
    std::sort(inner_vec.begin(), inner_vec.end());
  }

  // Sort 2D vectors
  std::sort(vec1.begin(), vec1.end());
  std::sort(vec2.begin(), vec2.end());
}

TYPED_TEST(BronKerbosch, ThreeCliques) {
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(1)};
  const auto vertex_2{graph.add_vertex(2)};
  const auto vertex_3{graph.add_vertex(3)};
  const auto vertex_4{graph.add_vertex(4)};
  const auto vertex_5{graph.add_vertex(5)};

  graph.add_edge(vertex_1, vertex_2, 1);
  graph.add_edge(vertex_1, vertex_3, 1);
  graph.add_edge(vertex_3, vertex_2, 1);
  graph.add_edge(vertex_3, vertex_4, 1);

  auto cliques = bron_kerbosch(graph);
  std::vector<std::vector<vertex_id_t>> expected_cliques{
      {vertex_1, vertex_2, vertex_3}, {vertex_3, vertex_4}, {vertex_5}};

  sort_vectors(cliques, expected_cliques);

  ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, OneClique) {
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(1)};
  const auto vertex_2{graph.add_vertex(2)};
  const auto vertex_3{graph.add_vertex(3)};
  const auto vertex_4{graph.add_vertex(4)};

  graph.add_edge(vertex_1, vertex_2, 1);
  graph.add_edge(vertex_1, vertex_3, 1);
  graph.add_edge(vertex_1, vertex_4, 1);
  graph.add_edge(vertex_2, vertex_4, 1);
  graph.add_edge(vertex_2, vertex_3, 1);
  graph.add_edge(vertex_3, vertex_4, 1);

  auto cliques = bron_kerbosch(graph);
  std::vector<std::vector<vertex_id_t>> expected_cliques{
      {vertex_1, vertex_2, vertex_3, vertex_4}};

  sort_vectors(cliques, expected_cliques);
  ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, FourCliques) {
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(1)};
  const auto vertex_2{graph.add_vertex(2)};
  const auto vertex_3{graph.add_vertex(3)};
  const auto vertex_4{graph.add_vertex(4)};
  const auto vertex_5{graph.add_vertex(5)};
  const auto vertex_6{graph.add_vertex(6)};
  const auto vertex_7{graph.add_vertex(7)};

  graph.add_edge(vertex_1, vertex_2, 1);
  graph.add_edge(vertex_1, vertex_3, 1);
  graph.add_edge(vertex_2, vertex_3, 1);

  graph.add_edge(vertex_4, vertex_5, 1);
  graph.add_edge(vertex_5, vertex_6, 1);
  graph.add_edge(vertex_6, vertex_7, 1);

  auto cliques = bron_kerbosch(graph);
  std::vector<std::vector<vertex_id_t>> expected_cliques{
      {vertex_1, vertex_2, vertex_3},
      {vertex_4, vertex_5},
      {vertex_6, vertex_7},
      {vertex_6, vertex_5}};

  sort_vectors(cliques, expected_cliques);
  ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, GraphPentogram) {
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(1)};
  const auto vertex_2{graph.add_vertex(2)};
  const auto vertex_3{graph.add_vertex(3)};
  const auto vertex_4{graph.add_vertex(4)};
  const auto vertex_5{graph.add_vertex(5)};
  const auto vertex_6{graph.add_vertex(6)};
  const auto vertex_7{graph.add_vertex(7)};

  graph.add_edge(vertex_1, vertex_2, 1);
  graph.add_edge(vertex_1, vertex_7, 1);
  graph.add_edge(vertex_1, vertex_4, 1);
  graph.add_edge(vertex_4, vertex_7, 1);
  graph.add_edge(vertex_2, vertex_7, 1);
  graph.add_edge(vertex_2, vertex_3, 1);
  graph.add_edge(vertex_3, vertex_7, 1);
  graph.add_edge(vertex_3, vertex_6, 1);
  graph.add_edge(vertex_6, vertex_7, 1);
  graph.add_edge(vertex_5, vertex_6, 1);
  graph.add_edge(vertex_5, vertex_7, 1);
  graph.add_edge(vertex_4, vertex_5, 1);

  auto cliques = bron_kerbosch(graph);
  std::vector<std::vector<vertex_id_t>> expected_cliques{
      {vertex_1, vertex_2, vertex_7}, {vertex_1, vertex_4, vertex_7},
      {vertex_2, vertex_3, vertex_7}, {vertex_3, vertex_6, vertex_7},
      {vertex_4, vertex_5, vertex_7}, {vertex_5, vertex_6, vertex_7}};
  sort_vectors(cliques, expected_cliques);

  ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, GraphTriangle) {
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

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

  auto cliques = bron_kerbosch(graph);
  std::vector<std::vector<vertex_id_t>> expected_cliques{
      {vertex_1, vertex_2, vertex_3, vertex_4}};
  sort_vectors(cliques, expected_cliques);

  ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, GraphCone) {
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(1)};
  const auto vertex_2{graph.add_vertex(2)};
  const auto vertex_3{graph.add_vertex(3)};
  const auto vertex_4{graph.add_vertex(4)};
  const auto vertex_5{graph.add_vertex(4)};

  // Bottom
  graph.add_edge(vertex_1, vertex_2, 1);
  graph.add_edge(vertex_1, vertex_3, 1);
  graph.add_edge(vertex_1, vertex_4, 1);
  graph.add_edge(vertex_2, vertex_3, 1);
  graph.add_edge(vertex_2, vertex_4, 1);
  graph.add_edge(vertex_3, vertex_4, 1);

  // Top
  graph.add_edge(vertex_5, vertex_1, 1);
  graph.add_edge(vertex_5, vertex_2, 1);
  graph.add_edge(vertex_5, vertex_3, 1);
  graph.add_edge(vertex_5, vertex_4, 1);

  auto cliques = bron_kerbosch(graph);
  std::vector<std::vector<vertex_id_t>> expected_cliques{
      {vertex_1, vertex_2, vertex_3, vertex_4, vertex_5}};
  sort_vectors(cliques, expected_cliques);

  ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, GraphEightSideStar) {
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_1{graph.add_vertex(1)};
  const auto vertex_2{graph.add_vertex(2)};
  const auto vertex_3{graph.add_vertex(3)};
  const auto vertex_4{graph.add_vertex(4)};
  const auto vertex_5{graph.add_vertex(5)};
  const auto vertex_6{graph.add_vertex(6)};
  const auto vertex_7{graph.add_vertex(7)};
  const auto vertex_8{graph.add_vertex(8)};
  const auto vertex_9{graph.add_vertex(9)};
  const auto vertex_10{graph.add_vertex(10)};
  const auto vertex_11{graph.add_vertex(11)};
  const auto vertex_12{graph.add_vertex(12)};
  const auto vertex_13{graph.add_vertex(13)};
  const auto vertex_14{graph.add_vertex(14)};
  const auto vertex_15{graph.add_vertex(15)};
  const auto vertex_16{graph.add_vertex(16)};

  graph.add_edge(vertex_1, vertex_2, 1);
  graph.add_edge(vertex_1, vertex_15, 1);
  graph.add_edge(vertex_2, vertex_15, 1);

  graph.add_edge(vertex_2, vertex_4, 1);
  graph.add_edge(vertex_2, vertex_3, 1);
  graph.add_edge(vertex_3, vertex_4, 1);

  graph.add_edge(vertex_4, vertex_6, 1);
  graph.add_edge(vertex_4, vertex_5, 1);
  graph.add_edge(vertex_5, vertex_6, 1);

  graph.add_edge(vertex_6, vertex_7, 1);
  graph.add_edge(vertex_6, vertex_8, 1);
  graph.add_edge(vertex_7, vertex_8, 1);

  graph.add_edge(vertex_8, vertex_9, 1);
  graph.add_edge(vertex_8, vertex_10, 1);
  graph.add_edge(vertex_9, vertex_10, 1);

  graph.add_edge(vertex_10, vertex_11, 1);
  graph.add_edge(vertex_10, vertex_12, 1);
  graph.add_edge(vertex_11, vertex_12, 1);

  graph.add_edge(vertex_12, vertex_13, 1);
  graph.add_edge(vertex_12, vertex_14, 1);
  graph.add_edge(vertex_13, vertex_14, 1);

  graph.add_edge(vertex_14, vertex_15, 1);
  graph.add_edge(vertex_14, vertex_16, 1);
  graph.add_edge(vertex_15, vertex_16, 1);

  auto cliques = bron_kerbosch(graph);
  std::vector<std::vector<vertex_id_t>> expected_cliques{
      {vertex_1, vertex_2, vertex_15},   {vertex_2, vertex_3, vertex_4},
      {vertex_5, vertex_4, vertex_6},    {vertex_7, vertex_6, vertex_8},
      {vertex_8, vertex_9, vertex_10},   {vertex_10, vertex_11, vertex_12},
      {vertex_12, vertex_13, vertex_14}, {vertex_14, vertex_15, vertex_16},
  };
  sort_vectors(cliques, expected_cliques);

  ASSERT_EQ(cliques, expected_cliques);
}

TYPED_TEST(BronKerbosch, RandomGraphCheckRunTime) {
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  std::vector<vertex_id_t> vertices;

  for (int i = 1; i <= 70; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> rand_vertex(0, 69);

  for (int i = 0; i < 1360; ++i) {
    graph.add_edge(vertices[rand_vertex(rng)], vertices[rand_vertex(rng)], 1);
  }

  auto start = std::chrono::high_resolution_clock::now();
  auto cliques = bron_kerbosch(graph);
  auto stop = std::chrono::high_resolution_clock::now();

  int expected_time = 900;

  ASSERT_TRUE(expected_time >=
              duration_cast<std::chrono::milliseconds>(stop - start).count());
}

};  // namespace graaf::algorithm