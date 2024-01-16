<p align="center"><img src="docs/static/img/graaf.png"></p>
<h1 align="center">Graaf Library</h1>

<p align="center">
  Graaf is a general-purpose header-only graph library implemented in C++. It is designed as a lightweight alternative to the <a href="https://www.boost.org/doc/libs/1_82_0/libs/graph/doc/index.html">Boost Graph Library (BGL)</a>.
</p>

<br/>

<p align="center">
  <a href="https://github.com/bobluppes/graaf/actions/workflows/main-ci.yml"><img src="https://github.com/bobluppes/graaf/actions/workflows/main-ci.yml/badge.svg" height="20"></a>
  <a href="https://codecov.io/github/bobluppes/graaf"><img src="https://codecov.io/github/bobluppes/graaf/branch/main/graph/badge.svg?token=ZFBLNFN39C" height="20"></a>
  <a href="https://bobluppes.github.io/graaf/"><img src="https://img.shields.io/badge/user_docs-docusaurus-%23ff69b4" height="20"></a>
  <a href="https://github.com/bobluppes/graaf/wiki"><img src="https://img.shields.io/badge/contributer_docs-wiki-9cf" height="20"></a>
</p>

<p align="center">
  <a href="https://discord.gg/cGczwRHJ9K"><img src="https://img.shields.io/badge/chat-discord-%237289DA?style=flat&logo=discord&labelColor=white" height="20"></a>
  <a href="https://GitHub.com/bobluppes/graaf/releases/"><img src="https://img.shields.io/github/v/release/bobluppes/graaf?color=%23F7DE3A&include_prereleases"></a>
  <a href="LICENSE.md"><img src="https://img.shields.io/badge/license-MIT-black" height="20"></a>
</p>

<p align="center">

</p>

# About

Graph is an abstract data type that is widely used in computer science. It is a collection of vertices (nodes) and edges
that connect these vertices. Graphs are used to model many real-world problems, such as social networks, road networks,
and computer networks. As such, graph algorithms are used in many applications, including route planning, network
analysis, and data mining.

Graaf: A Lightweight, Header-Only C++20 Graph Library

**Key Features**:

- **Header-only**: No separate compilation or linking required.
- **Generality**: Supports user-defined vertex and edge classes.
- **Algorithm Support**: Provides a range of graph algorithms.

**Purpose**:
Graaf is designed with the goal of simplifying graph-related tasks. It offers a lightweight alternative to the [Boost Graph Library (BGL)](https://www.boost.org/doc/libs/1_82_0/libs/graph/doc/index.html) and is built for simplicity and extensibility. With Graaf, you can easily create, manipulate, and analyze graphs, making it suitable for a wide range of applications.

# Installation

The most straightforward way to use the Graaf in your project is to include it as a header-only library. Please take a
look at the [installation guide](https://bobluppes.github.io/graaf/docs/quickstart/installation) for alternative
installation methods.

## Header-Only Library

The Graaf libary can be included as a header-only library. All it requires is a compiler with **C++ 20 support**.

Download the `header-only` library from our [release page](https://github.com/bobluppes/graaf/releases) and add
the `include/graaflib` directory to your include path. You can now use Graaf in your source files:

```c++
// main.cpp
#include <graaflib/directed_graph>
```

For more details or alternative installation methods, see
the [installation guide](https://bobluppes.github.io/graaf/docs/quickstart/installation).

# How to use Graaf

Using the Graaf library is easy! Specializations are provided for a `directed_graph` as well as for `undirected_graph`.
To create your first graph:

```c++
undirected_graph<int, float> my_graph{};
```

This creates an undirected graph with `integer` values on the vertices and `float` weights on the edges. Graaf is
designed with generality in mind. As such, it can be used to store any user-defined vertex and edge class:

```c++
struct User {
  std::string name;
  int age;
};

// An edge type can also be unweighted if we don't derive from weighted_edge
struct Connection : public weighted_edge<float> {
  float strength;
  float get_weight() const override { return strength; }
};

undirected_graph<User, Connection> my_graph{};
```

Implementations for common [graph algorithms](#algorithms) are provided under the `algorithm` namespace. Combining this
with built-in `dot` format support allows us to do things like visualizing the shortest path between two vertices:

<p align="center">
<img src="docs/static/img/graph_example.png">
</p>

To get started, take a look at our [quickstart guide](https://bobluppes.github.io/graaf/docs/quickstart/intro).

# Algorithms

Algorithms implemented in the Graaf library include the following. For more information on individual algorithms please
take a look at the [docs](https://bobluppes.github.io/graaf/docs/algorithms/intro).

1. [**Cycle Detection Algorithms**](https://bobluppes.github.io/graaf/docs/category/cycle-detection-algorithms):
   - [DFS-Based Cycle Detection](https://bobluppes.github.io/graaf/docs/algorithms/cycle-detection/dfs-based)
2. [**Graph Coloring Algorithms**](https://bobluppes.github.io/graaf/docs/category/graph-coloring-algorithms):
   - [Greedy Graph Coloring](https://bobluppes.github.io/graaf/docs/algorithms/coloring/greedy-graph-coloring)
   - [Welsh-Powell Algorithm]
3. [**Minimum Spanning Tree (MST) Algorithms**](https://bobluppes.github.io/graaf/docs/category/minimum-spanning-tree)
   - [Kruskal's Algorithm](https://bobluppes.github.io/graaf/docs/algorithms/minimum-spanning-tree/kruskal)
   - [Prim's Algorithm](https://bobluppes.github.io/graaf/docs/algorithms/minimum-spanning-tree/prim)
4. [**Shortest Path Algorithms**](https://bobluppes.github.io/graaf/docs/category/shortest-path-algorithms):
   - [A\* search](https://bobluppes.github.io/graaf/docs/algorithms/shortest-path/a-star)
   - [Bellman-Ford Shortest Path](https://bobluppes.github.io/graaf/docs/algorithms/shortest-path/bellman-ford)
   - [BFS-Based Shortest Path](https://bobluppes.github.io/graaf/docs/algorithms/shortest-path/bfs-based-shortest-path)
   - [Dijkstra Shortest Path](https://bobluppes.github.io/graaf/docs/algorithms/shortest-path/dijkstra)
   - [Floyd-Warshall Algorithm](https://bobluppes.github.io/graaf/docs/algorithms/shortest-path/floyd-warshall)
5. [**Strongly Connected Components Algorithms**](https://bobluppes.github.io/graaf/docs/category/strongly-connected-component-algorithms):
   - [Tarjan's Strongly Connected Components](https://bobluppes.github.io/graaf/docs/algorithms/strongly-connected-components/tarjan)
   - [Kosaraju's Strongly Connected Components](https://bobluppes.github.io/graaf/docs/algorithms/strongly-connected-components/kosarajus)
6. [**Topological Sorting Algorithms**](https://bobluppes.github.io/graaf/docs/algorithms/topological-sort):
7. [**Traversal Algorithms**](https://bobluppes.github.io/graaf/docs/category/traversal-algorithms):
   - [Breadth-First Search (BFS)](https://bobluppes.github.io/graaf/docs/algorithms/traversal/breadth-first-search)
   - [Depth-First Search (DFS)](https://bobluppes.github.io/graaf/docs/algorithms/traversal/depth-first-search)
8. [**Clique Detection**](https://bobluppes.github.io/graaf/docs/category/clique-detection)
    - [Bron-Kerbosch](https://bobluppes.github.io/graaf/docs/algorithms/clique-detection/bron-kerbosch)

# Contributing

The Graaf library welcomes contributions 🎊

If you're interested in improving, fixing bugs, or adding features, please refer to
the [wiki](https://github.com/bobluppes/graaf/wiki) for guidelines and have your [development environment set up](https://github.com/bobluppes/graaf/wiki/development-setup) before you start. Check out our roadmap
on [YouTrack](https://graaf.youtrack.cloud/agiles/147-2/current) to stay up to date on planned features and
improvements. We also have an [issue tracker](https://github.com/bobluppes/graaf/issues) for bug reports and feature
requests.

Feel free to join our [Discord](https://discord.gg/cGczwRHJ9K) for assistance and a smooth contribution experience.

### Contributors

<a href="https://github.com/bobluppes/graaf/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=bobluppes/graaf" />
</a>

# Acknowledgements

<p align="left">
  <a href="https://www.jetbrains.com">
    <img src="docs/static/img/jetbrains-logo.svg" width="60" alt="JetBrains Logo">
  </a>
</p>

Special thanks to [JetBrains](https://www.jetbrains.com/community/opensource/) for providing development tools for this
project.

# License

This project is licensed under the [MIT license](LICENSE.md).
