cmake_minimum_required(VERSION 3.1...3.25)

project(
  Graaf
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

# Including header files here helps IDEs but is not required.
file(GLOB SOURCES "src/*/*.cpp" "src/*/*.h" "src/*.cpp" "src/*.h")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_library(${PROJECT_NAME}_lib ${SOURCES})

# Link each target with other targets or add options, etc.

# Adding something we can run
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

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

file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(
  ${PROJECT_NAME}_test
  ${TEST_SOURCES}
)
target_link_libraries(
  ${PROJECT_NAME}_test
  ${PROJECT_NAME}_lib
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)