# DFS Based Cycle Detection

A DFS based cycle detection algorithm is used to identify cycles in graphs, both directed and undirected.
The algorithm can be used to detect cycles in the structure of a graph, as it does not consider edge weights.

# Directed graph

The key idea is that when a vertex is processed, mark it as: UNVISITED, VISITED and NO_CYCLE.
By default all vertices marked as UNVISITED. During the traversal, we label vertices as VISITED. At the exit of the
recursion, we label the vertex as NO CYCLE.
If we met a vertex labeled VISITED, we found a cycle in the graph.

# Undirected graph

The key idea is to store the parent of each vertex during the traversal. So when we check neighboring vertices, we skip
back edge.
During the traversal we mark the vertex as visited and continue the traversal. In case a vertex was visited before and
vertices have different parents, we found a cycle.

The runtime of the algorithm is `O(|V| + |E|)` and memory consumption is `O(|V|)`. Where V is the number of vertices in
the graph and E the number of edges.
The algorithm uses DFS traversal and therefore suffers the same limitations (see depth-first-search.md).

# Use cases

- Resource dependencies:
    - Redundant connections.
    - Deadlocks in concurrent systems.
    - Deadlocks in concurrent systems.
- Logical dependencies:
    - Data base relation.
    - Dependency management.
    - Circuit design.
- Infinity loops.

[wikipedia](https://en.wikipedia.org/wiki/Cycle_(graph_theory)#Cycle_detection)

## Syntax

Cycle detection for directed graph.

```cpp
template <typename V, typename E>
[[nodiscard]] bool dfs_cycle_detection(
    const graph<V, E, graph_type::DIRECTED> &graph);

```

Cycle detection for unidrected graph.

```cpp
template <typename V, typename E>
[[nodiscard]] bool dfs_cycle_detection(
    const graph<V, E, graph_type::UNDIRECTED> &graph);
```

- **graph** The graph to traverse.
- **return** Returns true in case of cycle otherwise returns false.

## Similar algorithms

There are many algorithms for cycle detection or algorithms with specific cycle conditions.
See [wikipedia](https://en.wikipedia.org/wiki/Cycle_(graph_theory)#Graph_classes_defined_by_cycle)
