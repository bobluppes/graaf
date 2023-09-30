---
sidebar_position: 1
---

# Graaf Architecture

From a very high level, the project is structured in two parts:

- The graph classes and core data structures
- Algorithms and additional functionality

## Graph classes and core data structures

The main class of the library is the abstract graph class:

```c++
enum class edge_type { WEIGHTED, UNWEIGHTED };
enum class graph_spec { DIRECTED, UNDIRECTED };

template <typename VERTEX_T, typename EDGE_T, edge_type EDGE_TYPE_V, graph_spec GRAPH_SPEC_V>
class graph {...};
```

An instance of a `graph` can have user provided types for the vertices and edges. Internally, it stores the graph in an
adjacency list, and has separate containers for the vertex and edge instances:

```c++
// N.B. These types are a bit more abstracted in the codebase behind using
// declarations, but for clarity I have left this out.

// Adjacency information is stored in a set for fast existence checks and fast removal
std::unordered_map<vertex_id_t, std::unordered_set<vertex_id_t>> adjacency_list_{};

// Storing these in a separate container has the advantage that
// vertices and edges are only in memory once
std::unordered_map<vertex_id_t, VERTEX_T> vertices_{};
std::unordered_map<std::pair<vertex_id_t, vertex_id_t>, edge_t, edge_id_hash> edges_{};
```

The `graph` class is abstract as it contains pure virtual private methods related to the handling of
edges (`do_has_edge`, `do_get_edge`, `do_add_edge`, and `do_remove_edge`).

### Directed and undirected graphs

There are two classes which publicly derive from `graph`:

- `directed_graph`
- `undirected_graph`

```c++
template <typename VERTEX_T, typename EDGE_T, edge_type EDGE_TYPE_V = edge_type::UNWEIGHTED>
class directed_graph final
    : public graph<VERTEX_T, EDGE_T, EDGE_TYPE_V, graph_spec::DIRECTED> 
    {...};

template <typename VERTEX_T, typename EDGE_T, edge_type EDGE_TYPE_V = edge_type::UNWEIGHTED>
class undirected_graph final
    : public graph<VERTEX_T, EDGE_T, EDGE_TYPE_V, graph_spec::UNDIRECTED> 
    {...};
```

These are the classes which the user instantiates.

They provide implementations for the pure virtual methods related to handling edges. The `unweighted_graph` first sorts
the pair of vertex ids related to an edge before interacting with the internal `edges_` data structure. This ensures
that an edge **a**->**b** is the same as an edge from **b**->**a**.

### Weighted graphs

Certain algorithms (such as A*) operate on weighted graphs. A graph is automatically weighted if a primitive numeric
type is passed as a template parameter to `EDGE_T`. Alternatively, user provided edge classes can publicly derive
from `weighted_edge`.

The `weighted_edge` class provides a default implementation for the `get_weight` method, but this can be overridden in
the derived class:

```c++
template <typename WEIGHT_T = int>
class weighted_edge {
 public:
  using weight_t = WEIGHT_T;
  /**
   * By default an edge has a unit weight.
   */
  [[nodiscard]] virtual WEIGHT_T get_weight() const noexcept { return 1; };
};

```

To create an unweighted graph, simply do not derive from `weighted_edge` in your edge class.

## Algorithms and additional functionality

The idea here is to keep the graph classes as general-purpose as possible, and to not include use case specific logic (
such as dot serialization) as member functions. Therefore, each algorithm/utility function is implemented as a free
function.