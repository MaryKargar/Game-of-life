cmake_minimum_required(VERSION 3.10)

# Project name
project(GameOfLife)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable with all source files
add_executable(GameOfLife main.cpp Timing.cpp GameOfLife.cpp)

# Find and link OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(GameOfLife PUBLIC OpenMP::OpenMP_CXX)
endif()

# Enable compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(GameOfLife PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Debug configuration
set_target_properties(GameOfLife PROPERTIES DEBUG_POSTFIX "_d")
