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
    target_include_directories(${PROJECT_NAME}_${EXAMPLE_NAME}_example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

    target_link_libraries(
        ${PROJECT_NAME}_${EXAMPLE_NAME}_example
        PRIVATE
        ${PROJECT_NAME}_lib
    )
endforeach()