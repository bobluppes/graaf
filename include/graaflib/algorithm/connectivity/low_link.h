#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <vector>

namespace graaf::algorithm::detail {

struct cut_structure {
  std::vector<vertex_id_t> articulation_points{};
  std::vector<edge_id_t> bridges{};
};

template <typename V, typename E>
[[nodiscard]] cut_structure find_cut_structure(
    const graph<V, E, graph_type::UNDIRECTED>& graph);

}  // namespace graaf::algorithm::detail

#include "low_link.tpp"
