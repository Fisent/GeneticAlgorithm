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
    Evolution e(100, 100, 0.7, 0.01, 5, "had12.dat");

    Result* r1 = new Result(12);
    Result* r2 = new Result(12);
    for(auto element : r1->res) std::cout << element << ", "; std::cout << std::endl;
    for(auto element : r2->res) std::cout << element << ", "; std::cout << std::endl;
    auto pair = r1->crossover(r2, 1);
    for(auto element : pair.first->res) std::cout << element << ", "; std::cout << std::endl;
    for(auto element : pair.first->res) std::cout << element << ", "; std::cout << std::endl;
}
