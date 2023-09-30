#include <fmt/core.h>
#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>
#include <graaflib/algorithm/graph_traversal/common.h>
#include <graaflib/algorithm/shortest_path/bfs_shortest_path.h>
#include <graaflib/algorithm/shortest_path/dijkstra_shortest_path.h>
#include <graaflib/graph.h>
#include <graaflib/io/dot.h>
#include <graaflib/types.h>

#include <optional>
#include <unordered_set>

struct station {
  std::string name{};
};

struct railroad : public graaf::weighted_edge<double> {
  double kilometers{};
  [[nodiscard]] double get_weight() const noexcept override {
    return kilometers;
  }
  railroad(double distance) : kilometers(distance) {}
  ~railroad() {}
};

struct graph_with_start_and_target {
  graaf::undirected_graph<station, railroad> graph{};
  graaf::vertex_id_t start{};
  graaf::vertex_id_t target{};
};

graph_with_start_and_target create_graph_with_start_and_target() {
  graaf::undirected_graph<station, railroad> my_stations{};

  // Germany railway stations
  const auto station_13{my_stations.add_vertex(station{"Hamburg"})};
  const auto station_12{my_stations.add_vertex(station{"Bremen"})};
  const auto station_3{
      my_stations.add_vertex(station{"Berlin Central Station"})};
  const auto station_4{
      my_stations.add_vertex(station{"Hannover Hauptbahnhof"})};
  const auto station_11{my_stations.add_vertex(station{"Dortmund"})};
  const auto station_5{my_stations.add_vertex(station{"Kassel Hbf"})};
  const auto station_2{
      my_stations.add_vertex(station{"Leipzig Central Station"})};
  const auto station_1{
      my_stations.add_vertex(station{"Dresden Central Station"})};
  const auto station_10{
      my_stations.add_vertex(station{"Cologne Hauptbahnhof"})};
  const auto station_9{
      my_stations.add_vertex(station{"Frankfurt Hauptbahnhof"})};
  const auto station_6{
      my_stations.add_vertex(station{"Nurnberg Central Station"})};
  const auto station_8{
      my_stations.add_vertex(station{"Stuttgart Central Station"})};
  const auto station_7{my_stations.add_vertex(station{"Munchen Hbf"})};

  // Canada railway stations
  const auto station_14{
      my_stations.add_vertex(station{"Edmonton central station"})};
  const auto station_15{
      my_stations.add_vertex(station{"Toronto Union Station"})};

  my_stations.add_edge(station_1, station_2, 357.3);
  my_stations.add_edge(station_1, station_3, 730.67);
  my_stations.add_edge(station_3, station_4, 533.3);
  my_stations.add_edge(station_2, station_5, 693.3);
  my_stations.add_edge(station_2, station_4, 1152);
  my_stations.add_edge(station_4, station_5, 288);
  my_stations.add_edge(station_2, station_6, 741.3);
  my_stations.add_edge(station_5, station_6, 1464);
  my_stations.add_edge(station_7, station_6, 432);
  my_stations.add_edge(station_7, station_8, 930);
  my_stations.add_edge(station_8, station_6, 1236);
  my_stations.add_edge(station_9, station_6, 840);
  my_stations.add_edge(station_9, station_10, 498);
  my_stations.add_edge(station_10, station_11, 462);
  my_stations.add_edge(station_13, station_4, 480);
  my_stations.add_edge(station_11, station_5, 822);
  my_stations.add_edge(station_11, station_4, 582);
  my_stations.add_edge(station_11, station_12, 720);
  my_stations.add_edge(station_12, station_13, 330);
  my_stations.add_edge(station_12, station_4, 486);
  my_stations.add_edge(station_13, station_3, 732);

  my_stations.add_edge(station_14, station_15, 9920);

  return {my_stations, station_13, station_6};
}

void print_shortest_path(
    const graaf::undirected_graph<station, railroad>& graph,
    const std::optional<graaf::algorithm::graph_path<double>>& path,
    const std::string& filepath) {
  auto shortest_path{path.value()};
  std::unordered_set<graaf::edge_id_t, graaf::edge_id_hash>
      edges_on_shortest_path{};

  graaf::vertex_id_t prev{shortest_path.vertices.front()};
  shortest_path.vertices.pop_front();
  for (const auto current : shortest_path.vertices) {
    edges_on_shortest_path.insert(std::make_pair(prev, current));
    prev = current;
  }

  const auto vertex_writer{[](graaf::vertex_id_t vertex_id,
                              station vertex) -> std::string {
    const auto style{"filled"};
    return fmt::format(
        "label=\"{}\", style={}, color=black, fontcolor=black, shape=rectangle,"
        "fillcolor=mediumspringgreen",
        vertex.name, style);
  }};

  const auto edge_writer{[&edges_on_shortest_path](
                             const graaf::edge_id_t& edge_id,
                             const auto& edge) -> std::string {
    const auto style{"solid"};
    if (edges_on_shortest_path.contains({edge_id.first, edge_id.second}) ||
        edges_on_shortest_path.contains({edge_id.second, edge_id.first})) {
      return fmt::format("label=\"{}\", style={}, color=red, fontcolor=black",
                         edge.kilometers, style);
    }
    return fmt::format("label=\"{}\", style={}, color=black, fontcolor=black",
                       edge.kilometers, style);
  }};

  const std::filesystem::path output{filepath};
  graaf::io::to_dot(graph, output, vertex_writer, edge_writer);
}

using seen_edges_t = std::unordered_set<graaf::edge_id_t, graaf::edge_id_hash>;
struct record_edges_callback {
  seen_edges_t& seen_edges;

  record_edges_callback(seen_edges_t& seen_edges) : seen_edges{seen_edges} {}

  void operator()(const graaf::edge_id_t& edge) const {
    seen_edges.insert(edge);
  }
};

void print_visited_vertices(
    const graaf::undirected_graph<station, railroad>& graph,
    seen_edges_t& seen_edges, const std::string& filepath) {
  const auto vertex_writer{[](graaf::vertex_id_t vertex_id,
                              station vertex) -> std::string {
    const auto style{"filled"};

    return fmt::format(
        "label=\"{}\", style={}, color=black, fontcolor=black, shape=rectangle,"
        "fillcolor=mediumspringgreen",
        vertex.name, style);
  }};

  const auto edge_writer{[&seen_edges](const graaf::edge_id_t& edge_id,
                                       const auto& edge) -> std::string {
    const auto style{"solid"};

    if (seen_edges.contains({edge_id.first, edge_id.second}) ||
        seen_edges.contains({edge_id.second, edge_id.first}))
      return fmt::format("label=\"{}\", style={}, color=red, fontcolor=black",
                         edge.kilometers, style);
    return fmt::format("label=\"{}\", style={}, color=black, fontcolor=black",
                       edge.kilometers, style);
  }};

  const std::filesystem::path output{filepath};
  graaf::io::to_dot(graph, output, vertex_writer, edge_writer);
}

int main() {
  const auto [graph, start, target]{create_graph_with_start_and_target()};

  const auto weighted_shortest_path{
      graaf::algorithm::dijkstra_shortest_path(graph, start, target)};
  print_shortest_path(graph, weighted_shortest_path,
                      "example_weighted_graph.dot");

  const auto unweighted_shortest_path{
      graaf::algorithm::bfs_shortest_path(graph, start, target)};
  print_shortest_path(graph, unweighted_shortest_path,
                      "example_unwieghted_graph.dot");

  seen_edges_t seen_edges{};
  graaf::algorithm::breadth_first_traverse(graph, start,
                                           record_edges_callback{seen_edges});
  print_visited_vertices(graph, seen_edges, "example_traverse_BFS_graph.dot");
}
