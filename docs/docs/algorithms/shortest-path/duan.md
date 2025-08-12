# Duan Shortest Paths (Experimental)

This algorithm computes shortest paths from a source vertex to all other vertices using a multi-phase approach inspired by [Duan et al](https://arxiv.org/pdf/2504.17033). It assumes non-negative edge weights. On unweighted graphs, a unit weight is assumed for each edge.

[wikipedia](https://en.wikipedia.org/wiki/Shortest_path_problem)

## Syntax

Find the shortest paths from a source vertex to all other vertices in the graph using the Duan-style multi-phase algorithm.

```cpp
template <typename V, typename E, graph_type T, typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
[[nodiscard]] std::unordered_map<vertex_id_t, graph_path<WEIGHT_T>>
duan_shortest_paths(const graph<V, E, T>& graph, vertex_id_t source_vertex, int k = 3, double work_factor = 6.0);
```

- **graph** The graph we want to search.
- **source_vertex** The source vertex from which to compute shortest paths.
- **k** Number of Bellman–Ford-style frontier relaxation rounds per outer loop.
- **work_factor** Heap-pop limit multiplier for the bounded multi-source phase.
- **return** A map from target vertex IDs to graph_path containing total weight and the vertex sequence.
