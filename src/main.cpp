#include <iostream>
#include "Result.h"
#include "FileReader.h"
#include "Problem.h"
#include "Evolution.h"
#include <random>
#include <chrono>

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

int main(){
    Evolution e(100, 100, 0.1, 0.1, 5, "had12.dat");
    std::cout << e.get_pop_size() << std::endl;

    Result r1(12);
    Result r2(12);
    std::cout << "r1: ";
    for(auto e : r1.getVector()) std::cout << e << ", ";
    std::cout << std::endl;
    std::cout << "r2: ";
    for(auto e : r2.getVector()) std::cout << e << ", ";
    std::cout << std::endl;
    r1.crossover(r2, 0.5);

    std::cout << "r1: ";
    for(auto e : r1.getVector()) std::cout << e << ", ";
    std::cout << std::endl;
    std::cout << "r2: ";
    for(auto e : r2.getVector()) std::cout << e << ", ";
    std::cout << std::endl;
}
