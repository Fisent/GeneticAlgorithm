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
#include <cassert>

void check_crossover(){
    Result* r1 = new Result(12);
    Result* r2 = new Result(12);
    for(auto element : r1->res) std::cout << element << ", "; std::cout << std::endl;
    for(auto element : r2->res) std::cout << element << ", "; std::cout << std::endl;
    for(int i = 0; i < 100; i++) r2 = r1->crossover(r2, 1);
    std::cout << "crossover" << std::endl;
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
        if (i % 1000 == 0) std::cout << i << std::endl;
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

void same_animals_check(){
    Evolution e(100, 100, 0.7, 0.01, 10, "had12.dat");
    for(int i = 0; i < 10; i ++ ){
        e.step();
        auto a = e.population;
        bool same = true;
        for(int i = 0; i < a->size() - 1; i++){
            same = (a->at(i)->res == a->at(i+1)->res) && same;
        }
        if(same) std::cout << "i: " << i << "  same!" << std::endl;
    }
}

void selection_check(){
    Evolution e(100, 100, 0.7, 0.01, 10, "had12.dat");
    for(int i = 0; i < 100; i++){
        std::cout << "average cost: " << e.getAverageCost() << std::endl;
        double average = 0;
        for(int j = 0; j < 100; j++){
            average += e.problem->costFunction(*e.rankingSelection());
        }
        average /= 100;
        assert(average < e.getAverageCost());
        std::cout << "average cost of selected ones: " << average << std::endl;
        e.step();

    }
}

int main(){
    run();
}
