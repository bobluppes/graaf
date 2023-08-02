---
sidebar_position: 2
---

# Network Example
The undirected_graph implemented in `graaf::undirected_graph`
The shortest path algorithm implemented in `graaf::algorithm::get_shortest_path`
The graph traversal implemented in `graaf::algorithm::graph_traversal`

Using the following graph:

<pre>
<p align="center">
    <img src={require("/static/img/examples/example_usage.png").default}></img>
</p>
</pre>

Custom vertex and edge. In order to use Dijkstra, we should provide the get_weight() function for the edge.

```c++
struct station {
    int id{};
	std::string name{};
    double gaz_capacity{};
};

struct road {
	int length{};
    int get_weight() { return length; }
};
```

# Initializing graph, start and end vertecies
First, we create data structure and initializing graph with vertices and edges

```c++
struct graph_with_start_and_target {
    graaf::undirected_graph<station, road> graph{};
    graaf::vertex_id_t start{};
    graaf::vertex_id_t target{};
};

graph_with_start_and_target create_graph_with_start_and_target() {
...
}
```

## Visualizing graph traversal result
For shortest path, colouring edges with red to indicate the shortest path for both weighted and unweighted graph

Result of unweighted shortest path, chosen edges are coloured red
<pre>
<p align="center">
    <img src={require("/static/img/examples/example_shortest_path_unweighted.png").default}></img>
</p>
</pre>

Result of weighted shortest path, chosen edges are coloured red
<pre>
<p align="center">
    <img src={require("/static/img/examples/example_shortest_path_weighted.png").default}></img>
</p>
</pre>


```c++
void print_shortest_path(const graaf::undirected_graph<station, road>& graph,
                const std::optional<graaf::algorithm::GraphPath<int>>& path, const std::string & filepath) {
...
}

void print_visited_vertices(const graaf::undirected_graph<station, road>& graph,
                            seen_vertices_t& seen,
                            const std::string& filepath) {
...
}
```

Creating a vertex callback structure that will be passed as an argument in the graph traverse function
The function is needed in order to be called inside the traverse function; see graph.tpp file lines 15 and 45 for context.

```c++
using seen_vertices_t = std::unordered_multiset<graaf::vertex_id_t>;
struct record_vertex_callback {
    seen_vertices_t& seen_vertices;

    record_vertex_callback(seen_vertices_t& seen_vertices)
        : seen_vertices{seen_vertices} {}

    void operator()(const graaf::vertex_id_t vertex) const {
        seen_vertices.insert(vertex);
    }
};
```

### Graph example usage
First code block: traversing a weighted graph for the shortest path (Dijkstra) and printing the result to *.dot file.
Second code block: traversing an unweighted graph for the shortest path and printing the result to *.dot file.
The last one is traversing the graph from a given vertex and printing the result to *.dot file.

```c++
 const auto [graph, start, target]{create_graph_with_start_and_target()};

    const auto weighted_shortest_path{graaf::algorithm::get_shortest_path<
            graaf::algorithm::edge_strategy::WEIGHTED, station, road,
            graaf::graph_spec::UNDIRECTED, int>(graph, start, target)};
    print_shortest_path(graph, weighted_shortest_path, "example_weighted_graph.dot");

    const auto unweighted_shortest_path{graaf::algorithm::get_shortest_path<
        graaf::algorithm::edge_strategy::UNWEIGHTED, station, road,
        graaf::graph_spec::UNDIRECTED, int>(graph, start, target)};
    print_shortest_path(graph, unweighted_shortest_path, "example_unwieghted_graph.dot");

    seen_vertices_t seen_vertices{};
    graaf::algorithm::traverse<graaf::algorithm::search_strategy::BFS>(
        graph, start, record_vertex_callback{seen_vertices});
    print_visited_vertices(graph, seen_vertices, "example_traverse_BFS_graph.dot");
```
