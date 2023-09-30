---
sidebar_position: 1
---

# Installation

## Graaf Header-Only Installation

Installing Graaf on your project is easy! Simply copy the `graaflib` directory to your project and add it to your
include path.

1. Copy `graaflip` to your project.
2. Before compiling, add the directory to your include path.
    ```bash
    # For C compiler
    export C_INCLUDE_PATH="/full/path/to/include/graaflib/:$C_INCLUDE_PATH"
    # For Cpp compiler
    export CPLUS_INCLUDE_PATH="/full/path/to/include/graaflib/:$CPLUS_INCLUDE_PATH"
    ```

   Or in CMake:
    ```CMake
    include_directories("graaf/src/graaflib")
    ```
3. Include the graaf header in your sources.
    ```c++
    #include <graaflib/directed_graph.h>
    ```

## CMake FetchContent

Alternatively, this project can be pulled in using CMake's `FetchContent`:

```CMake
include(FetchContent)
FetchContent_Declare(
        graaflib
        GIT_REPOSITORY https://github.com/bobluppes/graaf.git
        GIT_TAG main
)
FetchContent_MakeAvailable(graaflib)
```

Now you can link your target against `Graaf_lib`:

```CMake
target_link_libraries(${PROJECT_NAME} PRIVATE Graaf_lib)
```
