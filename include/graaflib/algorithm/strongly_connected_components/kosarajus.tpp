#pragma once

#include <graaflib/algorithm/graph_traversal/depth_first_search.h>
#include <graaflib/algorithm/strongly_connected_components/kosarajus.h>

#include <stack>

namespace graaf::algorithm {

template <typename V, typename E>
std::vector<std::vector<vertex_id_t>> kosarajus_strongly_connected_components(
    const graph<V, E, graph_type::DIRECTED>& graph) {
  // Vector to store strongly connected components
  std::vector<std::vector<vertex_id_t>> sccs;

  // Stack to hold vertices during traversal
  std::stack<vertex_id_t> stack;
}

}  // namespace graaf::algorithm
