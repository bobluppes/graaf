# Articulation Points

An articulation point (or cut vertex) of an undirected graph is a vertex whose removal, along with all its incident
edges, increases the number of connected components of the graph. In other words, it is a single point of failure for
the connectivity of the graph.

Articulation points are commonly used in network reliability analysis, infrastructure planning, and dependency-graph
analysis, where identifying single points of failure is important.

The algorithm runs in `O(|V| + |E|)` for undirected graphs, where `|V|` is the number of vertices and `|E|` is the
number of edges in the graph. So it runs in linear time.

[wikipedia](https://en.wikipedia.org/wiki/Biconnected_component)

## Syntax

```cpp
template <typename V, typename E>
articulation_points_t articulation_points(const graph<V, E, graph_type::UNDIRECTED>& graph);
```

- **graph** The undirected graph to analyse.
- **return** A list of vertex IDs that are articulation points.