# Kahn's Topological Sorting Algorithm

### Overview:
**Kahn's algorithm is used to find a topological order in a directed acyclic graph (DAG). A topological order is a linear ordering of vertices such that for every directed edge (u, v), vertex u comes before v in the order.**

### Implementation Files:

kahn.cpp: Contains the implementation of the Kahn's topological sorting algorithm.
kahn.h: Provides the function declaration and documentation for the algorithm.

### Usage:
```
#include "kahn.h"

// Create a directed graph 'myGraph' (graph type DIRECTED).

std::optional<std::vector<vertex_id_t>> result = kahns_topological_sort(myGraph);

if (result) {
    // 'result' contains the topological order.
} else {
    // The graph contains a cycle.
}
```

### Functions
```
template <typename V, typename E>
std::optional<std::vector<vertex_id_t>> kahns_topological_sort(
    const graph<V, E, graph_type::DIRECTED>& graph
);
```

### Parameters:

 - graph: The input directed graph for which you want to find the topological order.

### Return Value:

- If the graph is acyclic, it returns an optional containing a vector of vertex IDs representing the topological order.
- If the graph contains a cycle, it returns an empty optional (std::nullopt).

### Algorithm Steps:

1. Initialize data structures for in-degrees and a queue.
2. Calculate in-degrees for all vertices in the graph.
3. Enqueue vertices with in-degree 0.
4. Iteratively dequeue vertices with in-degree 0 and update in-degrees.
5. Append dequeued vertices to the topological order.
6. Repeat until the queue is empty.
7. Check if the topological order size matches the number of vertices. If not, the graph contains a cycle.

**Kahn's topological sorting algorithm efficiently finds a valid topological order in a directed acyclic graph or detects the presence of a cycle if one exists.**