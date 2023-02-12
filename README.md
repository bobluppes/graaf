![graaf](docs/img/graaf.png)

# Graaf
A light-weight C++ based graph library.

## Requirements
- C++ 20

## Features
The Graaf library provides support for both directed as well as undirected graph structures. Vertices in these graphs can wrap either predefined or user-defined types:

```c++
const auto my_graph = graaf::directed_graph<my_class>::builder()
        .vertices(...)  // Your vertex definitions here
        .edges(...)     // Your edge definitions here
        .build();
```

## Installation
This project supports CMake and can be pulled in using `FetchContent`:

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

## Building locally
You can also build the project yourself:

```bash
# Clone the repository
git clone https://github.com/bobluppes/graaf
mkdir -p graaf/build && cd graaf/build

# Build the project
cmake ..
cmake --build .

# Optionally, run the tests
ctest
```