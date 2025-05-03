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

set(GOOGLE_WEB_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/input_data/web-Google.txt")
set(GOOGLE_WEB_INPUT_URL "https://snap.stanford.edu/data/web-Google.txt.gz")
if(NOT EXISTS "${GOOGLE_WEB_INPUT_FILE}")
  if(NOT EXISTS "${GOOGLE_WEB_INPUT_FILE}.gz")
    file(DOWNLOAD "${GOOGLE_WEB_INPUT_URL}" "${GOOGLE_WEB_INPUT_FILE}.gz" SHOW_PROGRESS)
  endif()
  execute_process(
    COMMAND gzip -dc "${GOOGLE_WEB_INPUT_FILE}.gz"
    OUTPUT_FILE "${GOOGLE_WEB_INPUT_FILE}"
  )
endif()

set(BERKELEY_STANFORD_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/input_data/web-BerkStan.txt")
set(BERKELEY_STANFORD_INPUT_URL "https://snap-sentiment.stanford.edu/data/web-BerkStan.txt.gz")
if(NOT EXISTS "${BERKELEY_STANFORD_INPUT_FILE}")
  if(NOT EXISTS "${BERKELEY_STANFORD_INPUT_FILE}.gz")
    file(DOWNLOAD "${BERKELEY_STANFORD_INPUT_URL}" "${BERKELEY_STANFORD_INPUT_FILE}.gz" SHOW_PROGRESS)
  endif()
  execute_process(
    COMMAND gzip -dc "${BERKELEY_STANFORD_INPUT_FILE}.gz"
    OUTPUT_FILE "${BERKELEY_STANFORD_INPUT_FILE}"
  )
endif()

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

