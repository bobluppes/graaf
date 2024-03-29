# The benchmarks are based on the google benchmark framework
include(FetchContent)
FetchContent_Declare(
  google_benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.2
)
set(BENCHMARK_ENABLE_TESTING OFF) # Disable building the tests
FetchContent_MakeAvailable(google_benchmark)

# Include fmt as a dependency
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        9.1.0
)
FetchContent_MakeAvailable(fmt)

file(GLOB PERF_SOURCES "graaflib/*.cpp" "graaflib/*/*.cpp")
add_executable(
  ${PROJECT_NAME}_perf
  ${PERF_SOURCES}
)

# Include src such that we can #include <graaflib/*> in the sources
target_include_directories(${PROJECT_NAME}_perf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(
  ${PROJECT_NAME}_perf
  PRIVATE
  benchmark
  fmt::fmt
)