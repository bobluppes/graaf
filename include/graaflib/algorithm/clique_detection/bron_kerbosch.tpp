#pragma once

#include <graaflib/algorithm/clique_detection/bron_kerbosch.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <ranges>
#include <unordered_set>
#include <vector>

namespace graaf::algorithm {

namespace detail {
using clique_collection_t = std::vector<std::vector<vertex_id_t>>;
using vertex_set_t = std::unordered_set<vertex_id_t>;

vertex_set_t do_get_intersection(const vertex_set_t& lhs,
                                 const vertex_set_t& rhs) {
  vertex_set_t intersection{};

  for (const auto& vertex : lhs) {
    if (rhs.contains(vertex)) {
      intersection.insert(vertex);
    }
  }

  return intersection;
}

vertex_set_t set_union(const vertex_set_t& lhs, const vertex_set_t& rhs) {
  vertex_set_t union_set = lhs;
  for (const auto& vertex : rhs) union_set.insert(vertex);

  return union_set;
}

vertex_set_t set_difference(const vertex_set_t& lhs, const vertex_set_t rhs) {
  vertex_set_t difference_set = lhs;

  for (const auto& vertex : rhs) {
    difference_set.erase(vertex);
  }

  return difference_set;
}

template <typename V, typename E>
void do_bron_kerbosch_maximal_clique(
    std::vector<vertex_id_t>& clique, vertex_set_t& vertices,
    vertex_set_t& excluded_vertices, clique_collection_t& maximal_cliques,
    const graph<V, E, graph_type::UNDIRECTED>& graph) {
  if (vertices.empty() && excluded_vertices.empty()) {
    maximal_cliques.push_back(clique);
    return;
  }

  // union_set = candidate_vertices ⋃ excluded_vertices
  auto union_set = set_union(vertices, excluded_vertices);

  const auto pivot_vertex = *std::ranges::max_element(
      union_set, {},
      [&graph](vertex_id_t id) { return graph.get_neighbors(id).size(); });

  // vertices_to_process = candidate_vertices \ N(pivot_vertex)
  auto vertices_to_process =
      set_difference(vertices, graph.get_neighbors(pivot_vertex));

  for (const auto& vertex : vertices_to_process) {
    auto vertex_neighbors = graph.get_neighbors(vertex);

    // Intersection candidate_vertices ⋂ N(vertex)
    std::unordered_set<vertex_id_t> vertices_intersection{};
    vertices_intersection = do_get_intersection(vertices, vertex_neighbors);

    // Intersection excluded_vertices ⋂ N(vertex)
    std::unordered_set<vertex_id_t> exclude_intersection{};
    exclude_intersection =
        do_get_intersection(excluded_vertices, vertex_neighbors);

    clique.push_back(vertex);
    do_bron_kerbosch_maximal_clique(clique, vertices_intersection,
                                    exclude_intersection, maximal_cliques,
                                    graph);
    clique.pop_back();

    vertices.erase(vertex);
    excluded_vertices.insert(vertex);
  }
}
};  // namespace detail

template <typename V, typename E>
std::vector<std::vector<vertex_id_t>> bron_kerbosch(
    const graph<V, E, graph_type::UNDIRECTED>& graph) {
  detail::clique_collection_t maximal_cliques{};
  std::vector<vertex_id_t> clique{};
  detail::vertex_set_t vertices{};
  detail::vertex_set_t excluded{};

  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    vertices.insert(vertex_id);
  }
  detail::do_bron_kerbosch_maximal_clique(clique, vertices, excluded,
                                          maximal_cliques, graph);

  return maximal_cliques;
}

};  // namespace graaf::algorithm