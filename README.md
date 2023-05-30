<p align="center"><img src="docs/img/graaf.png"></p>
<h1 align="center">Graaf Lib</h1>

<p align="center">
  Graaf is a general-purpose lightweight C++ library designed for versatile graph operations. Graaf allows users to easily create, modify, and query graphs. It is well-suited for various graph-based applications, including social network analysis, CNNs, and more.
</p>

<p align="center">
  <a href="https://github.com/bobluppes/graaf/actions/workflows/main-ci.yml"><img src="https://github.com/bobluppes/graaf/actions/workflows/main-ci.yml/badge.svg" height="20"></a>
  <a href="https://codecov.io/github/bobluppes/graaf"><img src="https://codecov.io/github/bobluppes/graaf/branch/main/graph/badge.svg?token=ZFBLNFN39C" height="20"></a>
  <a href="https://bobluppes.github.io/graaf/"><img src="https://img.shields.io/badge/documentation-doxygen-%23ff69b4" height="20"></a>
  <a href="LICENSE.md"><img src="https://img.shields.io/badge/license-MIT-black" height="20"></a>
</p>

<p align="center">
  <a href="https://discord.gg/cGczwRHJ9K"><img src="https://img.shields.io/badge/chat-discord-%237289DA?style=flat&logo=discord&labelColor=white" height="20"></a>
</p>

# Features
The Graaf library is designed with generality in mind. As such, it comes with specializations for a `directed_graph` as well as an `undirected_graph`. Furthermore, it can be used to store user-defined vertex and edge classes:

```c++
graaf::undirected_graph<User, Connection> my_graph{};

const auto bob = my_graph.add_vertex(User{
  .name = "Bob",
  .age = 42
});

const auto alice = my_graph.add_vertex(User{
  .name = "Alice",
  .age = 33
});

my_graph.add_edge(bob, alice, Connection{
  .type = connection_type::FRIENDS
});
```

Implementations for common graph algorithms are provided under the `algorithm` namespace. For instance, there is support for traversing a graph using *depth-first search* and *breadth-first search* strategies.

```c++
const auto print_vertex_callback{[](const auto vertex) {
  std::cout << vertex << std::endl;
}};

traverse<search_strategy::BFS>(my_graph, start_vertex, print_vertex_callback);
```

For more examples, take a look at our [example section](./examples/README.md).
More details can be found in our [documentation](https://bobluppes.github.io/graaf/).

# Installation
## Header-Only Library
The Graaf libary can be included as a header-only library. It requires a compiler with C++ 20 support and requires linking against fmt.

### Requirements
- C++ 20
- [fmt/fmtlib](https://github.com/fmtlib/fmt)

Download the `header-only` library from our [release page](https://github.com/bobluppes/graaf/releases) and add the `include/graaflib` directory to your include path. You can now use Graaf in your source files:

```c++
// main.cpp
#include <graaflib/directed_graph>
```

For more details, see the [installation README](include/README.md).

## CMake FetchContent
Alternatively, this project can be pulled in using CMake's `FetchContent`:

```CMake
include(FetchContent)
FetchContent_Declare(
  graaflib
  GIT_REPOSITORY https://github.com/bobluppes/graaf.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(graaflib)
```

Now you can link your target against `Graaf_lib`:

```CMake
target_link_libraries(${PROJECT_NAME} PRIVATE Graaf_lib)
```

# Contributing
The Graaf library welcomes contributions! 

If you're interested in improving, fixing bugs, or adding features, please refer to the [wiki](https://github.com/bobluppes/graaf/wiki) for guidelines. Check out our roadmap on [YouTrack](https://graaf.youtrack.cloud/agiles/147-2/current) to stay up to date on planned features and improvements. We also have an [issue tracker](https://github.com/bobluppes/graaf/issues) for bug reports and feature requests. 

Feel free to join our [Discord](https://discord.gg/cGczwRHJ9K) for assistance and a smooth contribution experience.

# Important Links & Docs
- [Issue tracker](https://github.com/bobluppes/graaf/issues)
- [Roadmap](https://graaf.youtrack.cloud/agiles/147-2/current)
- [Documentation](https://bobluppes.github.io/graaf/)
- [Examples](examples/README.md)
- [Wiki](https://github.com/bobluppes/graaf/wiki)
- [Discord](https://discord.gg/cGczwRHJ9K)

# License
This project is licensed under the [MIT license](LICENSE.md).