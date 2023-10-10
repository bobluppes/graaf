#pragma once
#include <graaflib/algorithm/coloring/welsh_powell.h>
#include <graaflib/properties/vertex_properties.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

namespace graaf::algorithm {

template <typename GRAPH>
std::unordered_map<vertex_id_t, int> welsh_powell_coloring(const GRAPH& graph) {
    
    using degree_vertex_pair = std::pair<int, vertex_id_t>;

    // Step 1: Sort vertices by degree in descending order
    std::vector<degree_vertex_pair> degree_vertex_pairs;
    for (const auto& [vertex_id, _] : graph.get_vertices()) {
        
        int degree = properties::vertex_degree(graph, vertex_id);
        degree_vertex_pairs.emplace_back(degree, vertex_id);
    
    }

    std::sort(degree_vertex_pairs.rbegin(), degree_vertex_pairs.rend());

    // Step 2: Assign colors to vertices
    std::unordered_map<vertex_id_t, int> color_map;

    for (const auto [_, current_vertex] : degree_vertex_pairs) {

        int color = 0;  // Start with color 0

        // Check colors of adjacent vertices
        for (const auto& neighbor : graph.get_neighbors(current_vertex)) {
            // If neighbor is already colored with this color, increment the color
            if (color_map.contains(neighbor) && color_map[neighbor] == color) {
                    color++;
            }
        }

        // Assign the color to the current vertex
        color_map[current_vertex] = color;
    }

    return color_map;
}

}  // namespace graaf::algorithm
