#pragma once

#include <graaflib/graph.h>

#include <concepts>
#include <filesystem>
#include <string>
#include <type_traits>

namespace graaf::io
{

namespace detail
{

    template<typename T>
    concept string_convertible = requires(T element) { std::to_string(element); };

    template<typename T>
        requires string_convertible<T>
    auto const default_vertex_writer {
        [](vertex_id_t vertex_id, T const& vertex) -> std::string
        {
            // TODO(bluppes): replace with std::format once Clang supports it
            return "label=\"" + std::to_string(vertex_id) + ": " +
                   std::to_string(vertex) + "\"";
        }};

    auto const default_edge_writer {
        [](edge_id_t const& /*edge_id*/, auto const& edge) -> std::string
        {
            // TODO(bluppes): replace with std::format once Clang supports it
            return "label=\"" + std::to_string(get_weight(edge)) + "\"";
        }};
} // namespace detail

/**
 * @brief Serializes a graph to dot format and writes the result to a file.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The graph we want to serialize.
 * @param vertex_writer Function used for serializing the vertices. Should
 * accept a vertex_id_t and a type V and serialize it to a string. Default
 * implementations are provided for primitive numeric types.
 * @param edge_writer Function used for serializing the edges. Should accept an
 * edge_id_t and a graph::edge_t and serialize it to a string. Default
 * implementations are provided for primitive numeric types.
 * @param path Path to the output dot file.
 */
template<typename V,
         typename E,
         graph_type T,
         typename VERTEX_WRITER_T = decltype(detail::default_vertex_writer<V>),
         typename EDGE_WRITER_T   = decltype(detail::default_edge_writer)>
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
            const VERTEX_WRITER_T& vertex_writer = detail::default_vertex_writer<V>,
            const EDGE_WRITER_T& edge_writer     = detail::default_edge_writer);

} // namespace graaf::io

#include "dot.tpp"
