# Architecture Overview
From a very high level, the project is structured in two parts:

1) The graph classes and core data structures
2) Algorithms and additional functionality

The core data structures are designed to store the graph data without being concerned with any business logic.
All additional functionality is built on top of these core classes on a higher abstraction level.

## 1) Graph classes and core data structures
The main class of the library is the `graph` class. This class handles directedness of graphs (undirected vs. directed) 
and weightedness of the edges. Each graph is an instance of the `graph` class:

```c++
enum class graph_type { DIRECTED, UNDIRECTED };

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
class graph {...};
```

The template parameter `GRAPH_TYPE_V` indicates whether the graph is directed or undirected. This cannot be dynamically
changed after construction of the graph. A graph can have arbitrary user provided types for the vertices and edges,
as indicated by the `VERTEX_T` and `EDGE_T` template parameters.

Internally, the graph is stored as an adjacency list. Separate containers hold the values for vertices and edges.

```c++
// N.B. These types are a bit more abstracted in the codebase behind using
// declarations, but for clarity I have left this out.

// Adjacency information is stored in a set for fast existence checks and fast removal
std::unordered_map<vertex_id_t, std::unordered_set<vertex_id_t>> adjacency_list_{};

// Storing vertex and edge values in a separate container has the advantage that
// vertices and edges are only in memory once
std::unordered_map<vertex_id_t, VERTEX_T> vertices_{};
std::unordered_map<edge_id_t, EDGE_T> edges_{};
```

Two *using declarations* are provided to make it easier to instantiate a directed or undirected graph:

```c++
template <typename VERTEX_T, typename EDGE_T>
using directed_graph = graph<VERTEX_T, EDGE_T, graph_type::DIRECTED>;

template <typename VERTEX_T, typename EDGE_T>
using undirected_graph = graph<VERTEX_T, EDGE_T, graph_type::UNDIRECTED>;
```

### Weighted graphs
Certain algorithms (such as A*) operate on weighted graphs. Since the edge type can be any user provided type, we need
to be careful in defining what a weighted graph is. Therefore, we distinguish three:

1) Any graph for which the edge type is derived from the pure virtual class `weighted_edge` is a weighted graph. More
   details on the `weighted_edge` class below. The weight of an edge is given by the `get_weight` function of an edge.
2) Any graph with a primitive numeric type for the edge type (`int`, `float`, `double` etc.) is a weighted graph. The
   weight of an edge is simply given by the numeric value.
3) In all other cases, the graph is unweighted. In contexts where a weighted graph is required, each edge defaults to a 
   unit weight automatically.

The weight of an edge can be queried using the following *overload set* of `get_weight` functions in the `graaf` 
namespace.

*Weighted Edge*
The pure virtual `weighted_edge` class provides an interface for user provided edge classes which should carry a 
weight.

```c++
template <typename WEIGHT_T = int>
class weighted_edge {
 public:
  using weight_t = WEIGHT_T;

  virtual ~weighted_edge() = default;

  [[nodiscard]] virtual WEIGHT_T get_weight() const noexcept = 0;
};
```

## 2) Algorithms and additional functionality
The idea here is to keep the graph classes as general-purpose as possible, and to not include use case specific logic 
(such as dot serialization) as member functions. Therefore, each algorithm/utility function is implemented as a free 
function.

The design goal is to keep the algorithms as general purpose as possible, such that their functionality can be reused
in future algorithms. For example, once we defined BFS/DFS traversal of graphs, search algorithms could be defined
in terms of these traversal algorithms.