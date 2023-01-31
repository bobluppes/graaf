cmake_minimum_required(VERSION 3.1...3.25)

project(
  Graaf
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)

# Find packages go here.

# You should usually split this into folders, but this is a simple example

# Including header files here helps IDEs but is not required.
file(GLOB SOURCES "src/*/*.cpp" "src/*/*.h" "src/*.cpp" "src/*.h")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_library(GraafLib ${SOURCES})

# Link each target with other targets or add options, etc.

# Adding something we can run
add_executable(Graaf src/main.cpp)

target_link_libraries(Graaf PRIVATE GraafLib)