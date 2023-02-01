# Adding something we can run
add_executable(${PROJECT_NAME}_example main.cpp)
target_include_directories(${PROJECT_NAME}_example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(${PROJECT_NAME}_example PRIVATE ${PROJECT_NAME}_lib)