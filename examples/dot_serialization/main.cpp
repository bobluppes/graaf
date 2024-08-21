#include <fmt/core.h>
#include <graaflib/graph.h>
#include <graaflib/io/dot.h>
#include <graaflib/types.h>

#include <filesystem>
#include <string>

/**
 * @brief A user defined vertex type.
 *
 * Each vertex holds some arbitrary data.
 */
struct my_vertex
{
    int number {};
    std::string name {};
};

enum class edge_priority
{
    LOW,
    HIGH
};

/**
 * @brief A user defined edge type.
 *
 * Each edge has a priority and a weight set.
 */
struct my_edge
{
    edge_priority priority {edge_priority::LOW};
    float weight {};
};

auto create_graph()
{
    graaf::directed_graph<my_vertex, my_edge> graph {};

    auto const vertex_1 {graph.add_vertex(my_vertex {10, "some data"})};
    auto const vertex_2 {graph.add_vertex(my_vertex {20, "some more data"})};
    auto const vertex_3 {graph.add_vertex(my_vertex {30, "abc"})};
    auto const vertex_4 {graph.add_vertex(my_vertex {40, "123"})};
    auto const vertex_5 {graph.add_vertex(my_vertex {50, "xyz"})};

    graph.add_edge(vertex_1, vertex_2, my_edge {edge_priority::HIGH, 3.3});
    graph.add_edge(vertex_2, vertex_1, my_edge {edge_priority::HIGH, 5.0});
    graph.add_edge(vertex_1, vertex_3, my_edge {edge_priority::HIGH, 1.0});
    graph.add_edge(vertex_3, vertex_4, my_edge {edge_priority::LOW, 2.0});
    graph.add_edge(vertex_3, vertex_5, my_edge {edge_priority::HIGH, 3.0});
    graph.add_edge(vertex_2, vertex_5, my_edge {edge_priority::LOW, 42.0});

    return graph;
}

int main()
{
    auto const my_graph {create_graph()};

    auto const vertex_writer {
        [](graaf::vertex_id_t vertex_id, my_vertex const& vertex) -> std::string
        {
            auto const color {vertex.number <= 25 ? "lightcyan" : "mediumspringgreen"};
            return fmt::format("label=\"{}: {}\", fillcolor={}, style=filled",
                               vertex_id,
                               vertex.name,
                               color);
        }};

    auto const edge_writer {
        [](graaf::edge_id_t const& /*edge_id*/, auto const& edge) -> std::string
        {
            auto const style {edge.priority == edge_priority::HIGH ? "solid" : "dashed"};
            return fmt::format(
                "label=\"{}\", style={}, color=gray, fontcolor=gray", edge.weight, style);
        }};

    std::filesystem::path const dof_file_path {"./dot_example.dot"};
    graaf::io::to_dot(my_graph, dof_file_path, vertex_writer, edge_writer);
}
