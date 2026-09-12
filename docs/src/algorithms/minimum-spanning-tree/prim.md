# Prim's Algorithm

Prim's algorithm computes the minimum spanning tree (MST) of a connected, undirected graph with weighted edges. Starting
with an arbitrary vertex, the algorithm iteratively selects the edge with the smallest weight that connects a
vertex in the tree to a vertex outside the tree, adding it to the MST.

The algorithm's worst-case time complexity is O(∣E∣log∣V∣).

Unlike Kruskal's algorithm, Prim's algorithm works efficiently on dense graphs. A limitation is that it requires the
graph to be connected and does not handle disconnected graphs or graphs with negative-weight cycles.

Prim's MST is often used in network design, such as electrical wiring and telecommunications.

[wikipedia](https://en.wikipedia.org/wiki/Prim%27s_algorithm)

## Syntax

```cpp
template <typename V, typename E,
          typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
[[nodiscard]] std::optional<tree<vertex_id_t, WEIGHT_T>>
prim_minimum_spanning_tree(const graph<V, E, graph_type::UNDIRECTED>& graph,
                           vertex_id_t start_vertex);
```

- **graph** The undirected graph for which we want to compute the MST.
- **start_vertex** The vertex ID which should be the root of the MST.
- **return** Returns a `tree` rooted at `start_vertex`, where each edge value is the weight of the corresponding edge
  in the graph, if the graph is connected, otherwise returns an empty optional.