#include "farthest_vertex.h"

#include <algorithm>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <vector>

namespace utils {

std::size_t find_farthest_vertex(const graph_t& graph,
                                 const std::size_t start_vertex) {
  std::vector<int> distances(boost::num_vertices(graph));
  boost::dijkstra_shortest_paths(
      graph, start_vertex,
      boost::distance_map(boost::make_iterator_property_map(
          distances.begin(), boost::get(boost::vertex_index, graph))));

  return static_cast<std::size_t>(
      std::max_element(distances.begin(), distances.end()) - distances.begin());
}

}  // namespace utils
