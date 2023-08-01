# Include fmt/fmtlib as a dependency
include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        9.1.0
)
FetchContent_MakeAvailable(fmt)

file(GLOB EXAMPLES "**/main.cpp")

foreach (EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_PATH ${EXAMPLE} DIRECTORY)
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_PATH} NAME)

    # Create one executable per example directory
    add_executable(
        ${PROJECT_NAME}_${EXAMPLE_NAME}_example
        ${EXAMPLE}
    )

    # Include src such that we can #include <graaflib/*> in the sources
    target_include_directories(${PROJECT_NAME}_${EXAMPLE_NAME}_example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    target_link_libraries(
        ${PROJECT_NAME}_${EXAMPLE_NAME}_example
        PRIVATE
        fmt::fmt
    )
endforeach()