#include <fmt/core.h>
#include <graaflib/algorithm/graph_traversal.h>
#include <graaflib/algorithm/shortest_path.h>
#include <graaflib/io/dot.h>
#include <graaflib/types.h>
#include <graaflib/undirected_graph.h>

struct station {
  std::string name{};
  double gaz_capacity{};
};

struct road {
  int length{};
  int get_weight() { return length; }
};

struct graph_with_start_and_target {
  graaf::undirected_graph<station, road> graph{};
  graaf::vertex_id_t start{};
  graaf::vertex_id_t target{};
};

graph_with_start_and_target create_graph_with_start_and_target() {
  graaf::undirected_graph<station, road> my_stations{};

  const auto station_1{my_stations.add_vertex(station{"Road 66", 13.5})};
  const auto station_2{my_stations.add_vertex(station{"Long road", 7.3})};
  const auto station_3{my_stations.add_vertex(station{"Stop & Buy", 25.4})};
  const auto station_4{my_stations.add_vertex(station{"GAZilla", 11.3})};
  const auto station_5{my_stations.add_vertex(station{"Station 32", 73.12})};
  const auto station_6{my_stations.add_vertex(station{"Last stop", 0.5})};
  const auto station_7{my_stations.add_vertex(station{"You won't reach it", 55.5})};
  const auto station_8{my_stations.add_vertex(station{"Went for lunch break", 66.5})};

  my_stations.add_edge(station_1, station_2, road{125});
  my_stations.add_edge(station_2, station_4, road{205});
  my_stations.add_edge(station_4, station_5, road{325});
  my_stations.add_edge(station_5, station_3, road{1725});
  my_stations.add_edge(station_6, station_3, road{88});
  my_stations.add_edge(station_1, station_5, road{77});
  my_stations.add_edge(station_5, station_2, road{93});
  my_stations.add_edge(station_5, station_6, road{193});
  my_stations.add_edge(station_7, station_8, road{5});

  return {my_stations, station_1, station_3};
}

void print_shortest_path(const graaf::undirected_graph<station, road>& graph,
        const std::optional<graaf::algorithm::GraphPath<int>>& path,
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

    const auto vertex_writer{
        [](graaf::vertex_id_t vertex_id, station vertex) -> std::string {
        const auto style{"solid"};
        return fmt::format("label=\"{}: {}\", style={}, color=black, fontcolor=black",
                            vertex.name, style);
    }};

    const auto edge_writer{[&edges_on_shortest_path](
                                const graaf::edge_id_t& edge_id,
                                const auto& edge) -> std::string {
        const auto style{"solid"};
        if (edges_on_shortest_path.contains({edge_id.first, edge_id.second}) ||
            edges_on_shortest_path.contains({edge_id.second, edge_id.first})) {
            return fmt::format("label=\"{}\", style={}, color=red, fontcolor=black",
                                edge->length, style);
        }
        return fmt::format("label=\"{}\", style={}, color=black, fontcolor=black",
                       edge->length, style);
    }};

  const std::filesystem::path output{filepath};
  graaf::io::to_dot(graph, output, vertex_writer, edge_writer);
}

using seen_vertices_t = std::unordered_multiset<graaf::vertex_id_t>;
struct record_vertex_callback {
  seen_vertices_t& seen_vertices;

  record_vertex_callback(seen_vertices_t& seen_vertices)
      : seen_vertices{seen_vertices} {}

  void operator()(const graaf::vertex_id_t vertex) const {
    seen_vertices.insert(vertex);
  }
};

void print_visited_vertices(const graaf::undirected_graph<station, road>& graph,
                            seen_vertices_t& seen,
                            const std::string& filepath) {
  std::unordered_set<graaf::edge_id_t, graaf::edge_id_hash> seen_edges{};

  for (const auto current : graph.get_edges()) {
    const auto from = current.first.first;
    const auto to = current.first.second;
    if (seen.contains(from) && seen.contains(to)) 
        seen_edges.insert({from, to});
  }

  const auto vertex_writer{
      [](graaf::vertex_id_t vertex_id, station vertex) -> std::string {
        const auto style{"solid"};

        return fmt::format(
            "label=\"{}: {}\", style={}, color=gray, fontcolor=black",
            vertex.name, style);
  }};

  const auto edge_writer{[&seen_edges](const graaf::edge_id_t& edge_id,
                                       const auto& edge) -> std::string {
    const auto style{"solid"};

    if (seen_edges.contains({edge_id.first, edge_id.second}) ||
        seen_edges.contains({edge_id.second, edge_id.first}))
            return fmt::format("label=\"{}\", style={}, color=red, fontcolor=black",
                            edge->length, style);
    return fmt::format("label=\"{}\", style={}, color=black, fontcolor=black",
                       edge->length, style);
  }};

  const std::filesystem::path output{filepath};
  graaf::io::to_dot(graph, output, vertex_writer, edge_writer);
}

int main() {
  const auto [graph, start, target]{create_graph_with_start_and_target()};

  const auto weighted_shortest_path{graaf::algorithm::get_shortest_path<
      graaf::algorithm::edge_strategy::WEIGHTED, station, road,
      graaf::graph_spec::UNDIRECTED, int>(graph, start, target)};
  print_shortest_path(graph, weighted_shortest_path, "example_weighted_graph.dot");

  const auto unweighted_shortest_path{graaf::algorithm::get_shortest_path<
      graaf::algorithm::edge_strategy::UNWEIGHTED, station, road,
      graaf::graph_spec::UNDIRECTED, int>(graph, start, target)};
  print_shortest_path(graph, unweighted_shortest_path, "example_unwieghted_graph.dot");

  seen_vertices_t seen_vertices{};
  graaf::algorithm::traverse<graaf::algorithm::search_strategy::BFS>(
      graph, start, record_vertex_callback{seen_vertices});
  print_visited_vertices(graph, seen_vertices, "example_traverse_BFS_graph.dot");
}
