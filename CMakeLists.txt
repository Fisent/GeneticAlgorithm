cmake_minimum_required(VERSION 2.6)
project(GeneticAlgorithm)

add_subdirectory(src)
add_subdirectory(ut)
add_executable(run main.cpp)


target_link_libraries(run Result)
