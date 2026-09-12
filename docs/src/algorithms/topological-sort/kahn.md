# Kahn's Algorithm

Kahn's algorithm produces a topological ordering of a DAG (directed acyclic graph) by repeatedly emitting vertices that
have no remaining incoming edges.

The algorithm first counts the in-degree of every vertex. Every vertex with an in-degree of zero is a valid starting
point, so all of them are placed in a queue. Vertices are then taken off the queue one at a time and appended to the
result. Taking a vertex conceptually removes its outgoing edges, so the in-degree of each of its neighbors is decreased
by one, and any neighbor whose in-degree drops to zero is pushed onto the queue in turn.

Cycle detection falls out of the algorithm for free. A vertex on a cycle always has an incoming edge from another vertex
on that same cycle, so its in-degree never reaches zero and it is never emitted. If the result does not contain every
vertex of the graph, the graph contains a cycle and no topological ordering exists.

The runtime of the algorithm is `O(|V| + |E|)` and the memory consumption is `O(|V|)`. Where V is the number of vertices
in the graph and E the number of edges. Each vertex enters and leaves the queue exactly once, and each edge is relaxed
exactly once, when its source vertex is emitted.

[wikipedia](https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm)

## Syntax

```cpp
template <typename V, typename E>
[[nodiscard]] std::vector<vertex_id_t> kahn_topological_sort(
    const graph<V, E, graph_type::DIRECTED>& graph);
```

- **graph** The directed graph to traverse.
- **return** Vector of vertices sorted in topological order.
- **throws** `std::invalid_argument` if the graph contains a cycle, mirroring how `bellman_ford_shortest_paths` reports
  a negative cycle.

A graph generally admits more than one valid topological ordering. Which one is returned depends on the order in which
vertices with an in-degree of zero are encountered, so callers should not depend on a particular ordering beyond it
being topologically valid.

## Comparison with the DFS based approach

Graaf also ships a [DFS based topological sort](topological-sort.md). Both produce a valid topological ordering in
`O(|V| + |E|)` time using `O(|V|)` additional memory, and for a graph with several valid orderings the two will
generally return different ones. They differ in a few practical respects.

| | `kahn_topological_sort` | `dfs_topological_sort` |
| --- | --- | --- |
| Traversal | BFS-like, explicit queue | DFS, recursive |
| Cycle detection | Falls out of the algorithm itself | Separate `dfs_cycle_detection` pass up front |
| Graph passes | One | Two (cycle detection, then the sort) |
| Reports a cycle by | Throwing `std::invalid_argument` | Returning `std::nullopt` |
| Return type | `std::vector<vertex_id_t>` | `std::optional<std::vector<vertex_id_t>>` |

Because Kahn's algorithm is iterative, its memory use does not depend on the depth of the graph. The DFS based version
recurses once per vertex along a path, so a graph with a very long path can exhaust the call stack; it inherits that
limitation from the DFS traversal it is built on. Prefer Kahn's algorithm for deep or very large graphs.

Kahn's algorithm also lends itself to *layered* processing. Every vertex sitting in the queue at the start of an
iteration has all of its dependencies satisfied, so a batch drained from the queue in one go forms a dependency
"level" whose vertices can be processed in parallel. This is a natural fit for build systems and job schedulers. The
DFS based version does not expose that structure.

Conversely, the DFS based version returns an `optional` rather than throwing, which fits better in code paths where a
cyclic graph is an expected outcome rather than an error.

## Use cases

- Build systems and package managers, ordering targets so dependencies are built first.
- Job and task schedulers, including parallel schedulers that use the level structure described above.
- Course or curriculum ordering with prerequisites.
- Spreadsheet formula evaluation order.
- Detecting whether a dependency graph has become circular.
