# Welsh Powell Algorithm

Welsh Powell Algorithm computes a coloring of the vertices of a (simple, connected) graph such that no two adjacent
vertices have the same color.

If the graph has different connected components, each component will be treated as a separate simple connected graph.

The algorithm is heuristic and does not guarantee an optimal number of different colors (that is, equal to the chromatic
number of a simple, connected graph).

Colors are represented by the numbers 0, 1, 2,... The Welsh Powell algorithm considers the vertices of the graph in 
descending order of their degrees and assigns each vertex with its first available color, i.e. the color with the 
smallest number that is not already used by one of its neighbors.

The overall worst-case time complexity of the algorithm is `O(n^2)`. In cases where the graph has a fixed degree (a
constant number of neighbors for each vertex), the time complexity can be approximated as `O(n)`. However, if the graph
is highly connected (dense) and approaches a complete graph, the time complexity could approach `O(n^2)`.

If no coloring is possible, an empty `unordered_map` is returned. This is the case when the graph contains no vertices.

[Tutorials Point](https://www.tutorialspoint.com/welsh-powell-graph-colouring-algorithm)

## Syntax

```cpp
template <typename GRAPH>
std::unordered_map<vertex_id_t, int> welsh_powell_coloring(const GRAPH& graph);
```

- **graph** A graph to perform graph coloring on.
- **return** An unordered_map where keys are vertex identifiers and values are their respective colors. If no coloring
  is possible, an empty `unordered_map` is returned.