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
    std::cout << e.get_pop_size();
    e.step();
}
