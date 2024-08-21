#pragma once

#include <graaflib/graph.h>

#include <fstream>
#include <string_view>

namespace graaf::io
{

namespace detail
{

    /**
     * @brief Converts a graph specialization to the correct dot keyword.
     *
     * DIRECTED: graph
     * UNDIRECTED: digraph
     *
     * @param spec The graph specialization
     * @return constexpr const char* String with the correct dot keyword
     */
    char constexpr const* graph_type_to_string(graph_type const& type)
    {
        switch(type)
        {
            using enum graph_type;
        case DIRECTED :
            return "digraph";
            break;
        case UNDIRECTED :
            return "graph";
            break;
        // LCOV_EXCL_START
        default :
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
    char constexpr const* graph_type_to_edge_specifier(graph_type const& type)
    {
        switch(type)
        {
            using enum graph_type;
        case DIRECTED :
            return "->";
            break;
        case UNDIRECTED :
            return "--";
            break;
        // LCOV_EXCL_START
        default :
            // We should never reach this
            std::abort();
            // LCOV_EXCL_STOP
        }
    }
} // namespace detail

template<typename V,
         typename E,
         graph_type T,
         typename VERTEX_WRITER_T,
         typename EDGE_WRITER_T>
    requires std::is_invocable_r_v<std::string,
                                   const VERTEX_WRITER_T&,
                                   vertex_id_t,
                                   V const&> &&
             std::is_invocable_r_v<std::string,
                                   const EDGE_WRITER_T&,
                                   graaf::edge_id_t const&,
                                   typename graph<V, E, T>::edge_t const&>
void to_dot(graph<V, E, T> const& graph,
            std::filesystem::path const& path,
            const VERTEX_WRITER_T& vertex_writer,
            const EDGE_WRITER_T& edge_writer)
{
    std::ofstream dot_file {path};

    auto const append_line {[&dot_file](std::string const& line)
                            {
                                dot_file << line << std::endl;
                            }};

    // TODO(bluppes): replace with std::format once Clang supports it
    append_line(std::string(detail::graph_type_to_string(T)) + " {");

    for(auto const& [vertex_id, vertex]: graph.get_vertices())
    {
        append_line("\t" + std::to_string(vertex_id) + " [" +
                    vertex_writer(vertex_id, vertex) + "];");
    }

    auto const edge_specifier {detail::graph_type_to_edge_specifier(T)};
    for(auto const& [edge_id, edge]: graph.get_edges())
    {
        auto const [source_id, target_id] {edge_id};
        append_line("\t" + std::to_string(source_id) + " " + edge_specifier + " " +
                    std::to_string(target_id) + " [" + edge_writer(edge_id, edge) + "];");
    }

    append_line("}");
}

} // namespace graaf::io
