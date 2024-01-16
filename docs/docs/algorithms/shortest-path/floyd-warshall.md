# Floyd-Warshall algorithm

Floyd-Warshall algorithm computes the shortest path between any two vertices in a graph, both directed and undirected.
The algorithm does not work for graphs with negative weight cycles.
The key idea of the algorithm is to relax the weighted shortest path between any two vertices, using any vertex as an
intermediate one.
Advantage of the algorithm is that it processes vertices instead of edges. This advantage can be used when the number of
edges is large enough, aka a dense graph.
Runtime of the algorithm is O(|V<sup>3</sup>|) and memory consumption is O(|V<sup>2</sup>|).

[wikipedia](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)

## Syntax

Calculates the shortest path between any two vertices.

```cpp
template <typename V, typename E, graph_type T,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
std::vector<std::vector<WEIGHT_T>> floyd_warshall_shortest_paths(
    const graph<V, E, T>& graph);
```

- **graph** The graph to extract the shortest path from.
- **return** Returns a 2D vector of the shortest path. If a path doesn't exist between two vertices, mark it as
  TYPE_MAX.