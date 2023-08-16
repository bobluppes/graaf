cmake_minimum_required(VERSION 3.11...3.25)

project(Graaf
  VERSION 0.1.0
  DESCRIPTION "A light-weight C++ graph library."
  LANGUAGES C CXX
)

# This project uses C++ 20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Example usages of the library
option(BUILD_EXAMPLES "Build the examples" OFF)
if(BUILD_EXAMPLES)
add_subdirectory(examples)
endif(BUILD_EXAMPLES)

# Enables testing in CMAKE, needs to be called BEFORE call to add_subdirectory
option(BUILD_TESTS "Built the tests" OFF)
if(BUILD_TESTS)
enable_testing()
add_subdirectory(test)
endif(BUILD_TESTS)

# Benchmarks
option(BUILD_BENCHMARKS "Built the performance benchmarks" OFF)
if(BUILD_BENCHMARKS)
add_subdirectory(perf)
endif(BUILD_BENCHMARKS)

