# GTEST
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SOURCES "*.cpp" "*/*.cpp")
add_executable(
  ${PROJECT_NAME}_test
  ${TEST_SOURCES}
)
target_include_directories(${PROJECT_NAME}_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(
  ${PROJECT_NAME}_test
  ${PROJECT_NAME}_lib
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)