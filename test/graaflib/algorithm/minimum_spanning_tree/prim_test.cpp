#include <graaflib/algorithm/minimum_spanning_tree/prim.h>
#include <gtest/gtest.h>
#include <utils/scenarios/scenarios.h>

#include <functional>
#include <unordered_set>

namespace graaf::algorithm {

namespace {

using mst_tree_t = tree<vertex_id_t, int>;

// Recursive on purpose: only used in this test file to compare the small,
// hand-built trees below, so recursion depth is bounded by construction and
// can never approach a real call-stack limit. graaf::tree deliberately does
// not expose this as operator== - a general-purpose comparison would need to
// either accept that risk for arbitrarily large trees or take on much more
// complexity to avoid it, and no production code needs tree equality today.
[[nodiscard]] bool trees_equal(const mst_tree_t::tree_node& lhs,
                               const mst_tree_t::tree_node& rhs);

// A child, keyed by the edge value towards it and its subtree. Equality
// recurses back into trees_equal, so two child_keys are equal iff their
// whole subtrees are. Hashing only needs to agree with that (equal children
// always have the same root vertex, since trees_equal checks that first),
// not capture the full subtree, so hashing just the root vertex is enough.
struct child_key {
  int edge_value;
  const mst_tree_t::tree_node* node;

  [[nodiscard]] bool operator==(const child_key& other) const {
    return edge_value == other.edge_value && trees_equal(*node, *other.node);
  }
};

struct child_key_hash {
  [[nodiscard]] std::size_t operator()(const child_key& key) const {
    return std::hash<vertex_id_t>{}(key.node->value);
  }
};

bool trees_equal(const mst_tree_t::tree_node& lhs,
                 const mst_tree_t::tree_node& rhs) {
  if (lhs.value != rhs.value) {
    return false;
  }

  const auto children_of{[](const auto& node) {
    std::unordered_set<child_key, child_key_hash> children{};
    for (const auto& link : node.children) {
      children.insert(child_key{link.value, link.child.get()});
    }
    return children;
  }};

  // unordered_set::operator== compares the two sets element for element
  // regardless of insertion order, using child_key::operator== (which
  // recurses back into trees_equal) - so the order-independent matching of
  // children is handled entirely by the standard library, not hand-rolled
  // here.
  return children_of(lhs) == children_of(rhs);
}

[[nodiscard]] bool trees_equal(const mst_tree_t& lhs, const mst_tree_t& rhs) {
  return trees_equal(*lhs.root(), *rhs.root());
}

}  // namespace

TEST(PrimMstTest, SingleVertex) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;

  graph_t graph{};
  const auto start_vertex{graph.add_vertex(10)};

  const mst_tree_t expected{start_vertex};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN - The mst is a single node with no children
  ASSERT_TRUE(mst.has_value());
  ASSERT_TRUE(trees_equal(*mst, expected));
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

  const auto expected{[&] {
    mst_tree_t res{start_vertex};
    [[maybe_unused]] auto* child_1{res.root()->add_child(100, vertex_1)};
    return res;
  }()};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN
  ASSERT_TRUE(mst.has_value());
  ASSERT_TRUE(trees_equal(*mst, expected));
}

TEST(PrimMstTest, TreeGraphStartAtRoot) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;
  const auto [graph,
              vertex_ids]{utils::scenarios::create_tree_scenario<graph_t>()};

  // We start at the root node of the tree
  const auto start_vertex{vertex_ids[0]};

  // Since the graph is a tree we expect all edges in the graph, oriented
  // away from the start vertex.
  const auto expected{[&] {
    mst_tree_t res{start_vertex};
    [[maybe_unused]] auto* child_1{res.root()->add_child(100, vertex_ids[1])};
    auto* node_2{res.root()->add_child(200, vertex_ids[2])};
    [[maybe_unused]] auto* child_3{node_2->add_child(300, vertex_ids[3])};
    [[maybe_unused]] auto* child_4{node_2->add_child(400, vertex_ids[4])};
    return res;
  }()};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN
  ASSERT_TRUE(mst.has_value());
  ASSERT_TRUE(trees_equal(*mst, expected));
}

TEST(PrimMstTest, TreeGraphStartAtLeaf) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;
  const auto [graph,
              vertex_ids]{utils::scenarios::create_tree_scenario<graph_t>()};

  // We start at a leaf node of the tree
  const auto start_vertex{vertex_ids[3]};

  // Since the graph is a tree we expect all edges in the graph, now oriented
  // outwards from the leaf we started at instead of the original root.
  const auto expected{[&] {
    mst_tree_t res{start_vertex};
    auto* node_2{res.root()->add_child(300, vertex_ids[2])};
    auto* node_0{node_2->add_child(200, vertex_ids[0])};
    [[maybe_unused]] auto* child_4{node_2->add_child(400, vertex_ids[4])};
    [[maybe_unused]] auto* child_1{node_0->add_child(100, vertex_ids[1])};
    return res;
  }()};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN
  ASSERT_TRUE(mst.has_value());
  ASSERT_TRUE(trees_equal(*mst, expected));
}

TEST(PrimMstTest, SimpleGraph) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;
  const auto [graph, vertex_ids]{
      utils::scenarios::create_simple_graph_scenario<graph_t>()};
  const auto start_vertex{vertex_ids[1]};

  const auto expected{[&] {
    mst_tree_t res{start_vertex};
    [[maybe_unused]] auto* child_0{res.root()->add_child(100, vertex_ids[0])};
    auto* node_2{res.root()->add_child(200, vertex_ids[2])};
    auto* node_3{node_2->add_child(400, vertex_ids[3])};
    [[maybe_unused]] auto* child_4{node_3->add_child(500, vertex_ids[4])};
    return res;
  }()};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN
  ASSERT_TRUE(mst.has_value());
  ASSERT_TRUE(trees_equal(*mst, expected));
}

}  // namespace graaf::algorithm
