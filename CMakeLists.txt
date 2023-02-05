cmake_minimum_required(VERSION 3.11...3.25)

project(Graaf
  VERSION 0.1.0
  DESCRIPTION "A light-weight C++ graph library."
  LANGUAGES CXX
)

# This project uses C++ 20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Shows example usages of the library
add_subdirectory(example)

# The graph library itself
add_subdirectory(src)

# Enables testing in CMAKE, needs to be called BEFORE call to add_subdirectory
enable_testing()
add_subdirectory(test)