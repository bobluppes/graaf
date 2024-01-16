# Dot Serialization Example

The `to_dot` function as defined under `graaf::io` can be used to searialize graphs to
the [dot format](https://graphviz.org/doc/info/lang.html). This can be handy for debugging purposes, as well as for
post-processing of your graphs in another tool which supports the format.

## Numeric primitive types

Default vertex and edge writers are provided such that you can serialize graphs with numeric primitive vertices and
edges. For instance:

```c++
graaf::undirected_graph<int, float> my_graph{};

// ...

graaf::io::to_dot(my_graph, path):
```

## User defined types

For user defined vertex and edge types, it is necessary to provide your own vertex and edge writers. These writers
should take a vertex or edge as a parameter and serialize it to a string. This resulting string is used in the
dot [attribute list](https://graphviz.org/doc/info/attrs.html) of the respective vertex or edge.

For example, consider the following user defined vertex and edge types:

```c++
struct my_vertex {
  int number{};
  std::string name{};
};

enum class edge_priority { LOW, HIGH };

struct my_edge {
  edge_priority priority{edge_priority::LOW};
  float weight{};
};
```

We define two lambdas to serialize these vertices and edges. Here we can use any of
the [graphviz attributes](https://graphviz.org/doc/info/attrs.html). In this example, we
use [fmtlib](https://github.com/fmtlib/fmt) to format our strings.

**Vertex writer**

```c++
const auto vertex_writer{[](graaf::vertex_id_t vertex_id,
                              const my_vertex& vertex) -> std::string {
  const auto color{vertex.number <= 25 ? "lightcyan" : "mediumspringgreen"};
  return fmt::format("label=\"{}: {}\", fillcolor={}, style=filled", vertex_id, vertex.name, color);
}};
```

**Edge writer**

```c++
const auto edge_writer{[](const graaf::vertex_ids_t& /*edge_id*/,
                            const my_edge& edge) -> std::string {
  const auto style{edge.priority == edge_priority::HIGH ? "solid" : "dashed"};
  return fmt::format("label=\"{}\", style={}, color=gray, fontcolor=gray", edge.weight, style);
}};
```

Now let's create a directed graph and serialize it to dot:

```c++
graaf::directed_graph<my_vertex, my_edge> graph{};

const auto vertex_1{graph.add_vertex({10, "some data"})};
const auto vertex_2{graph.add_vertex({20, "some more data"})};
// ...

graph.add_edge(vertex_1, vertex_2, {edge_priority::HIGH, 3.3});
// ...

const std::filesystem::path dof_file_path{"./my_graph.dot"};
graaf::io::to_dot(my_graph, dof_file_path, vertex_writer, edge_writer);
```

The contents of `my_graph.dot` can be processed in any tool which supports dot format. For example, you can use
the `dot` command line tool to generate png images:

```bash
dot -Tpng ./my_graph.dot -o my_graph.png
```

Alternatively, you can
use [graphviz online](https://dreampuf.github.io/GraphvizOnline/#digraph%20G%20%7B%0A%0A%20%20subgraph%20cluster_0%20%7B%0A%20%20%20%20style%3Dfilled%3B%0A%20%20%20%20color%3Dlightgrey%3B%0A%20%20%20%20node%20%5Bstyle%3Dfilled%2Ccolor%3Dwhite%5D%3B%0A%20%20%20%20a0%20-%3E%20a1%20-%3E%20a2%20-%3E%20a3%3B%0A%20%20%20%20label%20%3D%20%22process%20%231%22%3B%0A%20%20%7D%0A%0A%20%20subgraph%20cluster_1%20%7B%0A%20%20%20%20node%20%5Bstyle%3Dfilled%5D%3B%0A%20%20%20%20b0%20-%3E%20b1%20-%3E%20b2%20-%3E%20b3%3B%0A%20%20%20%20label%20%3D%20%22process%20%232%22%3B%0A%20%20%20%20color%3Dblue%0A%20%20%7D%0A%20%20start%20-%3E%20a0%3B%0A%20%20start%20-%3E%20b0%3B%0A%20%20a1%20-%3E%20b3%3B%0A%20%20b2%20-%3E%20a3%3B%0A%20%20a3%20-%3E%20a0%3B%0A%20%20a3%20-%3E%20end%3B%0A%20%20b3%20-%3E%20end%3B%0A%0A%20%20start%20%5Bshape%3DMdiamond%5D%3B%0A%20%20end%20%5Bshape%3DMsquare%5D%3B%0A%7D)
for easy visualization:

<pre>
<p align="center">
  <img src={require("/static/img/examples/dot-serialization-graph.png").default}></img>
</p>
</pre>