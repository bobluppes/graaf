#pragma once

#include <fmt/core.h>
#include <graaflib/graph.h>

#include <fstream>
#include <string_view>

namespace graaf::io {

namespace detail {

/**
 * @brief Converts a graph specialization to the correct dot keyword.
 *
 * DIRECTED: graph
 * UNDIRECTED: digraph
 *
 * @param spec The graph specialization
 * @return constexpr const char* String with the correct dot keyword
 */
constexpr const char* spec_to_string(const graph_spec& spec) {
  switch (spec) {
    using enum graph_spec;
    case DIRECTED:
      return "digraph";
      break;
    case UNDIRECTED:
      return "graph";
      break;
    // LCOV_EXCL_START
    default:
      // We should never reach this
      std::abort();
      // LCOV_EXCL_STOP
  }
}

/**
 * @brief Converts a graph specialization to the correct dot edge specifier.
 *
 * DIRECTED: ->
 * UNDIRECTED: --
 *
 * @param spec The graph specialization
 * @return constexpr const char* String with the correct dot edge specifier
 */
constexpr const char* spec_to_edge_specifier(const graph_spec& spec) {
  switch (spec) {
    using enum graph_spec;
    case DIRECTED:
      return "->";
      break;
    case UNDIRECTED:
      return "--";
      break;
    // LCOV_EXCL_START
    default:
      // We should never reach this
      std::abort();
      // LCOV_EXCL_STOP
  }
}
}  // namespace detail

template <typename V, typename E, graph_spec S, typename VERTEX_WRITER_T,
          typename EDGE_WRITER_T>
  requires std::is_invocable_r_v<std::string, const VERTEX_WRITER_T&,
                                 vertex_id_t, const V&> &&
           std::is_invocable_r_v<std::string, const EDGE_WRITER_T&,
                                 const graaf::edge_id_t&,
                                 const typename graph<V, E, S>::edge_t&>
void to_dot(const graph<V, E, S>& graph, const std::filesystem::path& path,
            const VERTEX_WRITER_T& vertex_writer,
            const EDGE_WRITER_T& edge_writer) {
  std::ofstream dot_file{path};

  const auto append_line{
      [&dot_file](const std::string& line) { dot_file << line << std::endl; }};

  append_line(fmt::format("{} {{", detail::spec_to_string(S)));

  for (const auto& [vertex_id, vertex] : graph.get_vertices()) {
    append_line(
        fmt::format("\t{} [{}];", vertex_id, vertex_writer(vertex_id, vertex)));
  }

  const auto edge_specifier{detail::spec_to_edge_specifier(S)};
  for (const auto& [edge_id, edge] : graph.get_edges()) {
    const auto [source_id, target_id]{edge_id};
    append_line(fmt::format("\t{} {} {} [{}];", source_id, edge_specifier,
                            target_id, edge_writer(edge_id, edge)));
  }

  append_line("}");
}

}  // namespace graaf::io