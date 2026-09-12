#include <graaflib/algorithm/minimum_spanning_tree/prim.h>
#include <gtest/gtest.h>
#include <utils/scenarios/scenarios.h>

#include <algorithm>
#include <tuple>
#include <vector>

namespace graaf::algorithm {

namespace {

using mst_tree_t = tree<vertex_id_t, int>;

struct tree_edge {
  vertex_id_t parent;
  vertex_id_t child;
  int weight;

  [[nodiscard]] bool operator==(const tree_edge&) const = default;
};

void collect_edges(const mst_tree_t::tree_node* node,
                   std::vector<tree_edge>& out) {
  for (const auto& link : node->children) {
    out.push_back(tree_edge{node->value, link.child->value, link.value});

    // Every child must point back to the node we reached it from - this is
    // an invariant of the tree class itself, but it is exactly what an
    // algorithm producing the tree is responsible for getting right.
    EXPECT_EQ(link.child->parent, node);

    collect_edges(link.child.get(), out);
  }
}

[[nodiscard]] std::size_t count_nodes(const mst_tree_t::tree_node* node) {
  std::size_t count{1};
  for (const auto& link : node->children) {
    count += count_nodes(link.child.get());
  }
  return count;
}

[[nodiscard]] bool compare_mst(const mst_tree_t& actual,
                               vertex_id_t expected_root,
                               std::vector<tree_edge> expected_edges) {
  const auto* root{actual.root()};
  if (root == nullptr || root->value != expected_root ||
      root->parent != nullptr) {
    return false;
  }

  if (count_nodes(root) != expected_edges.size() + 1) {
    return false;
  }

  std::vector<tree_edge> actual_edges{};
  collect_edges(root, actual_edges);

  const auto sort_key{[](const tree_edge& lhs, const tree_edge& rhs) {
    return std::tie(lhs.parent, lhs.child, lhs.weight) <
           std::tie(rhs.parent, rhs.child, rhs.weight);
  }};
  std::ranges::sort(actual_edges, sort_key);
  std::ranges::sort(expected_edges, sort_key);

  return actual_edges == expected_edges;
}

}  // namespace

TEST(PrimMstTest, SingleVertex) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;

  graph_t graph{};
  const auto start_vertex{graph.add_vertex(10)};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN - The mst is a single node with no children
  ASSERT_TRUE(mst.has_value());
  ASSERT_TRUE(compare_mst(*mst, start_vertex, {}));
}

TEST(PrimMstTest, DisconnectedGraph) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;

  graph_t graph{};
  const auto start_vertex{graph.add_vertex(10)};
  [[maybe_unused]] const auto vertex_1{graph.add_vertex(20)};
  [[maybe_unused]] const auto vertex_2{graph.add_vertex(30)};

  graph.add_edge(start_vertex, vertex_1, 100);

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

  const std::vector<tree_edge> expected_edges{{start_vertex, vertex_1, 100}};
  ASSERT_TRUE(compare_mst(*mst, start_vertex, expected_edges));
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

  // THEN - Since the graph is a tree we expect all edges in the graph,
  // oriented away from the start vertex.
  ASSERT_TRUE(mst.has_value());

  const std::vector<tree_edge> expected_edges{
      {vertex_ids[0], vertex_ids[1], 100},
      {vertex_ids[0], vertex_ids[2], 200},
      {vertex_ids[2], vertex_ids[3], 300},
      {vertex_ids[2], vertex_ids[4], 400}};

  ASSERT_TRUE(compare_mst(*mst, start_vertex, expected_edges));
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

  // THEN - Since the graph is a tree we expect all edges in the graph, now
  // oriented outwards from the leaf we started at instead of the original
  // root.
  ASSERT_TRUE(mst.has_value());

  const std::vector<tree_edge> expected_edges{
      {vertex_ids[3], vertex_ids[2], 300},
      {vertex_ids[2], vertex_ids[0], 200},
      {vertex_ids[2], vertex_ids[4], 400},
      {vertex_ids[0], vertex_ids[1], 100}};

  ASSERT_TRUE(compare_mst(*mst, start_vertex, expected_edges));
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

  const std::vector<tree_edge> expected_edges{
      {vertex_ids[1], vertex_ids[0], 100},
      {vertex_ids[1], vertex_ids[2], 200},
      {vertex_ids[2], vertex_ids[3], 400},
      {vertex_ids[3], vertex_ids[4], 500}};

  ASSERT_TRUE(compare_mst(*mst, start_vertex, expected_edges));
}

}  // namespace graaf::algorithm
