cmake_minimum_required(VERSION 3.15)

project(Student_App VERSION 1.0 LANGUAGES CXX)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Main executable
add_executable(Student_App ${SOURCES})
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp") 

# Google Test Setup
add_subdirectory(${CMAKE_SOURCE_DIR}/googletest)

# Test executable
file(GLOB TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp") # Use the 'tests' folder
add_executable(UnitTests ${TEST_SOURCES} ${SOURCES})      # Add both test sources and main sources

# Add include directories for UnitTests
target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link Google Test to UnitTests
target_link_libraries(UnitTests gtest gtest_main)

# Enable testing and discover tests
include(GoogleTest)
enable_testing()
gtest_discover_tests(UnitTests)
