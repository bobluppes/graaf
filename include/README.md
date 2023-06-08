# Graaf Header-Only Installation
Installing Graaf on your project is easy! Simply copy the `graaflib` directory to your project and add it to your include path. For more details or alternative installation methods, take a look at our [installation guide](https://bobluppes.github.io/graaf/docs/quickstart/installation).

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