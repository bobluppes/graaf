# Breadth First Search (BFS)

## Breadth First Search (BFS) Algorithm

Breadth First Search (BFS) is a fundamental graph traversal algorithm used to explore and analyze graphs, be they
directed or undirected. It operates on the principle of visiting nodes in layers, starting from a given source node and
gradually expanding outward to neighboring nodes at increasing distances. BFS ensures that all nodes at a particular
distance from the source are visited before moving on to nodes at a greater distance. This process continues until all
reachable nodes have been visited, forming a breadth-first exploration of the graph.

The BFS algorithm can be succinctly described using the following steps:

1. Begin by selecting a source node as the starting point of the traversal and enqueue it in a queue data structure.

2. While the queue is not empty, repeat the following steps:
    * a. Dequeue a node from the front of the queue.
    * b. Process the dequeued node, which may involve examining its attributes, marking it as visited, or performing
      other relevant operations.
    * c. Enqueue all unvisited neighbors of the dequeued node into the queue.

3. Continue this process until the queue becomes empty, indicating that all reachable nodes have been visited.

### BFS is particularly useful for:

- P2P - Find neighbor nodes:
    - Finds all neighbors, and then all neighbors of these neighbors.

- Search Engine Crawler:
    - Helps in systematically crawling web pages, exploring links layer by layer.

- Garbage Collection:
    - Identifies and marks reachable objects, propagating to related objects.

- Broadcasting in Networks:
    - Efficiently distributes information across nodes in a network.

- Analyzing the Connectivity of Components:
    - Determines the connected components in a graph.

- Solving Puzzles like the Sliding Tile Puzzle:
    - Explores possible moves in a puzzle in a systematic manner.

#### Limitations of BFS:

1. **Memory Usage:** BFS may consume significant memory resources, especially in graphs with many nodes or when
   searching for paths in deep or complex graphs.

2. **Performance on Dense Graphs:** In dense graphs, where the number of edges is close to the maximum possible, BFS may
   not perform as efficiently as other algorithms designed specifically for dense graphs.

3. **Unweighted Graphs:** BFS doesn't incorporate edge weights, which makes it less suitable for finding shortest paths
   in graphs with weighted edges.

4. **No Negative Weights:** BFS is not suited for graphs with negative edge weights, as it assumes that all edges have a
   non-negative weight. This is because BFS relies on the property that it visits nodes in increasing order of distance
   from the source, and negative weights can lead to unexpected results.

5. **No Guarantee of Optimality:** While BFS can find the shortest path in an unweighted graph, it may not guarantee the
   shortest path in graphs with weighted edges or other more complex scenarios. Dijkstra's algorithm or the Bellman-Ford
   algorithm are better suited for such cases.

### Complexity and Performance:

The BFS algorithm is implemented with a priority queue and runs in `O(|V| + |E|)` time complexity for connected graphs,
where `|E|` is the number of edges and `|V|` the number of vertices in the graph.

In summary, Breadth First Search is a powerful and versatile algorithm for exploring graphs, but its limitations in
handling weighted graphs and negative edge weights should be considered. It provides a straightforward way to explore a
graph layer by layer and is particularly useful for unweighted graph scenarios and connectivity analysis.

[wikipedia](https://en.wikipedia.org/wiki/Breadth-first_search)

## Syntax

The bfs_termination_strategy returns true when a certain condition is met, causing to terminate. The bfs_edge_callback
is a function that is used as a callback during the BFS traversal to perform some action whenever an edge is traversed.

```cpp
template <
    typename V, typename E, graph_type T,
    typename EDGE_CALLBACK_T = detail::noop_callback,
    typename SEARCH_TERMINATION_STRATEGY_T = detail::exhaustive_search_strategy>
  requires std::invocable<EDGE_CALLBACK_T &, edge_id_t &> &&
           std::is_invocable_r_v<bool, SEARCH_TERMINATION_STRATEGY_T &,
                                 vertex_id_t>
void breadth_first_traverse(
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
