#pragma once

#include <algorithm>
#include <unordered_map>

namespace graaf::algorithm {

namespace detail {

enum vertex_color{WHITE, GREY, BLACK};

template <typename V, typename E, graph_spec S>
bool do_dfs_directed(const graph<V, E, S>& graph,
                     std::unordered_map<vertex_id_t, int>& colored_vertices,
                     vertex_id_t current) {
  colored_vertices[current] = vertex_color::GREY;

  for (const auto& neighbour_vertex : graph.get_neighbors(current)) {
    if (colored_vertices[neighbour_vertex] == vertex_color::WHITE) {
        if (do_dfs_directed(graph, colored_vertices, neighbour_vertex))
            return true;
    } 
    else if (colored_vertices[neighbour_vertex] == vertex_color::GREY) {
      return true;
    }
  }

  colored_vertices[current] = vertex_color::BLACK;
  return false;
}

template<typename V, typename E, graph_spec S>
bool do_dfs_undirected(const graph<V,E,S> & graph, 
    std::unordered_map<vertex_id_t, bool> & visited_vertices,
    std::unordered_map<vertex_id_t, vertex_id_t> & parent_vertices,
    vertex_id_t parent_vertex, vertex_id_t current) {

    visited_vertices[current] = true;

    for (const auto& neighbour_vertex : graph.get_neighbors(current)) {
        if (neighbour_vertex == parent_vertex) 
            continue;

        if (visited_vertices[neighbour_vertex]) 
            return true;

        parent_vertices[neighbour_vertex] = parent_vertex;

        if (do_dfs_undirected(graph, visited_vertices, parent_vertices, neighbour_vertex,
                            parent_vertices[neighbour_vertex])) {
                                     return true;
        }
    }

    return false;
}

}  // namespace detail

template <typename V, typename E, graph_spec S>
bool has_cycle(const graph<V, E, S>& graph) {


  if (graph.is_directed()) {
        std::unordered_map<vertex_id_t, int> colored_vertices{};

        for (const auto& vertex : graph.get_vertices()) {
            if (!colored_vertices.contains(vertex.first) &&
                detail::do_dfs_directed(graph, colored_vertices, vertex.first)) {
                        return true;
            }
        }

    return false;
  }

  if (graph.is_undirected()) {
        std::unordered_map<vertex_id_t, bool> visited_vertices{};
        std::unordered_map<vertex_id_t, vertex_id_t> parent_vertices{};

        for (const auto& vertex : graph.get_vertices()) {
            if (!visited_vertices.contains(vertex.first) &&
                 detail::do_dfs_undirected(graph, visited_vertices, parent_vertices,
                                      vertex.first, parent_vertices[vertex.first])) {
                         return true;
            }
        }
  }

  return false;

  // We should never reach this
  std::abort();
}

}  // namespace graaf::algorithm