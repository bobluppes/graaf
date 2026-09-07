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

# A few benchmarks (Kruskal/Prim MST) run against large real-world graph
# datasets that are downloaded from the web. This is off by default so that
# configuring Graaf - whether standalone, in CI, or as a FetchContent
# dependency of another project - never silently hits the network. Enable
# this locally to actually download the datasets and run those benchmarks.
option(GRAAF_DOWNLOAD_PERF_DATASETS
  "Download large real-world graph datasets used by some perf benchmarks"
  OFF)

# Datasets are cached here, outside of the build directory, so that they
# survive a clean rebuild instead of being re-downloaded every time.
# PROJECT_SOURCE_DIR (Graaf's own root), not CMAKE_SOURCE_DIR, so that this
# still resolves correctly when Graaf is pulled in as a FetchContent
# dependency of another project (where CMAKE_SOURCE_DIR would point at the
# consumer's root instead).
set(GRAAF_PERF_DATASET_DIR "${PROJECT_SOURCE_DIR}/.cache/perf_datasets")

# Filenames are declared once here and used both to download the datasets
# below and, via the generated dataset_dir.h, to open them in
# dataset_reader.cpp - so the two can never drift out of sync.
set(GRAAF_WEB_GOOGLE_FILENAME web-Google.txt)
set(GRAAF_WEB_BERK_STAN_FILENAME web-BerkStan.txt)

# Downloads and extracts a gzip-compressed dataset into GRAAF_PERF_DATASET_DIR,
# unless it is already present there from a previous configure. The download
# is written to a temporary name and only renamed into place on success, so a
# failed or interrupted download can never be mistaken for a valid cache entry.
function(graaf_download_dataset filename url)
  set(extracted "${GRAAF_PERF_DATASET_DIR}/${filename}")
  if(NOT EXISTS "${extracted}")
    set(archive "${extracted}.gz")
    if(NOT EXISTS "${archive}")
      set(archive_partial "${archive}.partial")
      file(DOWNLOAD "${url}" "${archive_partial}" SHOW_PROGRESS STATUS download_status)
      list(GET download_status 0 download_status_code)
      if(NOT download_status_code EQUAL 0)
        list(GET download_status 1 download_status_message)
        file(REMOVE "${archive_partial}")
        message(FATAL_ERROR "Failed to download dataset '${filename}' from ${url}: ${download_status_message}")
      endif()
      file(RENAME "${archive_partial}" "${archive}")
    endif()
    execute_process(
      COMMAND "${GRAAF_GZIP_EXECUTABLE}" -dc "${archive}"
      OUTPUT_FILE "${extracted}"
      RESULT_VARIABLE gzip_result
    )
    if(NOT gzip_result EQUAL 0)
      file(REMOVE "${extracted}")
      message(FATAL_ERROR "Failed to extract dataset '${filename}' ('gzip' exited with ${gzip_result})")
    endif()
  endif()
endfunction()

if(GRAAF_DOWNLOAD_PERF_DATASETS)
  find_program(GRAAF_GZIP_EXECUTABLE gzip)
  if(NOT GRAAF_GZIP_EXECUTABLE)
    message(FATAL_ERROR "GRAAF_DOWNLOAD_PERF_DATASETS is ON but 'gzip' was not found on PATH; it is required to extract the perf benchmark datasets.")
  endif()

  file(MAKE_DIRECTORY "${GRAAF_PERF_DATASET_DIR}")

  graaf_download_dataset(${GRAAF_WEB_GOOGLE_FILENAME} https://snap.stanford.edu/data/web-Google.txt.gz)
  graaf_download_dataset(${GRAAF_WEB_BERK_STAN_FILENAME} https://snap-sentiment.stanford.edu/data/web-BerkStan.txt.gz)
endif()

# Generated unconditionally so the dataset-backed benchmarks always compile,
# even when GRAAF_DOWNLOAD_PERF_DATASETS is off (they just can't be run).
configure_file(
  graaflib/utils/dataset_dir.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/generated/graaflib/utils/dataset_dir.h
  @ONLY
)

file(GLOB PERF_SOURCES "graaflib/*.cpp" "graaflib/*/*.cpp")
add_executable(
  ${PROJECT_NAME}_perf
  ${PERF_SOURCES}
)

# Include src such that we can #include <graaflib/*> in the sources
target_include_directories(${PROJECT_NAME}_perf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Include the generated dataset_dir.h
target_include_directories(${PROJECT_NAME}_perf PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)

target_link_libraries(
  ${PROJECT_NAME}_perf
  PRIVATE
  benchmark
  fmt::fmt
)
