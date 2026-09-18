#pragma once

#include "dataset_reader.h"

namespace utils {

struct connected_subgraph_result {
  graph_t graph;
  graaf::vertex_id_t start_vertex;
};

// Builds the subgraph made up of the first max_vertices vertices discovered
// by a breadth-first exploration of dataset_name's edge list, starting from
// start_vertex.
//
// Unlike utils::construct_graph_from_file(), the returned graph's vertex IDs
// are not the original dataset vertex IDs: the graph assigns its own IDs, so
// the original dataset IDs are remapped. The caller gets the remapped start
// vertex back alongside the graph for this reason.
[[nodiscard]] connected_subgraph_result construct_connected_subgraph(
    const dataset& dataset_name, graaf::vertex_id_t start_vertex,
    std::size_t max_vertices);

}  // namespace utils
