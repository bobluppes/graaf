# Installation

## Graaf Header-Only Installation

Installing Graaf on your project is easy! Simply copy the `graaflib` directory to your project and add it to your
include path.

1. Copy `graaflib` to your project.
2. Before compiling, add the directory to your include path.

   ```bash
   # For C compiler
   export C_INCLUDE_PATH="/full/path/to/include/:$C_INCLUDE_PATH"
   # For Cpp compiler
   export CPLUS_INCLUDE_PATH="/full/path/to/include/:$CPLUS_INCLUDE_PATH"
   ```

   Or in CMake:

   ```CMake
   include_directories("graaf/include")
   ```

3. Include the graaf header in your sources.
   ```c++
   #include <graaflib/graph.h>

## CMake FetchContent

Alternatively, this project can be pulled in using CMake's `FetchContent`:

```CMake
include(FetchContent)
FetchContent_Declare(
        graaflib
        GIT_REPOSITORY https://github.com/bobluppes/graaf.git
        GIT_TAG v1.2.0
)
FetchContent_MakeAvailable(graaflib)
```

Pin `GIT_TAG` to a released version rather than `main` - `main` can contain unreleased, potentially breaking changes.

Now you can link your target against `Graaf::Graaf`:

```CMake
target_link_libraries(${PROJECT_NAME} PRIVATE Graaf::Graaf)
```

## CMake Options

There are multiple CMake Options available to choose how you want to build Graaf in your Project.

- `SKIP_TESTS`
  - Default: `OFF`
  - Enabling skips building the tests.
- `SKIP_EXAMPLES`
  - Default: `OFF`
  - This skips building the example usages of the Library.
- `SKIP_BENCHMARKS`
  - Default: `OFF`
  - This skips building the Benchmarks.
- `GRAAF_DOWNLOAD_PERF_DATASETS`
  - Default: `OFF`
  - Some benchmarks run against large real-world graph datasets. Enabling this downloads those datasets so these benchmarks can run; leaving it off still builds them, it just skips downloading the data.

These Options can be set while executing the cmake command
```bash
cmake -DSKIP_TESTS=ON -DSKIP_EXAMPLES=ON -DSKIP_BENCHMARKS=ON [source_directory]
```

or by setting them in your Projects CMakeLists.txt (before `FetchContent_MakeAvailable(graaflib)`)

```cmake
set(SKIP_TESTS ON)
set(SKIP_BENCHMARKS ON)
set(SKIP_EXAMPLES ON)
FetchContent_MakeAvailable(graaflib)
```
