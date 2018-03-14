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

    for(auto a : *e.getPopulation()){
        for(auto element : a->res) std::cout << element << ", ";
        std::cout << std::endl;
    }

    std::cout << "costs: " << std::endl;
    auto problem = e.getProblem();
    std::cout << problem->getN();
    for(auto a : *e.getPopulation()){
        problem->costFunction(*a);
    }
//    std::cout << costs->at(0);
//    for(int i = 0; i < costs->size(); i++){
//        std::cout << costs->at(i) << ", ";
//    }
    std::cout << std::endl;


}
