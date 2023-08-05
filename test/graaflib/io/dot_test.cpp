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

namespace graaf::io {

namespace {
const auto int_vertex_writer{
    [](vertex_id_t /*vertex_id*/, int vertex) -> std::string {
      return fmt::format("label=\"{}\"", std::to_string(vertex));
    }};

const auto int_edge_writer{
    [](const edge_id_t& /*edge_id*/, const auto& edge) -> std::string {
      return fmt::format("label=\"{}\"", std::to_string(edge->get_weight()));
    }};

template <typename T>
const auto make_vertex_string{
    [](vertex_id_t vertex_id, T vertex_label) -> std::string {
      return fmt::format("{} [label=\"{}\"];", vertex_id,
                         std::to_string(vertex_label));
    }};

template <typename T>
const auto make_edge_string{[](edge_id_t edge_id,
                               const std::string& edge_specifier,
                               T edge_label) -> std::string {
  return fmt::format("{} {} {} [label=\"{}\"];", edge_id.first, edge_specifier,
                     edge_id.second, std::to_string(edge_label));
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
inline std::pair<vertex_id_t, vertex_id_t> make_sorted_pair(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  if (vertex_id_lhs < vertex_id_rhs) {
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
[[nodiscard]] std::string read_to_string(const std::filesystem::path& path) {
  std::ifstream dot_file{path};

  return {std::istreambuf_iterator<char>{dot_file},
          std::istreambuf_iterator<char>{}};
}
}  // namespace

TEST(DotTest, EmptyUndirectedGraph) {
  // GIVEN
  const std::filesystem::path path{"./test.dot"};
  undirected_graph<int, int> graph{};

  // WHEN
  to_dot(graph, path, int_vertex_writer, int_edge_writer);

  // THEN
  const auto dot_content{read_to_string(path)};
  ASSERT_TRUE(dot_content.starts_with("graph"));
}

TEST(DotTest, EmptyDirectedGraph) {
  // GIVEN
  const std::filesystem::path path{"./test.dot"};
  directed_graph<int, int> graph{};

  // WHEN
  to_dot(graph, path, int_vertex_writer, int_edge_writer);

  // THEN
  const auto dot_content{read_to_string(path)};
  ASSERT_TRUE(dot_content.starts_with("digraph"));
}

TEST(DotTest, UndirectedGraph) {
  // GIVEN
  const std::filesystem::path path{"./test.dot"};
  undirected_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_1, vertex_3, 200);
  graph.add_edge(vertex_3, vertex_4, 300);
  graph.add_edge(vertex_5, vertex_3, 400);

  const std::unordered_set<std::string> expected_vertices{
      make_vertex_string<int>(vertex_1, 10),
      make_vertex_string<int>(vertex_2, 20),
      make_vertex_string<int>(vertex_3, 30),
      make_vertex_string<int>(vertex_4, 40),
      make_vertex_string<int>(vertex_5, 50)};
  const std::unordered_set<std::string> expected_edges{
      make_edge_string<int>(make_sorted_pair(vertex_1, vertex_2), "--", 100),
      make_edge_string<int>(make_sorted_pair(vertex_1, vertex_3), "--", 200),
      make_edge_string<int>(make_sorted_pair(vertex_3, vertex_4), "--", 300),
      make_edge_string<int>(make_sorted_pair(vertex_5, vertex_3), "--", 400)};

  // WHEN
  to_dot(graph, path, int_vertex_writer, int_edge_writer);

  // THEN - The order of vertices and edges in the graph is undefined
  // so we only check whether all expected vertices and edges are contained
  const auto dot_content{read_to_string(path)};

  for (const auto& expected_vertex : expected_vertices) {
    ASSERT_TRUE(dot_content.find(expected_vertex) != std::string::npos);
  }

  for (const auto& expected_edge : expected_edges) {
    ASSERT_TRUE(dot_content.find(expected_edge) != std::string::npos);
  }
}

TEST(DotTest, DirectedGraph) {
  // GIVEN
  const std::filesystem::path path{"./test.dot"};
  directed_graph<int, int> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  const auto vertex_3{graph.add_vertex(30)};
  const auto vertex_4{graph.add_vertex(40)};
  const auto vertex_5{graph.add_vertex(50)};

  graph.add_edge(vertex_1, vertex_2, 100);
  graph.add_edge(vertex_1, vertex_3, 200);
  graph.add_edge(vertex_3, vertex_4, 300);
  graph.add_edge(vertex_5, vertex_3, 400);

  const std::unordered_set<std::string> expected_vertices{
      make_vertex_string<int>(vertex_1, 10),
      make_vertex_string<int>(vertex_2, 20),
      make_vertex_string<int>(vertex_3, 30),
      make_vertex_string<int>(vertex_4, 40),
      make_vertex_string<int>(vertex_5, 50)};
  const std::unordered_set<std::string> expected_edges{
      make_edge_string<int>(std::make_pair(vertex_1, vertex_2), "->", 100),
      make_edge_string<int>(std::make_pair(vertex_1, vertex_3), "->", 200),
      make_edge_string<int>(std::make_pair(vertex_3, vertex_4), "->", 300),
      make_edge_string<int>(std::make_pair(vertex_5, vertex_3), "->", 400)};

  // WHEN
  to_dot(graph, path, int_vertex_writer, int_edge_writer);

  // THEN - The order of vertices and edges in the graph is undefined
  // so we only check whether all expected vertices and edges are contained
  const auto dot_content{read_to_string(path)};

  for (const auto& expected_vertex : expected_vertices) {
    ASSERT_TRUE(dot_content.find(expected_vertex) != std::string::npos);
  }

  for (const auto& expected_edge : expected_edges) {
    ASSERT_TRUE(dot_content.find(expected_edge) != std::string::npos);
  }
}

TEST(DotTest, UserProvidedVertexAndEdgeClass) {
  // GIVEN
  struct vertex_t {
    int numeric_data{};
    std::string string_data{};
  };

  struct edge_t {
    int numeric_data{};
    std::string string_data{};
  };

  const std::filesystem::path path{"./test.dot"};
  directed_graph<vertex_t, edge_t> graph{};

  const auto vertex_1{graph.add_vertex(vertex_t{10, "vertex 1"})};
  const auto vertex_2{graph.add_vertex(vertex_t{20, "vertex 2"})};
  graph.add_edge(vertex_1, vertex_2, edge_t{100, "edge 1"});

  const auto vertex_writer{
      [](vertex_id_t /*vertex_id*/, const vertex_t& vertex) {
        return fmt::format("{}, {}", vertex.numeric_data, vertex.string_data);
      }};
  const auto edge_writer{[](const edge_id_t& /*edge_id*/, const auto& edge) {
    return fmt::format("{}, {}", edge->numeric_data, edge->string_data);
  }};

  // WHEN
  to_dot(graph, path, vertex_writer, edge_writer);

  // THEN
  const auto dot_content{read_to_string(path)};
  ASSERT_TRUE(dot_content.find(fmt::format("{} [10, vertex 1];", vertex_1)) !=
              std::string::npos);
  ASSERT_TRUE(dot_content.find(fmt::format("{} [20, vertex 2];", vertex_2)) !=
              std::string::npos);
  ASSERT_TRUE(dot_content.find(fmt::format("{} -> {} [100, edge 1];", vertex_1,
                                           vertex_2)) != std::string::npos);
}

TEST(DotTest, DefaultWriters) {
  // GIVEN
  const std::filesystem::path path{"./test.dot"};
  directed_graph<int, float> graph{};

  const auto vertex_1{graph.add_vertex(10)};
  const auto vertex_2{graph.add_vertex(20)};
  graph.add_edge(vertex_1, vertex_2, 3.3);

  // WHEN
  to_dot(graph, path);

  // THEN
  const auto dot_content{read_to_string(path)};
  ASSERT_TRUE(dot_content.find(fmt::format("{} [label=\"{}: 10\"];", vertex_1,
                                           vertex_1)) != std::string::npos);
  ASSERT_TRUE(dot_content.find(fmt::format("{} [label=\"{}: 20\"];", vertex_2,
                                           vertex_2)) != std::string::npos);
  // For the float value we only check up until the first decimal place
  ASSERT_TRUE(dot_content.find(fmt::format("{} -> {} [label=\"3.3", vertex_1,
                                           vertex_2)) != std::string::npos);
}

}  // namespace graaf::io