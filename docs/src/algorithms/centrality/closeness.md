# Closeness Centrality

Closeness centrality measures how close a vertex is, on average, to the other
vertices that it can reach. A vertex with small total shortest-path distance
has greater closeness.

For a vertex `v`, the component-local score is:

```text
1 / sum(distance(v, u) for every reachable vertex u != v)
```

Graaf runs BFS from every source vertex and treats every edge as having equal
unit length. Edge weights are ignored.

## Disconnected graphs

Distances are calculated only among vertices in the same reachable component.
A vertex with no reachable vertices other than itself has closeness zero. The
scores are not normalized by the fraction of the graph that is reachable.

## API

```cpp
template <typename V, typename E, graph_type T>
std::unordered_map<vertex_id_t, double> closeness_centrality(
    const graaf::graph<V, E, T>& graph);
```

The map contains one entry for every live vertex ID. In a directed graph,
distances follow outgoing neighbors.

## Complexity

The implementation runs one BFS for every vertex. Its time complexity is
`O(V * (V + E))`, and its memory complexity is `O(V)`, where `V` is the
number of vertices and `E` is the number of edges.
