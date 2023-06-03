#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::properties {

template <typename V, typename E, edge_type T, graph_spec S>
[[nodiscard]] std::size_t get_vertex_degree(
    const graaf::graph<V, E, T, S>& graph, vertex_id_t vertex_id);

template <typename V, typename E, edge_type T, graph_spec S>
[[nodiscard]] std::size_t get_vertex_outdegree(
    const graaf::graph<V, E, T, S>& graph, vertex_id_t vertex_id);

template <typename V, typename E, edge_type T, graph_spec S>
[[nodiscard]] std::size_t get_vertex_indegree(
    const graaf::graph<V, E, T, S>& graph, vertex_id_t vertex_id);

}  // namespace graaf::properties

#include "vertex_properties.tpp"
