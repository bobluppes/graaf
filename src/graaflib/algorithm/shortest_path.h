#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <concepts>
#include <list>
#include <optional>

namespace graaf::algorithm {

enum class edge_strategy { WEIGHTED, UNWEIGHTED };

template <typename E>
struct GraphPath {
  std::list<vertex_id_t> vertices;
  E total_weight;

  bool operator==(const GraphPath& other) const {
    return vertices == other.vertices && total_weight == other.total_weight;
  }
};

/**
 * @brief calculates the shortest path between on start_vertex and one
 * end_vertex.
 *
 * @tparam EDGE_STRATEGY Tag to specify how to handle edges, can be either
 * WEIGHTED or UNWEIGHTED.
 * @param graph The graph to extract shortest path from.
 * @param start_vertex Vertex id where the shortest path should start.
 * @param end_vertex Vertex id where the shortest path should end.
 */
template <edge_strategy EDGE_STRATEGY, typename V, typename E, graph_spec S>
std::optional<GraphPath<E>> get_shortest_path(const graph<V, E, S>& graph,
                                              vertex_id_t start_vertex,
                                              vertex_id_t end_vertex);

}  // namespace graaf::algorithm

#include "shortest_path.tpp"