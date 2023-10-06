#pragma once

#include <graaflib/algorithm/clique/bron_kerbosch.h>

#include <iostream>
#include <iterator>
#include <optional>
#include <ranges>
#include <unordered_set>
#include <vector>

namespace graaf::algorithm {

namespace detail {

void do_get_intersection(std::unordered_set<vertex_id_t>& s1,
                         std::unordered_set<vertex_id_t>& s2,
                         std::unordered_set<vertex_id_t>& intersection) {
  for (const auto& vertex : s1) {
    if (s2.find(vertex) != s2.end()) {
      intersection.insert(vertex);
    }
  }
}

template <typename V, typename E>
void do_bron_kerbosch_maximal_clique(
    std::vector<vertex_id_t>& clique, std::unordered_set<vertex_id_t>& vertices,
    std::unordered_set<vertex_id_t>& excluded_vertices,
    std::vector<std::vector<vertex_id_t>>& maximal_cliques,
    const graph<V, E, graph_type::UNDIRECTED>& graph) {
  if (vertices.empty() && excluded_vertices.empty()) {
    maximal_cliques.push_back(clique);
    return;
  }

  // union_set = candidate_vertices ⋃ excluded_vertices
  auto union_set = vertices;
  for (const auto& vertex : excluded_vertices) union_set.insert(vertex);

  // Get pivot vertex with most amount of neighbors
  // to reduce recursion calls
  auto pivot_vertex = *union_set.begin();
  for (const auto& vertex : union_set) {
    if (graph.get_neighbors(pivot_vertex).size() <
        graph.get_neighbors(vertex).size()) {
      pivot_vertex = vertex;
    }
  }

  // vertices_to_process = candidate_vertices \ N(pivot_vertex)
  auto vertices_to_process = vertices;
  for (const auto& vertex : graph.get_neighbors(pivot_vertex)) {
    vertices_to_process.erase(vertex);
  }

  for (const auto& vertex : vertices_to_process) {
    auto vertex_neighbors = graph.get_neighbors(vertex);

    // Intersection candidate_vertices ⋂ N(vertex)
    std::unordered_set<vertex_id_t> vertices_intersection{};
    do_get_intersection(vertices, vertex_neighbors, vertices_intersection);

    // Intersection excluded_vertices ⋂ N(vertex)
    std::unordered_set<vertex_id_t> exclude_intersection{};
    do_get_intersection(excluded_vertices, vertex_neighbors,
                        exclude_intersection);

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
  std::vector<std::vector<vertex_id_t>> maximal_cliques{};

  std::vector<vertex_id_t> clique;
  std::unordered_set<vertex_id_t> vertices, excluded;
  for (const auto& [vertex, _] : graph.get_vertices()) {
    vertices.insert(vertex);
  }
  detail::do_bron_kerbosch_maximal_clique(clique, vertices, excluded,
                                          maximal_cliques, graph);

  return maximal_cliques;
}

};  // namespace graaf::algorithm