#pragma once

#include <graaflib/graph.h>

#include <filesystem>
#include <string>
#include <type_traits>

namespace graaf::io {

/**
 * @brief Serializes a graph to dot format and writes the result to a file.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @tparam VERTEX_WRITER_T Should accept a type V and serialize it to a string.
 * @tparam EDGE_WRITER_T Should accept a type E and serialize it to a string.
 * @param graph The graph we want to serialize.
 * @param vertex_writer Function used for serializing the vertices.
 * @param edge_writer Function used for serializing the edges.
 * @param path Path to the output dot file.
 */
template <typename V, typename E, graph_spec S, typename VERTEX_WRITER_T,
          typename EDGE_WRITER_T>
  requires std::is_invocable_r_v<std::string, const VERTEX_WRITER_T&,
                                 const V&> &&
           std::is_invocable_r_v<std::string, const EDGE_WRITER_T&, const E&>
void to_dot(const graph<V, E, S>& graph, const std::filesystem::path& path,
            const VERTEX_WRITER_T& vertex_writer,
            const EDGE_WRITER_T& edge_writer);

}  // namespace graaf::io

#include "dot.tpp"