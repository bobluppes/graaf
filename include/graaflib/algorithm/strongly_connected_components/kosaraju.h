#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <vector>

namespace graaf::algorithm {

template <typename V, typename E>
std::vector<std::vector<vertex_id_t>> kosarajus_strongly_connected_components(
    const graph<V, E, graph_type::DIRECTED>& graph
);

}  // namespace graaf::algorithm

#include "kosaraju.tpp"