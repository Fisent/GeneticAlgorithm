#include <iostream>
#include "Result.h"
#include "FileReader.h"
#include "Problem.h"
#include "Evolution.h"
#include <random>
#include <chrono>

#include <fstream>
#include <sstream>

int main(){
    auto rand = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::cout << rand() % 10 << std::endl;
    std::cout << std::rand() % 10 << std::endl;
}
