#pragma once

#include <graaflib/algorithm/cycle_detection.h>
#include <graaflib/algorithm/topological_sorting.h>

#include <vector>
#include <unordered_map>

namespace graaf::algorithm {

namespace detail {

enum class vertex_status { UNVISITED, VISITED};

// DFS topological sort
template <typename V, typename E>
void do_dfs_topological_sort(
    const graph<V, E, graph_type::DIRECTED>& graph,
    vertex_id_t start_vertex,
    std::unordered_map<vertex_id_t, vertex_status>& processed_vertices,
    std::vector<vertex_id_t>& sorted_vertices) {
    
    processed_vertices[start_vertex] = vertex_status::VISITED;
    for (const auto& next_vertex : graph.get_neighbors(start_vertex)) {
        if (processed_vertices[next_vertex] == vertex_status::UNVISITED) {
            do_dfs_topological_sort(graph, next_vertex, processed_vertices,
                sorted_vertices);
        }
    }

        sorted_vertices.push_back(start_vertex);
    }

}; // namespace detail

template <typename V, typename E>
std::vector<vertex_id_t> topological_sort(
    const graph<V, E, graph_type::DIRECTED>& graph) {
    
    // Graph should be acyclic
    if (dfs_cycle_detection(graph)) {
        return {};    
    }

    using enum detail::vertex_status;
    std::vector<vertex_id_t> sorted_vertices{};
    sorted_vertices.reserve(graph.vertex_count());
    std::unordered_map<vertex_id_t, detail::vertex_status> processed_vertices{};

    for (const auto& vertex : graph.get_vertices()) {
        if (processed_vertices[vertex.first] == UNVISITED) {
            detail::do_dfs_topological_sort(graph, vertex.first, processed_vertices, sorted_vertices);
        }
    }

    std::reverse(sorted_vertices.begin(), sorted_vertices.end());
    return sorted_vertices;
}

};  // namespace graaf::algorithm
