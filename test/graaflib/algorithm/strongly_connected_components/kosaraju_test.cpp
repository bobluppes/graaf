#include <graaflib/algorithm/strongly_connected_components/kosaraju.h>
#include <gtest/gtest.h>

namespace graaf::algorithm {

TEST(KosarajuTest, EqualOutputSCCS) {
  using sccs_t = std::vector<std::vector<vertex_id_t>>;

  // GIVEN
  directed_graph<int, int> graph{};
  const auto vertex_id_1 = graph.add_vertex(1, 1);
  const auto vertex_id_2 = graph.add_vertex(2, 2);
  const auto vertex_id_3 = graph.add_vertex(3, 3);
  const auto vertex_id_4 = graph.add_vertex(4, 4);
  const auto vertex_id_5 = graph.add_vertex(5, 5);
  const auto vertex_id_6 = graph.add_vertex(6, 6);
  const auto vertex_id_7 = graph.add_vertex(7, 7);
  const auto vertex_id_8 = graph.add_vertex(8, 8);

  graph.add_edge(vertex_id_1, vertex_id_2, 1);
  graph.add_edge(vertex_id_2, vertex_id_3, 1);
  graph.add_edge(vertex_id_3, vertex_id_4, 1);
  graph.add_edge(vertex_id_3, vertex_id_1, 1);
  graph.add_edge(vertex_id_4, vertex_id_5, 1);
  graph.add_edge(vertex_id_5, vertex_id_8, 1);
  graph.add_edge(vertex_id_5, vertex_id_6, 1);
  graph.add_edge(vertex_id_6, vertex_id_7, 1);
  graph.add_edge(vertex_id_7, vertex_id_8, 1);
  graph.add_edge(vertex_id_7, vertex_id_5, 1);

  // WHEN
  sccs_t sccs = kosarajus_strongly_connected_components(graph);
  sccs_t expected_sccs = {{1, 2, 3}, {4}, {5, 6, 7}, {8}};

  // THEN
  ASSERT_EQ(sccs.size(), expected_sccs.size());

  std::sort(sccs.begin(), sccs.end());
  std::sort(expected_sccs.begin(), expected_sccs.end());

  for (int i = 0; i < sccs.size(); i++) {
    ASSERT_EQ(sccs[i].size(), expected_sccs[i].size());

    std::sort(sccs[i].begin(), sccs[i].end());
    std::sort(expected_sccs[i].begin(), expected_sccs[i].end());

    ASSERT_EQ(sccs[i], expected_sccs[i]);
  }

  ASSERT_EQ(sccs, expected_sccs);
}

}  // namespace graaf::algorithm