#pragma once

#include <graaflib/types.h>

#include <algorithm>
#include <unordered_map>

namespace graaf::algorithm {

namespace detail {

enum class vertex_color { UNVISITED, VISITED, NO_CYCLE };

template <typename V, typename E, graph_type T>
bool do_dfs_directed(
    const graph<V, E, T>& graph,
    std::unordered_map<vertex_id_t, vertex_color>& colored_vertices,
    vertex_id_t current) {
  colored_vertices[current] = vertex_color::VISITED;

  for (const auto& neighbour_vertex : graph.get_neighbors(current)) {
    if (colored_vertices[neighbour_vertex] == vertex_color::UNVISITED) {
      if (do_dfs_directed(graph, colored_vertices, neighbour_vertex))
        return true;
    } else if (colored_vertices[neighbour_vertex] == vertex_color::VISITED) {
      return true;
    }
  }

  colored_vertices[current] = vertex_color::NO_CYCLE;
  return false;
}

template <typename V, typename E, graph_type T>
bool do_dfs_undirected(
    const graph<V, E, T>& graph,
    std::unordered_map<vertex_id_t, bool>& visited_vertices,
    std::unordered_map<vertex_id_t, vertex_id_t>& parent_vertices,
    vertex_id_t parent_vertex, vertex_id_t current) {
  visited_vertices[current] = true;

  for (const auto& neighbour_vertex : graph.get_neighbors(current)) {
    if (neighbour_vertex == parent_vertex) continue;

    if (visited_vertices[neighbour_vertex]) return true;

    parent_vertices[neighbour_vertex] = parent_vertex;

    if (do_dfs_undirected(graph, visited_vertices, parent_vertices,
                          neighbour_vertex,
                          parent_vertices[neighbour_vertex])) {
      return true;
    }
  }

  return false;
}

}  // namespace detail

template <typename V, typename E, graph_type T>
bool has_cycle(const graph<V, E, T>& graph) {
  if (graph.is_directed()) {
    std::unordered_map<vertex_id_t, detail::vertex_color> colored_vertices{};

    for (const auto& vertex : graph.get_vertices()) {
      using enum detail::vertex_color;
      if (colored_vertices[vertex.first] == UNVISITED &&
          detail::do_dfs_directed(graph, colored_vertices, vertex.first)) {
        return true;
      }
    }

    return false;
  }

  if (graph.is_undirected()) {
    // Number of vertices cannot be zero (in case if graph is empty)
    if (graph.edge_count() >= graph.vertex_count() &&
        graph.vertex_count() > 0) {
      return true;
    }

    std::unordered_map<vertex_id_t, bool> visited_vertices{};
    std::unordered_map<vertex_id_t, vertex_id_t> parent_vertices{};

    for (const auto& vertex : graph.get_vertices()) {
      if (!visited_vertices.contains(vertex.first) &&
          detail::do_dfs_undirected(graph, visited_vertices, parent_vertices,
                                    vertex.first,
                                    parent_vertices[vertex.first])) {
        return true;
      }
    }
  }

  return false;
}

}  // namespace graaf::algorithm