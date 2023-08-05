#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::properties {

template <typename V, typename E, graph_type T>
[[nodiscard]] std::size_t vertex_degree(const graaf::graph<V, E, T>& graph,
                                        vertex_id_t vertex_id);

template <typename V, typename E, graph_type T>
[[nodiscard]] std::size_t vertex_outdegree(const graaf::graph<V, E, T>& graph,
                                           vertex_id_t vertex_id);

template <typename V, typename E, graph_type T>
[[nodiscard]] std::size_t vertex_indegree(const graaf::graph<V, E, T>& graph,
                                          vertex_id_t vertex_id);

}  // namespace graaf::properties

#include "vertex_properties.tpp"
