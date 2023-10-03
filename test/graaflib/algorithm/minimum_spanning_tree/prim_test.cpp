#include <graaflib/algorithm/minimum_spanning_tree/prim.h>
#include <gtest/gtest.h>
#include <utils/scenarios/scenarios.h>

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
