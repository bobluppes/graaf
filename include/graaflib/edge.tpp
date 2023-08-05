#pragma once

namespace graaf {

template <typename WEIGHTED_EDGE_T>
  requires derived_from_weighted_edge<WEIGHTED_EDGE_T>
auto get_weight(const WEIGHTED_EDGE_T& edge) {
  return edge.get_weight();
}

template <typename EDGE_T>
  requires std::is_arithmetic_v<EDGE_T>
EDGE_T get_weight(const EDGE_T& edge) {
  return edge;
}

template <typename EDGE_T>
int get_weight(const EDGE_T& /*edge*/) {
  // By default, an edge has unit weight
  return 1;
}

}  // namespace graaf