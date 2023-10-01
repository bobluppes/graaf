# Greedy Graph Coloring Algorithm

Greedy Graph Coloring computes a coloring of the vertices of a (simple, connected) graph such that no two adjacent
vertices have the same color.

If the graph has different connected components, each component will be treated as a separate simple connected graph.

The algorithm is heuristic and does not guarantee an optimal number of different colors (that is, equal to the chromatic
number of a simple, connected graph).

Colors are represented by the numbers 0, 1, 2,... The greedy algorithm considers the vertices of the graph in sequence
and assigns each vertex its first available color, i.e. the color with the smallest number that is not already used by
one of its neighbors.

The overall worst-case time complexity of the algorithm is `O(n^2)`. In cases where the graph has a fixed degree (a
constant number of neighbors for each vertex), the time complexity can be approximated as `O(n)`. However, if the graph
is highly connected (dense) and approaches a complete graph, the time complexity could approach `O(n^2)`.

If no coloring is possible, an empty `unordered_map` is returned. This is the case when the graph contains no vertices.

[wikipedia](https://en.wikipedia.org/wiki/Greedy_coloring)

## Syntax

```cpp
template <typename GRAPH>
std::unordered_map<vertex_id_t, int> greedy_graph_coloring(const GRAPH& graph);
    // Step 1: Sort vertices by degree in descending order
    std::vector<DegreeVertexPair> degree_vertex_pairs;
    for (const auto& vertex : graph.get_vertices()) {
        int degree = graph.get_degree(vertex);
        degree_vertex_pairs.emplace_back(degree, vertex);
    }

    std::sort(degree_vertex_pairs.rbegin(), degree_vertex_pairs.rend());

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
```

- **graph** A graph to perform graph coloring on.
- **return** An unordered_map where keys are vertex identifiers and values are their respective colors. If no coloring
  is possible, an empty `unordered_map` is returned.