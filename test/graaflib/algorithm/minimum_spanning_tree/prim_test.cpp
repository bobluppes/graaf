#include <graaflib/algorithm/minimum_spanning_tree/prim.h>
#include <gtest/gtest.h>
#include <utils/scenarios/scenarios.h>

namespace graaf::algorithm {

TEST(PrimMstTest, SingleVertex) {
  // GIVEN
  using graph_t = undirected_graph<int, int>;

  graph_t graph{};
  const auto start_vertex{graph.add_vertex(10)};

  // WHEN
  const auto mst{prim_minimum_spanning_tree(graph, start_vertex)};

  // THEN - The mst is a single node with no children
  ASSERT_TRUE(mst.has_value());

  const tree<vertex_id_t, int> expected{start_vertex};
  ASSERT_TRUE(*mst == expected);
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

  tree<vertex_id_t, int> expected{start_vertex};
  static_cast<void>(expected.root()->add_child(100, vertex_1));

  ASSERT_TRUE(*mst == expected);
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

  tree<vertex_id_t, int> expected{start_vertex};
  static_cast<void>(expected.root()->add_child(100, vertex_ids[1]));
  auto* node_2{expected.root()->add_child(200, vertex_ids[2])};
  static_cast<void>(node_2->add_child(300, vertex_ids[3]));
  static_cast<void>(node_2->add_child(400, vertex_ids[4]));

  ASSERT_TRUE(*mst == expected);
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

  tree<vertex_id_t, int> expected{start_vertex};
  auto* node_2{expected.root()->add_child(300, vertex_ids[2])};
  auto* node_0{node_2->add_child(200, vertex_ids[0])};
  static_cast<void>(node_2->add_child(400, vertex_ids[4]));
  static_cast<void>(node_0->add_child(100, vertex_ids[1]));

  ASSERT_TRUE(*mst == expected);
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

  tree<vertex_id_t, int> expected{start_vertex};
  static_cast<void>(expected.root()->add_child(100, vertex_ids[0]));
  auto* node_2{expected.root()->add_child(200, vertex_ids[2])};
  auto* node_3{node_2->add_child(400, vertex_ids[3])};
  static_cast<void>(node_3->add_child(500, vertex_ids[4]));

  ASSERT_TRUE(*mst == expected);
}

}  // namespace graaf::algorithm
