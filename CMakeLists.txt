cmake_minimum_required(VERSION 3.8)

# Project setup
set(PROJECT_NAME cardgame)
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

# Source files and header files
set(SOURCES
    src/Main.cpp
    src/Game.cpp
    src/Presentation.cpp)

set(HEADERS
    src/Game.hpp
    src/Presentation.hpp)

# Organize files in folders for IDEs
source_group("Source" FILES ${SOURCES})
source_group("Source" FILES ${HEADERS})

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
    ${HEADERS})
