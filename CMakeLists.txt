cmake_minimum_required(VERSION 3.10)
project(MyDatabaseProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Add source files
add_executable(MyDatabaseProject main.cpp)

# Add Google Test
include(GoogleTest)
find_package(GTest REQUIRED)

# Add test executable
add_executable(MyDatabaseProjectTests table_tests.cpp)
target_link_libraries(MyDatabaseProjectTests GTest::gtest_main)

# Enable testing
enable_testing()
gtest_discover_tests(MyDatabaseProjectTests)