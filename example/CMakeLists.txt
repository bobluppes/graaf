file(GLOB EXAMPLES "graaflib/example_*.cpp")

# Set length to -1 because we want to loop over the open ended interval [0, length)
list(LENGTH EXAMPLES NUM_EXAMPLES)
MATH(EXPR NUM_EXAMPLES "${NUM_EXAMPLES}-1")

# Each example is a standalone executable
foreach(INDEX RANGE ${NUM_EXAMPLES})
    set(NAME ${PROJECT_NAME}_example_${INDEX})
    list(GET EXAMPLES ${INDEX} SOURCE)

    add_executable(${NAME} ${SOURCE})

    # Include src such that we can #include <graaflib/*> in the sources
    target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

    target_link_libraries(${NAME} PRIVATE ${PROJECT_NAME}_lib)
endforeach()