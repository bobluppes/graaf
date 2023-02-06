include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        9.1.0
)
FetchContent_MakeAvailable(fmt)

# Including header files here helps IDEs but is not required.
file(GLOB SOURCES "*/*.cpp" "*/*.h" "*.cpp" "*.h")

add_library(${PROJECT_NAME}_lib ${SOURCES})

# Include src such that we can #include <graaflib/*> in the sources
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}_lib fmt::fmt)

# Since this is a header only library (.h files), CMAKE cannot automatically determine the link language
set_target_properties(${PROJECT_NAME}_lib PROPERTIES LINKER_LANGUAGE CXX)