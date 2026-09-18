#include "farthest_vertex.h"

#include <graaflib/algorithm/shortest_path/dijkstra_shortest_paths.h>

#include <algorithm>

namespace utils {

graaf::vertex_id_t find_farthest_vertex(const graph_t& graph,
                                        const graaf::vertex_id_t start_vertex) {
  const auto shortest_paths{
      graaf::algorithm::dijkstra_shortest_paths(graph, start_vertex)};

  return std::ranges::max_element(
             shortest_paths, {},
             [](const auto& entry) { return entry.second.total_weight; })
      ->first;
}

}  // namespace utils
