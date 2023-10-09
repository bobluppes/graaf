#pragma once
#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

/**
 * @brief Applies the Welsh-Powell greedy graph coloring algorithm to the given
 * graph.
 *
 * The function sorts the vertices by their degree in descending order, then
 * attempts to color the graph in a way that no two adjacent vertices share the
 * same color.
 *
 * @tparam GRAPH The graph type.
 * @param graph The input graph to color.
 * @return std::unordered_map<vertex_id_t, int> An unordered map from vertex ID
 * to color if the graph could be colored, or an empty map otherwise.
 */
template <typename GRAPH>
std::unordered_map<vertex_id_t, int> welsh_powell_coloring(const GRAPH& graph);

}  // namespace graaf::algorithm

#include "welsh_powell.tpp"