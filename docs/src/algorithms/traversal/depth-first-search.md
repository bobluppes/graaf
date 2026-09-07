# Depth First Search (DFS)

## Depth First Search (DFS) Algorithm

Depth First Search (DFS) is a fundamental graph traversal algorithm used to explore and analyze graphs, whether they are
directed or undirected.
DFS traverses deeper into the graph before backtracking to explore other branches.

The DFS algorithm can be succinctly described using the following steps:

1. Begin by selecting a source node as the starting point of the traversal and push it onto a stack data structure.

2. While the stack is not empty, repeat the following steps:
    * a. Pop a node from the top of the stack.
    * b. Process the popped node, which may involve examining its attributes, marking it as visited, or performing other
      relevant operations.
    * c. Push all unvisited neighbors of the popped node onto the stack.

3. Continue this process until the stack becomes empty, indicating that all reachable nodes have been visited.

The main difference to the BFS is the use of a stack instead of a queue.

### DFS is particularly useful for:

- Topological Sorting:
    - Finds a linear ordering of nodes that respects the partial order imposed by directed edges in a directed acyclic
      graph.

- Pathfinding:
    - Can be used to find paths between nodes, although it may not always find the shortest path.

- Solving Mazes:
    - Navigates through maze-like structures to find a way from a starting point to an end point.

- Detecting Cycles:
    - Helps identify cycles in a graph, which is valuable for various applications.

#### Limitations of DFS:

1. **Completeness:** DFS may not explore all nodes in disconnected graphs unless modifications are made to the
   algorithm.

2. **Infinite Graphs:** DFS can get stuck in an infinite loop if applied to graphs with infinite branches.

3. **Performance on Dense Graphs:** In dense graphs, DFS might explore many nodes before reaching a solution, making it
   less efficient compared to other algorithms.

4. **No Guarantee of Optimality:** Like BFS, DFS may not always find the optimal solution, especially in cases where the
   graph has weighted edges or other complexities.

5. **Memory Usage:** DFS on deep graphs may lead to excessive recursion and memory consumption due to the call stack.

6. **Biased Exploration:** DFS can lead to biased exploration when some branches are deeper than others, potentially
   missing relevant solutions.

### Complexity and Performance:

The DFS algorithm is implemented with a stack and runs in `O(|V| + |E|)` time complexity for connected graphs,
where `|E|` is the number of edges and `|V|` the number of vertices in the graph.

In summary, Depth First Search is a powerful and versatile algorithm for exploring graphs, but its limitations in
handling weighted graphs and negative edge weights should be considered. It provides a straightforward way to explore a
graph layer by layer and is particularly useful for unweighted graph scenarios and connectivity analysis.

[wikipedia](https://en.wikipedia.org/wiki/Depth-first_search)

## Syntax

The dfs_termination_strategy returns true when a certain condition is met, causing to terminate. The dfs_edge_callback
is a function that is used as a callback during the DFS traversal to perform some action whenever an edge is traversed.

```cpp
template <
    typename V, typename E, graph_type T,
    typename EDGE_CALLBACK_T = detail::noop_callback,
    typename SEARCH_TERMINATION_STRATEGY_T = detail::exhaustive_search_strategy>
  requires std::invocable<EDGE_CALLBACK_T &, edge_id_t &> &&
           std::is_invocable_r_v<bool, SEARCH_TERMINATION_STRATEGY_T &,
                                 vertex_id_t>
void depth_first_traverse(
    const graph<V, E, T> &graph, vertex_id_t start_vertex,
    const EDGE_CALLBACK_T &edge_callback,
    const SEARCH_TERMINATION_STRATEGY_T &search_termination_strategy =
        SEARCH_TERMINATION_STRATEGY_T{});
```

### Explanation of Parameters:

- **graph**: The graph to traverse. This parameter represents the graph data structure on which the traversal will be
  performed.
- **start_vertex**: Vertex id where the traversal should be started. This parameter specifies the initial vertex from
  which the traversal begins.
- **edge_callback**: A callback function that is called for each traversed edge. It should be invocable with
  an `edge_id_t` object, representing an edge in the graph.
- **search_termination_strategy**: A unary predicate that indicates whether the traversal should continue or not. The
  traversal continues while this predicate returns `false`. This parameter is optional and defaults to a predefined
  search termination strategy, which traverses the graph exhaustively.
- **return**: The provided code does not explicitly return a value. The traversal is performed by visiting vertices and
  edges in the graph based on the specified parameters.
