#pragma once

#include "dataset_reader.h"

namespace utils {

// Builds the subgraph made up of the first max_vertices vertices discovered
// by a breadth-first exploration of dataset_name's edge list, starting from
// start_vertex.
[[nodiscard]] graph_t construct_connected_subgraph(
    const dataset& dataset_name, graaf::vertex_id_t start_vertex,
    std::size_t max_vertices);

}  // namespace utils
