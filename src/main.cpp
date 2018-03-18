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
#include <set>

void check_crossover(){
    Result* r1 = new Result(12);
    Result* r2 = new Result(12);
    for(auto element : r1->res) std::cout << element << ", "; std::cout << std::endl;
    for(auto element : r2->res) std::cout << element << ", "; std::cout << std::endl;
    r2 = r1->crossover(r2, 1);
    for(auto element : r1->res) std::cout << element << ", "; std::cout << std::endl;
    for(auto element : r2->res) std::cout << element << ", "; std::cout << std::endl;
}

void run(){
    Evolution e(100, 100, 0.7, 0.01, 5, "had12.dat");
    for(int i = 0; i < 100; i ++ ){
        e.step();
        std::cout << e.getAverageCost() << std::endl;
    }
}

void repair_check(){
    bool result = true;
    for(int i = 0; i < 10000000; i++) {
        Result *r1 = new Result(12);
        Result *r2 = new Result(12);
        r1->crossover(r2, 1.);

        std::set<int> set1, set2;
        for (int i = 0; i < r1->res.size(); i++) {
            set1.insert(r1->res.at(i));
            set2.insert(r2->res.at(i));
        }
        result = result && (set1.size() == set2.size());
    }
    std::cout << result << std::endl;
}

int main(){
    repair_check();
}
