cmake_minimum_required(VERSION 3.1...3.25)

project(
  Graaf
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(example)
add_subdirectory(src)
add_subdirectory(test)