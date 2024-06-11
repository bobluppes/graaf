cmake_minimum_required(VERSION 3.11...3.25)

project(Graaf
  VERSION 0.1.0
  DESCRIPTION "A light-weight C++ graph library."
  LANGUAGES C CXX
)

# This project uses C++ 20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(${GRAAF_LIB_TARGET_NAME} ${PROJECT_NAME})

# Example usages of the library
option(SKIP_EXAMPLES "Skip building the examples" OFF)
if(NOT SKIP_EXAMPLES)
add_subdirectory(examples)
endif()

# Enables testing in CMAKE, needs to be called BEFORE call to add_subdirectory
option(SKIP_TESTS "Skip building the tests" OFF)
if(NOT SKIP_TESTS)
enable_testing()
add_subdirectory(test)
endif()

# Benchmarks
option(SKIP_BENCHMARKS "Skip building the performance benchmarks" OFF)
if(NOT SKIP_BENCHMARKS)
add_subdirectory(perf)
endif()

add_library(Graaf INTERFACE)
#add_library(${PROJECT_NAME}::${GRAAF_LIB_TARGET_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(Graaf INTERFACE "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include/")