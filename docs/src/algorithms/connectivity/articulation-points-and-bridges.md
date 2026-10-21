# Articulation Points and Bridges

An *articulation point* (or cut vertex) of an undirected graph is a vertex whose removal, together with its incident
edges, increases the number of connected components. A *bridge* (or cut edge) is an edge whose removal increases the
number of connected components. Both mark the single points of failure of a network: if one of them fails, some
vertices can no longer reach each other.

A graph without articulation points is *biconnected*, and a graph without bridges is *2-edge-connected*. In a cycle,
every vertex and every edge can be removed without disconnecting the rest, so it has neither. In a tree it is the
other way around: every edge is a bridge, and every vertex that is not a leaf is an articulation point.

Both are found with a single depth first search. The search assigns every vertex `v` its discovery time `disc(v)`, and a
*low-link* value `low(v)`: the earliest discovery time reachable from the subtree of `v` using at most one edge that is
not part of the search tree. For a tree edge from `u` to its child `v`:

- the edge is a bridge if `low(v) > disc(u)`, since nothing below `v` can reach `u` or above without it;
- `u` is an articulation point if `low(v) >= disc(u)` and `u` is not the root of the search;
- the root of the search is an articulation point if it has two or more children in the search tree.

Self-loops never affect connectivity and are ignored. The search uses an explicit stack, so long paths do not exhaust
the call stack.

The runtime is `O(|V| + |E|)` and the memory consumption is `O(|V|)`, where V is the number of vertices in the graph and
E the number of edges.

[wikipedia](https://en.wikipedia.org/wiki/Biconnected_component)

## Syntax

```cpp
template <typename V, typename E>
[[nodiscard]] std::vector<vertex_id_t> articulation_points(
    const graph<V, E, graph_type::UNDIRECTED>& graph);

template <typename V, typename E>
[[nodiscard]] std::vector<edge_id_t> bridges(
    const graph<V, E, graph_type::UNDIRECTED>& graph);
```

- **graph** The undirected graph to analyse.
- **return** For `articulation_points`, the ids of all articulation points in ascending order. For `bridges`, the ids
  of all bridges in ascending order, each holding the smaller vertex id first. Both are empty if the graph has none,
  including for an empty graph.

Edge weights are ignored.

## Use cases

- Finding single points of failure in computer, power or transport networks.
- Spotting services or packages that a dependency graph cannot route around.
- Splitting a graph into biconnected or 2-edge-connected components.
