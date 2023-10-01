#pragma once

#include <graaflib/algorithm/coloring/welsh_powell.h>

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

namespace graaf::algorithm {

template <typename GRAPH>
std::unordered_map<vertex_id_t, int> welsh_powell_coloring(const GRAPH& graph) {
    
    using DegreeVertexPair = std::pair<int, vertex_id_t>;

    // Step 1: Sort vertices by degree in descending order
    std::vector<DegreeVertexPair> degree_vertex_pairs;
    for (const auto& vertex : graph.get_vertices()) {
        int degree = graph.get_degree(vertex);
        degree_vertex_pairs.emplace_back(degree, vertex);
    }

    std::sort(degree_vertex_pairs.rbegin(), degree_vertex_pairs.rend());

    // Step 2: Assign colors to vertices
    std::unordered_map<vertex_id_t, int> color_map;

    for (const auto& degree_vertex_pair : degree_vertex_pairs) {
        vertex_id_t current_vertex = degree_vertex_pair.second;
        int color = 1;  // Start with color 1

        // Check colors of adjacent vertices
        for (const auto& neighbor : graph.get_adjacent_vertices(current_vertex)) {
            if (color_map.find(neighbor) != color_map.end()) {
                // If neighbor is already colored with this color, increment the color
                if (color_map[neighbor] == color) {
                    color++;
                }
            }
        }

        // Assign the color to the current vertex
        color_map[current_vertex] = color;
    }

    return color_map;
}

}  // namespace graaf::algorithm
