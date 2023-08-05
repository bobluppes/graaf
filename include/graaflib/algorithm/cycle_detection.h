#pragma once

#include <graaflib/graph.h>

namespace graaf::algorithm {

/*
 * @brief Traverses the graph and checks for cycles.
 *
 * @param graph The graph to traverse.
 */
template <typename V, typename E, graph_type T>
[[nodiscard]] bool has_cycle(const graph<V, E, T> &graph);

}  // namespace graaf::algorithm

#include "cycle_detection.tpp"