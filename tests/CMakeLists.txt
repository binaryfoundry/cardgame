cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME cardgame_test)
project(${PROJECT_NAME})

# Add test executable
add_executable(
    ${PROJECT_NAME}
    GameTest.cpp)

# Link the test executable with the library
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME})
