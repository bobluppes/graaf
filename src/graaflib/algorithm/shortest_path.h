#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <concepts>
#include <optional>
#include <vector>

namespace graaf::algorithm {

enum class edge_strategy { WEIGHTED, UNWEIGHTED };

template <typename E>
struct GraphPath {
  std::vector<vertex_id_t> vertices;
  E total_weight;

  bool operator==(const GraphPath& other) const {
    return vertices == other.vertices && total_weight == other.total_weight;
  }
};

template <edge_strategy EDGE_STRATEGY, typename V, typename E, graph_spec S>
std::optional<GraphPath<E>> get_shortest_path(const graph<V, E, S>& graph,
                                              vertex_id_t start_vertex,
                                              vertex_id_t end_vertex);

}  // namespace graaf::algorithm

#include "shortest_path.tpp"