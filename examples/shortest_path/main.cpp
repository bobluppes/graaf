#include <fmt/core.h>
#include <graaflib/algorithm/shortest_path/bfs_shortest_path.h>
#include <graaflib/graph.h>
#include <graaflib/io/dot.h>
#include <graaflib/types.h>

#include <cassert>
#include <filesystem>
#include <string>
#include <unordered_set>

struct graph_with_start_and_target {
  graaf::directed_graph<int, int> graph{};
  graaf::vertex_id_t start{};
  graaf::vertex_id_t target{};
};

graph_with_start_and_target create_graph_with_start_and_target() {
  graaf::directed_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};
  const auto vertex_6{graph.add_vertex(60)};

  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_3, vertex_2, 200);
  graph.add_edge(vertex_3, vertex_5, 300);
  graph.add_edge(vertex_2, vertex_4, 400);
  graph.add_edge(vertex_4, vertex_3, 500);
  graph.add_edge(vertex_4, vertex_6, 600);
  graph.add_edge(vertex_6, vertex_3, 700);

  return {graph, vertex_1, vertex_3};
}

int main() {
  const auto [graph, start, target]{create_graph_with_start_and_target()};

  const auto maybe_shortest_path{
      graaf::algorithm::bfs_shortest_path(graph, start, target)};
  assert(maybe_shortest_path.has_value());
  auto shortest_path{maybe_shortest_path.value()};

  std::unordered_set<graaf::edge_id_t, graaf::edge_id_hash>
      edges_on_shortest_path{};

  graaf::vertex_id_t prev{shortest_path.vertices.front()};
  shortest_path.vertices.pop_front();
  for (const auto current : shortest_path.vertices) {
    edges_on_shortest_path.insert(std::make_pair(prev, current));
    prev = current;
  }

  // TODO(bluppes): Directly capture local binding once we have support for it
  // in Clang-16
  const auto vertex_writer{
      [start = start, target = target](graaf::vertex_id_t vertex_id,
                                       int vertex) -> std::string {
        if (vertex_id == start) {
          return "label=start, fillcolor=white, style=filled";
        } else if (vertex_id == target) {
          return "label=target, fillcolor=white, style=filled";
        }
        return "label=\"\", color=gray, fillcolor=white, style=filled";
      }};

  const auto edge_writer{
      [&edges_on_shortest_path](const graaf::edge_id_t& edge_id,
                                const auto& /*edge*/) -> std::string {
        if (edges_on_shortest_path.contains(edge_id)) {
          return "label=\"\", color=red";
        }
        return "label=\"\", color=gray, style=dashed";
      }};

  const std::filesystem::path output{"shortest_path.dot"};
  graaf::io::to_dot(graph, output, vertex_writer, edge_writer);
}