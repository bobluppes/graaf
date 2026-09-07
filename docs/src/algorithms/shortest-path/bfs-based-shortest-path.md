# BFS Based Shortest Path

Breadth-First Search (BFS) is a graph traversal algorithm that efficiently finds the shortest
path between two vertices in an **unweighted graph** by exploring vertices level by level,
guaranteeing the shortest path, and has a time complexity of `O(|E| + |V|)`,
where `|V|` is the number of vertices and `|E|` is the number of edges in the graph.
BFS uses a queue to iteratively visit neighboring vertices from the source
vertex, ensuring that the shortest path is discovered before longer paths.

[wikipedia](https://en.wikipedia.org/wiki/Breadth-first_search)

## Syntax

Calculates the shortest path between one start_vertex and one
end_vertex using BFS. This does not consider edge weights.

```cpp
template <typename V, typename E, graph_type T, typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::optional<graph_path<WEIGHT_T>> bfs_shortest_path(
    const graph<V, E, T>& graph, vertex_id_t start_vertex, vertex_id_t end_vertex);
```

- **graph** The graph to extract shortest path from.
- **start_vertex** Vertex id where the shortest path should start.
- **end_vertex** Vertex id where the shortest path should end.
- **return** An optional with the shortest path (list of vertices) if found.