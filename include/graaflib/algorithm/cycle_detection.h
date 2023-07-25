#pragma once

#include <graaflib/graph.h>

namespace graaf::algorithm {

/*
 * @breif Traverses the graph and checks for cycles.
 *
 * @param graph The graph to traverse.
 */
template <typename V, typename E, graph_spec S>
[[nodiscard]] bool has_cycle(const graph<V, E, S> &graph);

}  // namespace graaf::algorithm

#include "cycle_detection.tpp"