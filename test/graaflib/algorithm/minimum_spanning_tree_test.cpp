#include <fmt/core.h>
#include <graaflib/algorithm/minimum_spanning_tree.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>
#include <utils/scenarios/scenarios.h>

#include <type_traits>
#include <unordered_set>
#include <utility>

namespace graaf::algorithm {

namespace {

using edge_set_t = std::unordered_set<edge_id_t, edge_id_hash>;

[[nodiscard]] bool compare_mst(const std::vector<edge_id_t>& actual_mst,
                               edge_set_t expected_edges) {
  for (const auto& edge : actual_mst) {
    if (expected_edges.contains(edge)) {
      expected_edges.erase(edge);
      continue;
    } else if (const edge_id_t inverse_edge{edge.second, edge.first};
               expected_edges.contains(inverse_edge)) {
      // Since the graph is undirected, we also check the inverse of the edge
      expected_edges.erase(inverse_edge);
      continue;
    }

    // The expected edges did not contain the edge, nor the inverse edge
    return false;
  }

  return expected_edges.empty();
}

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
struct MSTTest : public testing::Test {
  using edge_t = typename T::second_type;
};

using weighted_graph_types = testing::Types<
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

TYPED_TEST_SUITE(MSTTest, weighted_graph_types);

TYPED_TEST(MSTTest, SparseGraph) {
  undirected_graph<int, int> graph{};
  const auto vertex_1 = graph.add_vertex(1);
  const auto vertex_2 = graph.add_vertex(2);
  const auto vertex_3 = graph.add_vertex(3);
  const auto vertex_4 = graph.add_vertex(4);

  graph.add_edge(vertex_3, vertex_1, 4);
  graph.add_edge(vertex_2, vertex_4, 6);
  graph.add_edge(vertex_3, vertex_4, 5);
  graph.add_edge(vertex_1, vertex_2, 15);

  auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
  std::vector<edge_id_t> expected_mst{
      {vertex_1, vertex_3}, {vertex_3, vertex_4}, {vertex_2, vertex_4}};

  ASSERT_EQ(expected_mst, mst);
}

TYPED_TEST(MSTTest, TwoComponents) {
  undirected_graph<int, float> graph{};

  const auto vertex_1 = graph.add_vertex(1);
  const auto vertex_2 = graph.add_vertex(2);
  const auto vertex_3 = graph.add_vertex(3);
  const auto vertex_4 = graph.add_vertex(4);

  const auto vertex_5 = graph.add_vertex(5);
  const auto vertex_6 = graph.add_vertex(6);
  const auto vertex_7 = graph.add_vertex(7);
  const auto vertex_8 = graph.add_vertex(8);
  const auto vertex_9 = graph.add_vertex(9);

  graph.add_edge(vertex_3, vertex_1, 0.3f);
  graph.add_edge(vertex_2, vertex_4, 0.14f);
  graph.add_edge(vertex_3, vertex_4, -5.3f);
  graph.add_edge(vertex_1, vertex_2, 223.0f);

  graph.add_edge(vertex_5, vertex_6, 2.0f);
  graph.add_edge(vertex_7, vertex_8, 4.0f);
  graph.add_edge(vertex_9, vertex_8, -23.0f);
  graph.add_edge(vertex_6, vertex_9, 3.0f);
  graph.add_edge(vertex_8, vertex_6, 0.15f);

  auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
  std::vector<edge_id_t> expected_mst{
      {vertex_8, vertex_9}, {vertex_3, vertex_4}, {vertex_2, vertex_4},
      {vertex_6, vertex_8}, {vertex_1, vertex_3}, {vertex_5, vertex_6},
      {vertex_7, vertex_8}};

  ASSERT_EQ(expected_mst, mst);
}

TYPED_TEST(MSTTest, EqualEdgeWeight) {
  undirected_graph<int, int> graph{};
  const auto vertex_1 = graph.add_vertex(1);
  const auto vertex_2 = graph.add_vertex(2);
  const auto vertex_3 = graph.add_vertex(3);
  const auto vertex_4 = graph.add_vertex(4);

  graph.add_edge(vertex_3, vertex_1, 5);
  graph.add_edge(vertex_2, vertex_4, 5);
  graph.add_edge(vertex_3, vertex_4, 5);
  graph.add_edge(vertex_1, vertex_2, 5);
  graph.add_edge(vertex_4, vertex_1, 5);

  auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
  std::vector<edge_id_t> expected_mst{
      {vertex_1, vertex_2}, {vertex_1, vertex_3}, {vertex_1, vertex_4}};

  ASSERT_EQ(expected_mst, mst);
}

TYPED_TEST(MSTTest, CompleteGraph) {
  undirected_graph<int, int> graph{};
  const auto vertex_1 = graph.add_vertex(1);
  const auto vertex_2 = graph.add_vertex(2);
  const auto vertex_3 = graph.add_vertex(3);
  const auto vertex_4 = graph.add_vertex(4);

  graph.add_edge(vertex_1, vertex_2, 35);
  graph.add_edge(vertex_1, vertex_3, 4);
  graph.add_edge(vertex_1, vertex_4, 45);
  graph.add_edge(vertex_2, vertex_4, 6);
  graph.add_edge(vertex_2, vertex_3, 55);
  graph.add_edge(vertex_3, vertex_4, 5);

  auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
  std::vector<edge_id_t> expected_mst{
      {vertex_1, vertex_3}, {vertex_3, vertex_4}, {vertex_2, vertex_4}};

  ASSERT_EQ(expected_mst, mst);
}

TYPED_TEST(MSTTest, NullGraph) {
  undirected_graph<int, float> graph{};

  const auto vertex_1 = graph.add_vertex(1);
  const auto vertex_2 = graph.add_vertex(2);
  const auto vertex_3 = graph.add_vertex(3);
  const auto vertex_4 = graph.add_vertex(4);

  auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
  std::vector<edge_id_t> example_mst{
      {vertex_3, vertex_4}, {vertex_2, vertex_4}, {vertex_1, vertex_3}};

  ASSERT_NE(example_mst, mst);
}

struct custom_vertex {
  int vertex_{};
  std::string name{};
};

struct custom_edge : public graaf::weighted_edge<int> {
 public:
  int weight_{};

  [[nodiscard]] int get_weight() const noexcept override { return weight_; }

  custom_edge(int weight) : weight_{weight} {};
  custom_edge(){};
  ~custom_edge(){};

  // Providing '<' and '!=' operators for sorting edges
  bool operator<(const custom_edge& e) const noexcept {
    return this->weight_ < e.weight_;
  }
  bool operator!=(const custom_edge& e) const noexcept {
    return this->weight_ != e.weight_;
  }
};

TYPED_TEST(MSTTest, CustomEdgeVertexOneComponentGraph) {
  undirected_graph<custom_vertex, custom_edge> graph{};

  const auto vertex_1 = graph.add_vertex(custom_vertex{1, "Custom vertex 1"});
  const auto vertex_2 = graph.add_vertex(custom_vertex{2, "Custom vertex 2"});
  const auto vertex_3 = graph.add_vertex(custom_vertex{3, "Custom vertex 3"});
  const auto vertex_4 = graph.add_vertex(custom_vertex{4, "Custom vertex 4"});

  graph.add_edge(vertex_3, vertex_1, 4);
  graph.add_edge(vertex_2, vertex_4, 6);
  graph.add_edge(vertex_3, vertex_4, 5);
  graph.add_edge(vertex_1, vertex_2, 16);

  auto mst = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
  std::vector<edge_id_t> expected_mst{
      {vertex_1, vertex_3}, {vertex_3, vertex_4}, {vertex_2, vertex_4}};

  ASSERT_EQ(expected_mst, mst);
}

TEST(PrimMstTest, SingleVertex) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;

  graph_t graph{};
  const auto start_vertex{graph.add_vertex(10)};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN - The mst is an empty edge collection
  ASSERT_TRUE(mst.has_value());
  ASSERT_TRUE(mst->empty());
}

TEST(PrimMstTest, DisconnectedGraph) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;

  graph_t graph{};
  const auto start_vertex{graph.add_vertex(10)};
  [[maybe_unused]] const auto vertex_1{graph.add_vertex(20)};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN - No MST as we cannot span the graph
  ASSERT_FALSE(mst.has_value());
}

TEST(PrimMstTest, SingleEdge) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;

  graph_t graph{};

  const auto start_vertex{graph.add_vertex(10)};
  const auto vertex_1{graph.add_vertex(20)};

  graph.add_edge(start_vertex, vertex_1, 100);

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN
  ASSERT_TRUE(mst.has_value());

  const edge_set_t expected_edges{{start_vertex, vertex_1}};
  ASSERT_TRUE(compare_mst(mst.value(), expected_edges));
}

TEST(PrimMstTest, TreeGraphStartAtRoot) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;
  const auto [graph,
              vertex_ids]{utils::scenarios::create_tree_scenario<graph_t>()};

  // We start at the root node of the tree
  const auto start_vertex{vertex_ids[0]};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN - Since the graph is a tree we expect all edges in the graph
  ASSERT_TRUE(mst.has_value());

  const edge_set_t expected_edges{{vertex_ids[0], vertex_ids[1]},
                                  {vertex_ids[0], vertex_ids[2]},
                                  {vertex_ids[2], vertex_ids[3]},
                                  {vertex_ids[2], vertex_ids[4]}};

  ASSERT_TRUE(compare_mst(mst.value(), expected_edges));
}

TEST(PrimMstTest, TreeGraphStartAtLeaf) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;
  const auto [graph,
              vertex_ids]{utils::scenarios::create_tree_scenario<graph_t>()};

  // We start at a leaf node of the tree
  const auto start_vertex{vertex_ids[3]};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN - Since the graph is a tree we expect all edges in the graph
  ASSERT_TRUE(mst.has_value());

  const edge_set_t expected_edges{{vertex_ids[0], vertex_ids[1]},
                                  {vertex_ids[0], vertex_ids[2]},
                                  {vertex_ids[2], vertex_ids[3]},
                                  {vertex_ids[2], vertex_ids[4]}};

  ASSERT_TRUE(compare_mst(mst.value(), expected_edges));
}

TEST(PrimMstTest, SimpleGraph) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;
  const auto [graph, vertex_ids]{
      utils::scenarios::create_simple_graph_scenario<graph_t>()};
  const auto start_vertex{vertex_ids[1]};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN
  ASSERT_TRUE(mst.has_value());

  const edge_set_t expected_edges{{vertex_ids[1], vertex_ids[0]},
                                  {vertex_ids[1], vertex_ids[2]},
                                  {vertex_ids[2], vertex_ids[3]},
                                  {vertex_ids[3], vertex_ids[4]}};

  ASSERT_TRUE(compare_mst(mst.value(), expected_edges));
}

}  // namespace graaf::algorithm
