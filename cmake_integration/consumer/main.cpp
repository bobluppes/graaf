#include <graaflib/graph.h>

int main() {
  graaf::undirected_graph<int, float> graph{};
  const auto vertex_1{graph.add_vertex(1)};
  const auto vertex_2{graph.add_vertex(2)};
  graph.add_edge(vertex_1, vertex_2, 1.0F);

  return graph.edge_count() == 1 ? 0 : 1;
}
