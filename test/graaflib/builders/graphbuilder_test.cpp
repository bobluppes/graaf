#include <gtest/gtest.h>

#include <graaflib/directed_graph.h>
#include <graaflib/undirected_graph.h>

namespace graaf {

TEST(GraphBuilderTest, DirectedGraphInitializerList) {
  const auto test_graph{directed_graph<int>::builder()
                            .vertices({{0, 10}, {1, 20}})
                            .edges({{0, 1}})
                            .build()};

  decltype(test_graph)::vertices_t expected_vertices{{0, 10},
                                                     {1, 20}};
  decltype(test_graph)::edges_t expected_edges{{0, 1}};

  ASSERT_EQ(test_graph.vertices(), expected_vertices);
  ASSERT_EQ(test_graph.edges(), expected_edges);
}

TEST(GraphBuilderTest, DirectedGraphSeparateVerticesAndEdges) {
  auto builder{directed_graph<int>::builder()};

  const auto v1{builder.add_vertex(10)};
  const auto v2{builder.add_vertex(20)};
  builder.add_edge(v1, v2);
  const auto test_graph{builder.build()};

  decltype(test_graph)::vertices_t expected_vertices{{0, 10}, {1, 20}};
  decltype(test_graph)::edges_t expected_edges{{0, 1}};

  ASSERT_EQ(test_graph.vertices(), expected_vertices);
  ASSERT_EQ(test_graph.edges(), expected_edges);
}

TEST(GraphBuilderTest, UndirectedGraphInitializerList) {
  const auto test_graph{undirected_graph<int>::builder()
                            .vertices({{0, 10}, {1, 20}})
                            .edges({{0, 1}})
                            .build()};

  decltype(test_graph)::vertices_t expected_vertices{{0, 10},
                                                     {1, 20}};
  decltype(test_graph)::edges_t expected_edges{{0, 1}};

  ASSERT_EQ(test_graph.vertices(), expected_vertices);
  ASSERT_EQ(test_graph.edges(), expected_edges);
}

TEST(GraphBuilderTest, UndirectedGraphSeparateVerticesAndEdges) {
  auto builder{undirected_graph<int>::builder()};

  const auto v1{builder.add_vertex(10)};
  const auto v2{builder.add_vertex(20)};
  builder.add_edge(v1, v2);
  const auto test_graph{builder.build()};

  decltype(test_graph)::vertices_t expected_vertices{{0, 10}, {1, 20}};
  decltype(test_graph)::edges_t expected_edges{{0, 1}};

  ASSERT_EQ(test_graph.vertices(), expected_vertices);
  ASSERT_EQ(test_graph.edges(), expected_edges);
}

} // namespace graaf