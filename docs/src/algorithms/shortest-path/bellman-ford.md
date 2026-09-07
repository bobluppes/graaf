# Bellman-Ford Shortest Path

Bellman-Ford's algorithm computes shortest paths from a single source vertex to all of the other vertices in weighted
graph and unweighted graphs. In weighted graphs, edge weights are allowed to be negative. Bellman-Ford's algorithm runs
in `O(|E||V|)` for connected graphs, where `|E|` is the number of edges and `|V|` the number of vertices in the
graph.

A limitation is that this implementation doesn't check for negative-weight cycles.

[wikipedia](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)

## Syntax

Find the shortest paths from a source vertex to all other vertices using the Bellman-Ford algorithm.

```cpp
template <typename V, typename E, graph_type T, 
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
bellman_ford_shortest_paths(const graph<V, E, T>& graph, vertex_id_t start_vertex);
```

- **graph** The graph to extract shortest path from.
- **start_vertex** The source vertex for the shortest paths.
- **return** A map of target vertex IDs to shortest path structures.
  Each value contains a graph_path object representing the shortest path from the source vertex to the respective
  vertex.
  If a vertex is unreachable from the source, its entry will be absent from the map.