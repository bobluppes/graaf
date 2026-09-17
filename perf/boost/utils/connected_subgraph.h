#pragma once

#include "dataset_reader.h"

namespace utils {

struct connected_subgraph_result {
  graph_t graph;
  boost::graph_traits<graph_t>::vertex_descriptor start_vertex;
};

// Builds the subgraph made up of the first max_vertices vertices discovered
// by a breadth-first exploration of dataset_name's edge list, starting from
// start_vertex.
//
// Unlike utils::construct_graph_from_file(), the returned graph's vertex
// descriptors are not the original dataset vertex IDs: boost::adjacency_list
// with vecS vertex storage requires a dense 0..N-1 index range, so the
// (sparse, large) dataset IDs are remapped to compact indices. The caller
// gets the remapped start vertex back alongside the graph for this reason.
[[nodiscard]] connected_subgraph_result construct_connected_subgraph(
    const dataset& dataset_name, std::size_t start_vertex,
    std::size_t max_vertices);

}  // namespace utils
