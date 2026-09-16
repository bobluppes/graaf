#pragma once

#include "dataset_reader.h"

namespace utils {

// Explores graph breadth-first from start_vertex and returns the subgraph
// made up of the first max_vertices vertices discovered (and the edges
// between them). Used by benchmarks that need to bound how much of a large,
// real-world dataset they run against.
[[nodiscard]] graph_t compute_connected_subgraph(
    const graph_t& graph, graaf::vertex_id_t start_vertex,
    std::size_t max_vertices);

}  // namespace utils
