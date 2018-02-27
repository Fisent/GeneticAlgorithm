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
    Result r(12);
    std::cout << r.toString();
    Result r2(12);
    std::cout << r2.toString();
}
