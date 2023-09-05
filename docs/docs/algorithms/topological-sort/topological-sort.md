---
sidebar_position: 1
---

# Topological sort algorithm
Topological sort algorithm processing DAG(directed acyclic graph) using DFS traversal.
Each vertex is visited only after all its dependencies are visited.
The runtime of the algorithm is `O(|V|+|E|)` and the memory consumption is `O(|V|)`.

[wikipedia](https://en.wikipedia.org/wiki/Topological_sorting)

## Syntax

```cpp
template <typename V, typename E>
[[nodiscard]] std::vector<edge_id_t> kruskal_minimum_spanning_tree(
    const graph<V, E, graph_type::UNDIRECTED>& graph);
```

- **graph** The graph to traverse.
- **return** Vector of vertices sorted in topological order. If the graph contains cycles, it returns an empty vector.