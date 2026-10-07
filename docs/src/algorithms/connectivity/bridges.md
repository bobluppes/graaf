# Bridges

A bridge (or cut edge) of an undirected graph is an edge whose removal increases the number of connected components of the graph. In other words, it is a single point of failure for the connectivity of the graph.

Bridges are commonly used in network reliability analysis and infrastructure planning, where identifying critical links is important.

The algorithm runs in `O(|V| + |E|)` for undirected graphs, where `|V|` is the number of vertices and `|E|` is the number of edges in the graph. So it runs in linear time.

[wikipedia](https://en.wikipedia.org/wiki/Bridge_(graph_theory))

## Syntax

```cpp
template <typename V, typename E>
bridges_t bridges(const graph<V, E, graph_type::UNDIRECTED>& graph);
```

- **graph** The undirected graph to analyse.
- **return** A list of edges that are bridges.