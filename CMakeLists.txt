cmake_minimum_required(VERSION 3.8)

# Project setup
set(PROJECT_NAME cardgame)
set(TESTS_NAME cardgame_test)
project(${PROJECT_NAME})

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Debug/)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Release/)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# Enable folder organization in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(
    ${PROJECT_SOURCE_DIR}/include)

# Source files and header files
set(SOURCES
    src/Game.cpp)

set(HEADERS
    include/cardgame/Game.hpp)

# Organize files in folders for IDEs
source_group("Source" FILES ${SOURCES})
source_group("Headers" FILES ${HEADERS})

source_group("Source" FILES src/Main.cpp)
source_group("Source" FILES tests/GameTest.cpp)

# Platform-specific configurations
if (MSVC)
    message(STATUS "Configuring for MSVC")
    # Set MSVC-specific compiler flags or definitions here if needed
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Configuring for GCC/Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

# Add the executable
add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    src/Main.cpp)

# Enable testing
enable_testing()

# Add test executable
add_executable(
    ${TESTS_NAME}
    ${SOURCES}
    ${HEADERS}
    tests/GameTest.cpp)

