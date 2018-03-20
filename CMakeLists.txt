cmake_minimum_required(VERSION 3.5)
project(GeneticAlgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_BUILD_TYPE Debug)

add_library(genetics src/Result.cpp src/FileReader.cpp src/Problem.cpp src/SquareMatrix.cpp src/Evolution.cpp src/Random.h src/Random.cpp)


add_executable(GeneticAlgorithm src/main.cpp)
target_link_libraries(GeneticAlgorithm genetics)

#GTest
add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests ut/test.cpp ${})
target_link_libraries(runUnitTests gtest gtest_main genetics)
add_test(ut runUnitTests)