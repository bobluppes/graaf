#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::properties
{

template<typename V, typename E, graph_type T>
[[nodiscard]]
std::size_t vertex_degree(graaf::graph<V, E, T> const& graph, vertex_id_t vertex_id);

template<typename V, typename E, graph_type T>
[[nodiscard]]
std::size_t vertex_outdegree(graaf::graph<V, E, T> const& graph, vertex_id_t vertex_id);

template<typename V, typename E, graph_type T>
[[nodiscard]]
std::size_t vertex_indegree(graaf::graph<V, E, T> const& graph, vertex_id_t vertex_id);

} // namespace graaf::properties

#include "vertex_properties.tpp"
