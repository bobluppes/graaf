#include "connected_subgraph.h"

#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>

namespace utils {

graph_t compute_connected_subgraph(const graph_t& graph,
                                   const graaf::vertex_id_t start_vertex,
                                   const std::size_t max_vertices) {
  graph_t connected_subgraph{};
  connected_subgraph.add_vertex(graph.get_vertex(start_vertex), start_vertex);

  const auto stop_once_full{
      [&connected_subgraph, max_vertices](graaf::vertex_id_t) {
        return connected_subgraph.vertex_count() >= max_vertices;
      }};

  graaf::algorithm::breadth_first_traverse(
      graph, start_vertex,
      [&graph, &connected_subgraph,
       max_vertices](const graaf::edge_id_t& edge) {
        const auto [source, target](edge);

        if (connected_subgraph.vertex_count() >= max_vertices) {
          return;
        }

        if (!connected_subgraph.has_vertex(source)) {
          connected_subgraph.add_vertex(graph.get_vertex(source), source);
        }

        if (!connected_subgraph.has_vertex(target)) {
          connected_subgraph.add_vertex(graph.get_vertex(target), target);
        }

        if (connected_subgraph.has_vertex(source) &&
            connected_subgraph.has_vertex(target) &&
            !connected_subgraph.has_edge(source, target)) {
          connected_subgraph.add_edge(source, target, graph.get_edge(edge));
        }
      },
      stop_once_full);

  return connected_subgraph;
}

}  // namespace utils
