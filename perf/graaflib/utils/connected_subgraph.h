#pragma once

#include "dataset_reader.h"

namespace utils {

// Builds the subgraph made up of the first max_vertices vertices discovered
// by a breadth-first exploration of dataset_name's edge list, starting from
// start_vertex. Vertex/edge values are copied from the corresponding
// entries in `graph`, which must already hold the full dataset (e.g. as
// returned by construct_graph_from_file(dataset_name)).
[[nodiscard]] graph_t compute_connected_subgraph(
    const graph_t& graph, const dataset& dataset_name,
    graaf::vertex_id_t start_vertex, std::size_t max_vertices);

}  // namespace utils
