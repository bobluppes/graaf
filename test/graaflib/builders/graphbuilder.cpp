#include <graaflib/graph.h>

#include <gtest/gtest.h>

namespace graaf {

TEST(GraphBuilderTest, BuildFromInitializerLists) {
  const auto test_graph{graph<int>::builder()
                            .vertices({{0, 10}, {1, 20}})
                            .edges({{0, 1}})
                            .build()};

  decltype(test_graph)::vertices_type expected_vertices{{0, 10}, {1, 20}};
  decltype(test_graph)::edges_type expected_edges{{0, 1}};

  ASSERT_EQ(test_graph.vertices(), expected_vertices);
  ASSERT_EQ(test_graph.edges(), expected_edges);
}

TEST(GraphBuilderTest, SeparateVerticesAndEdges) {
  auto builder{graph<int>::builder()};

  const auto v1{builder.add_vertex(10)};
  const auto v2{builder.add_vertex(20)};
  builder.add_edge(v1, v2);
  const auto test_graph{builder.build()};

  decltype(test_graph)::vertices_type expected_vertices{{0, 10}, {1, 20}};
  decltype(test_graph)::edges_type expected_edges{{0, 1}};

  ASSERT_EQ(test_graph.vertices(), expected_vertices);
  ASSERT_EQ(test_graph.edges(), expected_edges);
}

} // namespace graaf