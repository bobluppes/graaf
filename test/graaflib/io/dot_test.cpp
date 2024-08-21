#include <fmt/core.h>
#include <graaflib/graph.h>
#include <graaflib/io/dot.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>
#include <utility>

namespace graaf::io
{

namespace
{
    auto const int_vertex_writer {[](vertex_id_t /*vertex_id*/, int vertex) -> std::string
                                  {
                                      return fmt::format("label=\"{}\"",
                                                         std::to_string(vertex));
                                  }};

    auto const int_edge_writer {
        [](edge_id_t const& /*edge_id*/, auto const& edge) -> std::string
        {
            return fmt::format("label=\"{}\"", std::to_string(get_weight(edge)));
        }};

    template<typename T>
    auto const make_vertex_string {
        [](vertex_id_t vertex_id, T vertex_label) -> std::string
        {
            return fmt::format(
                "{} [label=\"{}\"];", vertex_id, std::to_string(vertex_label));
        }};

    template<typename T>
    auto const make_edge_string {[](edge_id_t edge_id,
                                    std::string const& edge_specifier,
                                    T edge_label) -> std::string
                                 {
                                     return fmt::format("{} {} {} [label=\"{}\"];",
                                                        edge_id.first,
                                                        edge_specifier,
                                                        edge_id.second,
                                                        std::to_string(edge_label));
                                 }};

    /**
     * @brief Returns a pair with the smalles vertex_id first.
     * Edges from undirected graphs are sorted on vertex ID, this function is used
     * to sort the expected values in the same fashion.
     *
     * @param vertex_id_lhs
     * @param vertex_id_rhs
     * @return std::pair<vertex_id_t, vertex_id_t>
     */
    inline std::pair<vertex_id_t, vertex_id_t> make_sorted_pair(vertex_id_t vertex_id_lhs,
                                                                vertex_id_t vertex_id_rhs)
    {
        if(vertex_id_lhs < vertex_id_rhs)
        {
            return std::make_pair(vertex_id_lhs, vertex_id_rhs);
        }
        return std::make_pair(vertex_id_rhs, vertex_id_lhs);
    }

    /**
     * @brief Reads the entire content of a given file into a string.
     *
     * WARNING: This reads the **entire** content of the file into memory, so this
     * should only be used on relatively small files for testing purposes.
     *
     * @param path Path to the file we want to read.
     * @return std::string String containing the file contents.
     */
    [[nodiscard]]
    std::string read_to_string(std::filesystem::path const& path)
    {
        std::ifstream dot_file {path};

        return {std::istreambuf_iterator<char> {dot_file},
                std::istreambuf_iterator<char> {}};
    }
} // namespace

TEST(DotTest, EmptyUndirectedGraph)
{
    // GIVEN
    std::filesystem::path const path {"./test.dot"};
    undirected_graph<int, int> graph {};

    // WHEN
    to_dot(graph, path, int_vertex_writer, int_edge_writer);

    // THEN
    auto const dot_content {read_to_string(path)};
    ASSERT_TRUE(dot_content.starts_with("graph"));
}

TEST(DotTest, EmptyDirectedGraph)
{
    // GIVEN
    std::filesystem::path const path {"./test.dot"};
    directed_graph<int, int> graph {};

    // WHEN
    to_dot(graph, path, int_vertex_writer, int_edge_writer);

    // THEN
    auto const dot_content {read_to_string(path)};
    ASSERT_TRUE(dot_content.starts_with("digraph"));
}

TEST(DotTest, UndirectedGraph)
{
    // GIVEN
    std::filesystem::path const path {"./test.dot"};
    undirected_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(50)};

    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_1, vertex_3, 200);
    graph.add_edge(vertex_3, vertex_4, 300);
    graph.add_edge(vertex_5, vertex_3, 400);

    std::unordered_set<std::string> const expected_vertices {
        make_vertex_string<int>(vertex_1, 10),
        make_vertex_string<int>(vertex_2, 20),
        make_vertex_string<int>(vertex_3, 30),
        make_vertex_string<int>(vertex_4, 40),
        make_vertex_string<int>(vertex_5, 50)};
    std::unordered_set<std::string> const expected_edges {
        make_edge_string<int>(make_sorted_pair(vertex_1, vertex_2), "--", 100),
        make_edge_string<int>(make_sorted_pair(vertex_1, vertex_3), "--", 200),
        make_edge_string<int>(make_sorted_pair(vertex_3, vertex_4), "--", 300),
        make_edge_string<int>(make_sorted_pair(vertex_5, vertex_3), "--", 400)};

    // WHEN
    to_dot(graph, path, int_vertex_writer, int_edge_writer);

    // THEN - The order of vertices and edges in the graph is undefined
    // so we only check whether all expected vertices and edges are contained
    auto const dot_content {read_to_string(path)};

    for(auto const& expected_vertex: expected_vertices)
    {
        ASSERT_TRUE(dot_content.find(expected_vertex) != std::string::npos);
    }

    for(auto const& expected_edge: expected_edges)
    {
        ASSERT_TRUE(dot_content.find(expected_edge) != std::string::npos);
    }
}

TEST(DotTest, DirectedGraph)
{
    // GIVEN
    std::filesystem::path const path {"./test.dot"};
    directed_graph<int, int> graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    auto const vertex_3 {graph.add_vertex(30)};
    auto const vertex_4 {graph.add_vertex(40)};
    auto const vertex_5 {graph.add_vertex(50)};

    graph.add_edge(vertex_1, vertex_2, 100);
    graph.add_edge(vertex_1, vertex_3, 200);
    graph.add_edge(vertex_3, vertex_4, 300);
    graph.add_edge(vertex_5, vertex_3, 400);

    std::unordered_set<std::string> const expected_vertices {
        make_vertex_string<int>(vertex_1, 10),
        make_vertex_string<int>(vertex_2, 20),
        make_vertex_string<int>(vertex_3, 30),
        make_vertex_string<int>(vertex_4, 40),
        make_vertex_string<int>(vertex_5, 50)};
    std::unordered_set<std::string> const expected_edges {
        make_edge_string<int>(std::make_pair(vertex_1, vertex_2), "->", 100),
        make_edge_string<int>(std::make_pair(vertex_1, vertex_3), "->", 200),
        make_edge_string<int>(std::make_pair(vertex_3, vertex_4), "->", 300),
        make_edge_string<int>(std::make_pair(vertex_5, vertex_3), "->", 400)};

    // WHEN
    to_dot(graph, path, int_vertex_writer, int_edge_writer);

    // THEN - The order of vertices and edges in the graph is undefined
    // so we only check whether all expected vertices and edges are contained
    auto const dot_content {read_to_string(path)};

    for(auto const& expected_vertex: expected_vertices)
    {
        ASSERT_TRUE(dot_content.find(expected_vertex) != std::string::npos);
    }

    for(auto const& expected_edge: expected_edges)
    {
        ASSERT_TRUE(dot_content.find(expected_edge) != std::string::npos);
    }
}

TEST(DotTest, UserProvidedVertexAndEdgeClass)
{
    // GIVEN
    struct vertex_t
    {
        int numeric_data {};
        std::string string_data {};
    };

    struct edge_t
    {
        int numeric_data {};
        std::string string_data {};
    };

    std::filesystem::path const path {"./test.dot"};
    directed_graph<vertex_t, edge_t> graph {};

    auto const vertex_1 {graph.add_vertex(vertex_t {10, "vertex 1"})};
    auto const vertex_2 {graph.add_vertex(vertex_t {20, "vertex 2"})};
    graph.add_edge(vertex_1, vertex_2, edge_t {100, "edge 1"});

    auto const vertex_writer {
        [](vertex_id_t /*vertex_id*/, vertex_t const& vertex)
        {
            return fmt::format("{}, {}", vertex.numeric_data, vertex.string_data);
        }};
    auto const edge_writer {
        [](edge_id_t const& /*edge_id*/, auto const& edge)
        {
            return fmt::format("{}, {}", edge.numeric_data, edge.string_data);
        }};

    // WHEN
    to_dot(graph, path, vertex_writer, edge_writer);

    // THEN
    auto const dot_content {read_to_string(path)};
    ASSERT_TRUE(dot_content.find(fmt::format("{} [10, vertex 1];", vertex_1)) !=
                std::string::npos);
    ASSERT_TRUE(dot_content.find(fmt::format("{} [20, vertex 2];", vertex_2)) !=
                std::string::npos);
    ASSERT_TRUE(dot_content.find(fmt::format(
                    "{} -> {} [100, edge 1];", vertex_1, vertex_2)) != std::string::npos);
}

TEST(DotTest, DefaultWriters)
{
    // GIVEN
    std::filesystem::path const path {"./test.dot"};
    directed_graph<int, float> graph {};

    auto const vertex_1 {graph.add_vertex(10)};
    auto const vertex_2 {graph.add_vertex(20)};
    graph.add_edge(vertex_1, vertex_2, 3.3);

    // WHEN
    to_dot(graph, path);

    // THEN
    auto const dot_content {read_to_string(path)};
    ASSERT_TRUE(dot_content.find(fmt::format(
                    "{} [label=\"{}: 10\"];", vertex_1, vertex_1)) != std::string::npos);
    ASSERT_TRUE(dot_content.find(fmt::format(
                    "{} [label=\"{}: 20\"];", vertex_2, vertex_2)) != std::string::npos);
    // For the float value we only check up until the first decimal place
    ASSERT_TRUE(dot_content.find(fmt::format(
                    "{} -> {} [label=\"3.3", vertex_1, vertex_2)) != std::string::npos);
}

} // namespace graaf::io
