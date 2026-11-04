# Betweenness Centrality

Betweenness centrality measures how often a vertex lies on a shortest path
between two other vertices. Vertices with high betweenness commonly act as
bridges or bottlenecks in a network.

For a vertex `v`, Brandes' algorithm accumulates its contribution by running a
BFS from every source vertex. During BFS, Graaf records shortest-path counts,
predecessors, and the vertices in decreasing BFS distance.

For each vertex `w` processed in reverse BFS order, the dependency received by
a predecessor `v` is:

```text
sigma[v] / sigma[w] * (1 + dependency[w])
```

## API

```cpp
template <typename V, typename E, graph_type T>
std::unordered_map<vertex_id_t, double> betweenness_centrality(
    const graaf::graph<V, E, T>& graph);
```

The map contains one entry for every live vertex ID. Edge weights are ignored,
because the implementation uses unweighted BFS. In an undirected graph, the
raw value is divided by two to remove the duplicate count produced by traversing
each shortest path in both directions.

## Complexity

The implementation runs one BFS for every vertex. Its time complexity is
`O(V * (V + E))`, and its memory complexity is `O(V + E)`, where `V` is the
number of vertices and `E` is the number of edges.
