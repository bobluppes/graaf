#pragma once

#include <graaflib/graph.h>

namespace graaf {

/**
 * Get transposed version of a given directed graph
 *
 * @param  graph The directed graph that is to be transposed
 * @return directed_graph<VERTEX_T, EDGE_T> The transposed graph
 */
template <typename VERTEX_T, typename EDGE_T>
directed_graph<VERTEX_T, EDGE_T> get_transposed_graph(
    const directed_graph<VERTEX_T, EDGE_T>& graph);

}  // namespace graaf

#include "utils.tpp"