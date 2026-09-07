# A* Search Algorithm

A\* computes the shortest path between a starting vertex and a target vertex in weighted and unweighted graphs.
It can be seen as an extension of Dijkstra's classical shortest paths algorithm. The implementation of A\* also tries to
follow `dijkstra_shortest_path` closely where appropriate. Compared to Dijkstra's algorithm, A\* only finds the shortest
path from a start vertex to a target vertex, and not the shortest path to all possible target vertices. Another
difference is that A\* uses a heuristic function to achieve better performance.

At each iteration of its main loop, A\* needs to determine which of its paths to extend. It does so by minimizing the
so-called `f_score`.

In A\*, the `f_score` represents the estimated total cost of the path from the start vertex to the goal vertex through
the current vertex. It's a combination of two components:

1. `g_score`: The actual cost of the path from the start vertex to the current vertex.
2. `h_score` (heuristic score): An estimate of the cost required from the current vertex to the goal vertex.

A\* tries to minimize the `f_score` for each vertex as it explores the graph. The idea is to prioritize exploring
vertices that have lower `f_score` values, as they are expected to lead to potentially better paths.

Mathematically, `f_score` is often defined as:

```
f_score = g_score + h_score
```

Where:

- `g_score` is the cost of the path from the start vertex to the current vertex.
- `h_score` is the heuristic estimate of the cost from the current vertex to the goal vertex.

In the implementation, the heuristic function `heuristic` provides an estimate of `h_score` for each vertex, and the
actual cost of the path from the start vertex to the current vertex is stored in the `g_score` unordered map, as the
algorithm progresses.

In the implementation, `dist_from_start` from path_vertex represents the `f_score` of the path.

The time complexity of A\* depends on the provided heuristic function. In the worst case of an unbounded search space,
the number of nodes expanded is exponential in the depth of the solution (the shortest path) `d`. This can be expressed
as `O(b^d)`, where `b` is the branching factor (the average number of successors per state) per stage.

In weighted graphs, edge weights should be non-negative. Like in the implementation of Dijkstra's algorithm, A\* is
implemented with the priority queue provided by C++, to perform the repeated selection of minimum (estimated) cost nodes
to expand. This is the `open_set`. If the shortest path is not unique, one of the shortest paths is returned.

* [wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm)
* [Red Blob Games](https://www.redblobgames.com/pathfinding/a-star/introduction.html)

## Syntax

calculates the shortest path between on start_vertex and one end_vertex using A\* search.
Works on both weighted as well as unweighted graphs. For unweighted graphs, a unit weight is used for each edge.

```cpp
template <typename V, typename E, graph_type T, typename HEURISTIC_T, typename WEIGHT_T = decltype(get_weight(std::declval<E>()))>
  requires std::is_invocable_r_v<WEIGHT_T, HEURISTIC_T&, vertex_id_t>
std::optional<graph_path<WEIGHT_T>> a_star_search(
    const graph<V, E, T> &graph, vertex_id_t start_vertex, vertex_id_t target_vertex,
    const HEURISTIC_T &heuristic);
```

- **graph** The graph to extract shortest path from.
- **start_vertex** The vertex id where the shortest path should should start.
- **target_vertex** The vertex id where the shortest path should end.
- **heuristic** A heuristic function estimating the cost from a vertex to the target.
- **return**  An optional containing the shortest path (a list of vertices) if found, or std::nullopt if no such path
  exists.