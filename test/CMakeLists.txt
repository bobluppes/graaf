# The tests are based on the GTEST framework
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES "graaflib/*.cpp" "graaflib/*/*.cpp")
add_executable(
  ${PROJECT_NAME}_test
  ${TEST_SOURCES}
)

if (ENABLE_COVERAGE)
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../cmake-modules)
  include(CodeCoverage)
  append_coverage_compiler_flags_to_target(${PROJECT_NAME}_test)

  setup_target_for_coverage_gcovr_xml(
    NAME ctest_coverage
    EXECUTABLE ctest -j ${PROCESSOR_COUNT}
    DEPENDENCIES ${PROJECT_NAME}_test
    EXCLUDE "test/graaflib/*"
  )
endif()

# Include src such that we can #include <graaflib/*> in the sources
target_include_directories(${PROJECT_NAME}_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(
  ${PROJECT_NAME}_test
  PRIVATE
  ${PROJECT_NAME}_lib
  gtest_main
)

# Enable CMAKE's test runner to discover tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)