#pragma once

#include "dataset_reader.h"

namespace utils {

// Finds the vertex farthest (by total edge weight) from start_vertex.
//
// Useful for single-pair shortest path benchmarks: searching to the
// farthest vertex forces the search to explore close to the entire
// reachable graph before it can terminate early. A hardcoded/arbitrary
// target vertex id can happen to sit very close to start_vertex in one
// dataset and far in another, making the two datasets' results
// incomparable.
[[nodiscard]] graaf::vertex_id_t find_farthest_vertex(
    const graph_t& graph, graaf::vertex_id_t start_vertex);

}  // namespace utils
