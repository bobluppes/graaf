---
sidebar_position: 3
---

# Edmonds-Karp Algorithm

The Edmonds-Karp algorithm computes the maximum flow in a flow network.
The Edmonds-Karp algorithm re-uses the existing `breadth_first_traverse` method for finding the shortest path that has available capacity. It runs in `O(|V||E|^2)` time, where `|V|` the number of vertices in the graph and `|E|` is the number of edges.

[wikipedia](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm)

## Syntax

```cpp
template <typename V, typename E, typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
[[nodiscard]] WEIGHT_T edmonds_karp_max_flow(
    const graph<V, E, graph_type::DIRECTED>& graph,
    vertex_id_t source, vertex_id_t sink);
```

- **graph** The flow network graph.
- **source** Vertex id where the flow network graph starts.
- **sink** Vertex id where the flow network graph ends.
- **return** The maximum flow value of the flow network graph.