# Tarjan's Strongly Connected Components

Tarjan's algorithm computes the Strongly Connected Components (SCCs) of a directed graph. An SCC is a subset of vertices
in the graph for which every vertex is reachable from every other vertex in the subset, i.e. there exists a path between
all pairs of vertices for the subset of vertices.

Tarjan's algorithm runs in `O(|V| + |E|)` for directed graphs, where `|V|` the number of vertices and `|E|` is the
number of edges in the graph. So it runs in linear time.

[wikipedia](https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)

## Syntax

```cpp
template <typename V, typename E>
[[nodiscard]] std::vector<std::vector<vertex_id_t>> 
tarjans_strongly_connected_components(const graph<V, E, graph_type::DIRECTED>& graph);
```

- **graph** The graph for which to compute SCCs.
- **return** A vector of vectors representing SCCs.