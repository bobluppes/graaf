# Dijkstra Shortest Path

Dijkstra's algorithm computes shortest paths between nodes in weighted and unweighted graphs. In weighted graphs,
edge weights should be non-negative. Dijkstra's algorithm is implemented with a priority queue and runs
in `O(|E|log|V|)` for connected graphs, where `|E|` is the number of edges and `|V|` the number of vertices in the
graph.

[wikipedia](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

## Syntax

calculates the shortest path between on start_vertex and one end_vertex using Dijkstra's algorithm. Works on both
weighted as well as unweighted graphs. For unweighted graphs, a unit weight is used for each edge.

```cpp
template <typename V, typename E, graph_type T, typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::optional<graph_path<WEIGHT_T>> 
dijkstra_shortest_path(const graph<V, E, T>& graph, vertex_id_t start_vertex, vertex_id_t end_vertex);
```

- **graph** The graph to extract shortest path from.
- **start_vertex** Vertex id where the shortest path should start.
- **end_vertex** Vertex id where the shortest path should end.
- **return** An optional with the shortest path (list of vertices) if found.

Find the shortest paths from a source vertex to all other vertices in the graph using Dijkstra's algorithm.

```cpp
template <typename V, typename E, graph_type T, typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
[[nodiscard]] std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
dijkstra_shortest_paths(const graph<V, E, T>& graph, vertex_id_t source_vertex);
```

- **graph** The graph we want to search.
- **source_vertex** The source vertex from which to compute shortest paths.
- **return** A map containing the shortest paths from the source vertex to all other vertices. The map keys are target
  vertex IDs, and the values are instances of graph_path, representing the shortest distance and the path (list of
  vertex IDs) from the source to the target. If a vertex is not reachable from the source, its entry will be absent from
  the map.