#pragma once

#include <graaflib/algorithm/strongly_connected_components/kosaraju.h>

namespace graaf::algorithm {

template <typename V, typename E>
std::vector<std::vector<vertex_id_t>> kosarajus_strongly_connected_components(
    const graph<V, E, graph_type::DIRECTED>& graph
) {
}


}  // namespace graaf::algorithm
