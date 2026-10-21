#pragma once
#include <graaflib/algorithm/connectivity/bridges.h>
#include <graaflib/algorithm/connectivity/low_link.h>

#include <vector>

namespace graaf::algorithm {

template <typename V, typename E>
std::vector<edge_id_t> bridges(
    const graph<V, E, graph_type::UNDIRECTED>& graph) {
  return detail::find_cut_structure(graph).bridges;
}

}  // namespace graaf::algorithm
