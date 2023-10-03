#pragma once

#include <graaflib/graph.h>

namespace graaf {

/**
 * Get transposed version of a given directed graph
 *
 * @param  graph The directed graph that is to be transposed
 * @param  out_transposed_graph An out parameter that will contain the
 * transposed graph
 */
template <typename VERTEX_T, typename EDGE_T>
directed_graph<VERTEX_T, EDGE_T> get_transposed_graph(
    const directed_graph<VERTEX_T, EDGE_T>& graph);

}  // namespace graaf

#include "utils.tpp"