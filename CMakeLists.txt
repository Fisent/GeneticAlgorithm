cmake_minimum_required(VERSION 3.10)
project(GeneticAlgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#GTest
add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests ut/test.cpp)
target_link_libraries(runUnitTests gtest gtest_main)
add_test(runUnitTests runUnitTests)

set(SOURCE_FILES src/main.cpp src/Result.cpp)
add_executable(GeneticAlgorithm ${SOURCE_FILES})