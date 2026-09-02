cmake_minimum_required(VERSION 3.11...3.25)

project(GraafFetchContentConsumer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    graaf
    SOURCE_DIR ${GRAAF_SOURCE_DIR}
)
set(SKIP_EXAMPLES ON CACHE BOOL "" FORCE)
set(SKIP_TESTS ON CACHE BOOL "" FORCE)
set(SKIP_BENCHMARKS ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(graaf)

add_executable(consumer main.cpp)
target_link_libraries(consumer PRIVATE Graaf::Graaf)

install(TARGETS consumer RUNTIME DESTINATION bin)
