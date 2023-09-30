#include <graaflib/algorithm/strongly_connected_components/tarjan.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace graaf::algorithm {

namespace {
template <typename T>
struct TypedStronglyConnectedComponentsTest : public testing::Test {
  using graph_t = T;
};

using graph_types =
    testing::Types<directed_graph<int, int>, undirected_graph<int, int>>;

TYPED_TEST_SUITE(TypedStronglyConnectedComponentsTest, graph_types);

}  // namespace

template <typename T>
class my_weighted_edge : public weighted_edge<T> {
 public:
  explicit my_weighted_edge(T weight) : weight_{weight} {}

  [[nodiscard]] T get_weight() const noexcept override { return weight_; }

 private:
  T weight_{};
};

template <typename T>
struct TarjansStronglyConnectedComponentsTest : public testing::Test {
  using graph_t = typename T::first_type;
  using edge_t = typename T::second_type;
};

bool are_set_vectors_equal(const std::vector<std::vector<vertex_id_t>>& vec1,
                           const std::vector<std::vector<vertex_id_t>>& vec2) {
  // Make copies of the input vectors to avoid modifying the originals
  std::vector<std::vector<vertex_id_t>> sorted_vec1 = vec1;
  std::vector<std::vector<vertex_id_t>> sorted_vec2 = vec2;

  // Sort the inner vectors within each vector
  for (std::vector<vertex_id_t>& inner_vec : sorted_vec1) {
    std::sort(inner_vec.begin(), inner_vec.end());
  }
  for (std::vector<vertex_id_t>& inner_vec : sorted_vec2) {
    std::sort(inner_vec.begin(), inner_vec.end());
  }

  // Sort the outer vectors
  std::sort(sorted_vec1.begin(), sorted_vec1.end());
  std::sort(sorted_vec2.begin(), sorted_vec2.end());

  // Compare the sorted vectors for equality
  return sorted_vec1 == sorted_vec2;
}

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
              my_weighted_edge<long double>>>;

TYPED_TEST_SUITE(TarjansStronglyConnectedComponentsTest, weighted_graph_types);

TYPED_TEST(TarjansStronglyConnectedComponentsTest,
           TarjansSingleVertexGraphTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  // Vertex
  const auto vertex_id_1{graph.add_vertex(0)};

  // WHEN
  auto sccs = tarjans_strongly_connected_components(graph);

  // THEN
  std::vector<std::vector<vertex_id_t>> expected_sccs;

  std::vector<vertex_id_t> component1 = {0};
  expected_sccs.push_back(component1);

  ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TYPED_TEST(TarjansStronglyConnectedComponentsTest, TarjansTwoTrianglesTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  // Triangle 1
  const auto vertex_id_1{graph.add_vertex(0)};
  const auto vertex_id_2{graph.add_vertex(1)};
  const auto vertex_id_3{graph.add_vertex(2)};

  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_2, vertex_id_3, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_3, vertex_id_1, edge_t{static_cast<weight_t>(1)});

  // Triangle 2
  const auto vertex_id_4{graph.add_vertex(3)};
  const auto vertex_id_5{graph.add_vertex(4)};
  const auto vertex_id_6{graph.add_vertex(5)};

  graph.add_edge(vertex_id_4, vertex_id_5, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_5, vertex_id_6, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_6, vertex_id_4, edge_t{static_cast<weight_t>(1)});

  // WHEN
  auto sccs = tarjans_strongly_connected_components(graph);

  std::vector<std::vector<vertex_id_t>> expected_sccs;

  std::vector<vertex_id_t> triangle_1 = {0, 1, 2};
  std::vector<vertex_id_t> triangle_2 = {3, 4, 5};

  expected_sccs.push_back(triangle_1);
  expected_sccs.push_back(triangle_2);

  ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TYPED_TEST(TarjansStronglyConnectedComponentsTest, TarjansLinearChainTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const int num_vertices = 5;

  // Create a linear chain graph
  std::vector<vertex_id_t> vertex_ids;
  for (int i = 0; i < num_vertices; ++i) {
    vertex_ids.push_back(graph.add_vertex(i));
    if (i > 0) {
      graph.add_edge(vertex_ids[i - 1], vertex_ids[i],
                     edge_t{static_cast<weight_t>(1)});
    }
  }

  // WHEN
  auto sccs = tarjans_strongly_connected_components(graph);

  // THEN
  std::vector<std::vector<vertex_id_t>> expected_sccs;

  // Each vertex is its own SCC in a linear chain graph
  for (const auto& vertex_id : vertex_ids) {
    expected_sccs.push_back({vertex_id});
  }

  ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

// Triangle and an isolated vertex.
TYPED_TEST(TarjansStronglyConnectedComponentsTest, TarjansCycleTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(0)};
  const auto vertex_id_2{graph.add_vertex(1)};
  const auto vertex_id_3{graph.add_vertex(2)};
  const auto vertex_id_4{graph.add_vertex(3)};

  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_2, vertex_id_3, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_3, vertex_id_1, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_3, vertex_id_4, edge_t{static_cast<weight_t>(1)});

  // WHEN
  auto sccs = tarjans_strongly_connected_components(graph);

  // THEN
  std::vector<std::vector<vertex_id_t>> expected_sccs;

  std::vector<vertex_id_t> component = {0, 1, 2};
  expected_sccs.push_back(component);

  std::vector<vertex_id_t> isolated_vertex = {3};
  expected_sccs.push_back(isolated_vertex);

  ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TYPED_TEST(TarjansStronglyConnectedComponentsTest,
           TarjansDirectedAcyclicGraphTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  // Vertices
  const auto vertex_id_1{graph.add_vertex(0)};
  const auto vertex_id_2{graph.add_vertex(1)};
  const auto vertex_id_3{graph.add_vertex(2)};
  const auto vertex_id_4{graph.add_vertex(3)};

  // Edges forming a DAG
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_1, vertex_id_3, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_2, vertex_id_4, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_3, vertex_id_4, edge_t{static_cast<weight_t>(1)});

  // WHEN
  auto sccs = tarjans_strongly_connected_components(graph);

  // THEN
  // Each vertex itself is considered an SCC.
  std::vector<std::vector<vertex_id_t>> expected_sccs;

  std::vector<vertex_id_t> component1 = {0};
  expected_sccs.push_back(component1);

  std::vector<vertex_id_t> component2 = {1};
  expected_sccs.push_back(component2);

  std::vector<vertex_id_t> component3 = {2};
  expected_sccs.push_back(component3);

  std::vector<vertex_id_t> component4 = {3};
  expected_sccs.push_back(component4);

  ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TYPED_TEST(TarjansStronglyConnectedComponentsTest,
           TarjansGraphWithSelfLoopsTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  // Vertices
  const auto vertex_id_1{graph.add_vertex(0)};
  const auto vertex_id_2{graph.add_vertex(1)};
  const auto vertex_id_3{graph.add_vertex(2)};

  // Self-loop edges
  graph.add_edge(vertex_id_1, vertex_id_1, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_2, vertex_id_2, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_3, vertex_id_3, edge_t{static_cast<weight_t>(1)});

  // WHEN
  auto sccs = tarjans_strongly_connected_components(graph);

  // THEN
  std::vector<std::vector<vertex_id_t>> expected_sccs;

  std::vector<vertex_id_t> component1 = {0};
  std::vector<vertex_id_t> component2 = {1};
  std::vector<vertex_id_t> component3 = {2};

  expected_sccs.push_back(component1);
  expected_sccs.push_back(component2);
  expected_sccs.push_back(component3);

  ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

TYPED_TEST(TarjansStronglyConnectedComponentsTest, TarjansComplexGraphTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  // Vertices
  const auto vertex_id_1{graph.add_vertex(0)};
  const auto vertex_id_2{graph.add_vertex(1)};
  const auto vertex_id_3{graph.add_vertex(2)};
  const auto vertex_id_4{graph.add_vertex(3)};
  const auto vertex_id_5{graph.add_vertex(4)};
  const auto vertex_id_6{graph.add_vertex(5)};

  // Edges
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_2, vertex_id_3, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_3, vertex_id_1, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_4, vertex_id_3, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_4, vertex_id_5, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_5, vertex_id_6, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(vertex_id_6, vertex_id_4, edge_t{static_cast<weight_t>(1)});

  // WHEN
  auto sccs = tarjans_strongly_connected_components(graph);

  // THEN
  std::vector<std::vector<vertex_id_t>> expected_sccs;

  std::vector<vertex_id_t> component1 = {0, 1, 2};
  std::vector<vertex_id_t> component2 = {3, 4, 5};

  expected_sccs.push_back(component1);
  expected_sccs.push_back(component2);

  ASSERT_TRUE(are_set_vectors_equal(sccs, expected_sccs));
}

}  // namespace graaf::algorithm