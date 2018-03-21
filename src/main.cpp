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
#include <thread>

void check_crossover(){
    Result* r1 = new Result(12);
    Result* r2 = new Result(12);
    for(auto element : r1->res) std::cout << element << ", "; std::cout << std::endl;
    for(auto element : r2->res) std::cout << element << ", "; std::cout << std::endl;
    for(int i = 0; i < 100; i++) r1->crossover(r2, 1);
    std::cout << "crossover" << std::endl;
    for(auto element : r1->res) std::cout << element << ", "; std::cout << std::endl;
    for(auto element : r2->res) std::cout << element << ", "; std::cout << std::endl;
}

void run(){

    Evolution e(100, 100, 0.7, 0.01, 5, false, "had12.dat");
    for(int i = 0; i < e.gen; i++){
        e.step();
        std::cout << std::to_string(e.costOfTheBest()) << ", " << std::to_string(e.getAverageCost()) << ", " << std::to_string(e.costOfTheWorst()) << std::endl;
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
    Evolution e(100, 100, 0.7, 0.01, 10, true, "had12.dat");
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
    Evolution e(100, 100, 0.7, 0.01, 10, true, "had12.dat");
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

void run_from_optimum(){
    Evolution e(100, 100, 0.7, 0.01, 5, true, "had12.dat");
    e.population = new std::vector<Result*>;
    for(int i = 0; i < e.pop_size; i++) {
        std::vector<int> v{3 - 1, 10 - 1, 11 - 1, 2 - 1, 12 - 1, 5 - 1, 6 - 1, 7 - 1, 8 - 1, 1 - 1, 4 - 1, 9 - 1};
        Result *res = new Result(v);
        e.population->push_back(res);
    }
    for(int i = 0; i < 100; i ++ ){
        e.step();
        std::cout << e.getAverageCost() << std::endl;
    }
}

void selection_how_many_same_animals_check(){
    Evolution e(100, 100, 0.7, 0.01, 10, true, "had12.dat");
    for(int i = 0; i < 100; i++){
        std::set<Result*> s;
        for(auto element : *e.population){
            s.insert(element);
        }
        std::cout << s.size() << std::endl;
        auto a = e.population;
        bool same = true;
        for(int i = 0; i < a->size() - 1; i++){
            same = (a->at(i)->res == a->at(i+1)->res) && same;
        }
        if(same) std::cout << "i: " << i << "  same! " << e.getAverageCost() << std::endl;
        e.step();
    }
}

void memory_addresses_check(){
    Evolution e(100, 100, 0.7, 0.01, 5, true, "had12.dat");
    for(int i = 0; i < 100; i ++ ){
        e.step();
        std::cout << e.getAverageCost() << std::endl;
        for(auto animal : *e.population){
            std::cout << animal << ", ";
        }
        std::cout << std::endl;
    }
}

void run_print_population(){
    Evolution e(100, 100, 0.7, 0.01, 5, true, "had12.dat");
    for(int i = 0; i < 100; i ++ ){
        e.step();
        std::cout << e.getAverageCost() << std::endl;
        for(auto a : *e.population) std::cout << a->toString() << std::endl;
    }
}

void run_log_all(bool roulette){
    int populations[] {100, 200};
    int generations[] {100};
    float pxs[] {0.7, 0.5, 0.1};
    float pms[] {0.01, 0.1, 0.5};
    int tours[] {5, 10};

    for(auto population : populations){
        for(auto generation : generations){
            for(auto px : pxs){
                for(auto pm : pms){
                    for(auto tour : tours){
                        Evolution e(population, generation, px, pm, tour, not roulette, "had12.dat");
                        e.run(true);
                    }
                }
            }
        }
    }
}

int main(){
    run_log_all(false);
    run_log_all(true);
}
