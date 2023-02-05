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

# Enables testing in CMAKE
enable_testing()

file(GLOB TEST_SOURCES "graaflib/*.cpp" "graaflib/*/*.cpp")
add_executable(
  ${PROJECT_NAME}_test
  ${TEST_SOURCES}
)

# Include src such that we can #include <graaflib/*> in the sources
target_include_directories(${PROJECT_NAME}_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(
  ${PROJECT_NAME}_test
  ${PROJECT_NAME}_lib
  gtest_main
)

# Enable CMAKE's test runner to discover tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)