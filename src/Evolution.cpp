#include "Evolution.h"
#include "FileReader.h"
#include "Random.h"
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <set>
#include <fstream>
#include <sstream>
#include <iomanip>

Evolution::Evolution(int pop_size, int gen, float px, float pm, int tour, bool ranking, std::string filename) {
    this->pop_size = pop_size;
    this->gen = gen;
    this->px = px;
    this->pm = pm;
    this->tour = tour;
    this->ranking = ranking;
    FileReader fr;
    problem = new Problem(fr.toVector(fr.read(filename)));
    population = new std::vector<Result*>;
    for(int i = 0; i<pop_size; i++){
        Result* res = new Result(problem->getN());
        population->push_back(res);
    }
}

int Evolution::get_pop_size() {
    return pop_size;
}

int Evolution::get_gen() {
    return gen;
}

float Evolution::get_px() {
    return px;
}

float Evolution::get_pm() {
    return pm;
}

int Evolution::get_tour() {
    return tour;
}

std::vector<Result*> *Evolution::getPopulation() {
    return this->population;
}

Problem* Evolution::getProblem() {
    return problem;
}

//TODO fix that all Results has the same address
void Evolution::step() {
    std::vector<Result*> *newPopulation = new std::vector<Result*>;
    for(int i = 0; i < pop_size * px; i+=2) {
        auto r1 = rankingSelection();
        auto r2 = rankingSelection();
        auto pair = r1->crossover(r2, px);
        newPopulation->push_back(pair.first);
        newPopulation->push_back(pair.second);

    }

    for(auto animal : *newPopulation) {
        int random = random_int(population->size());
        animal->crossover(newPopulation->at(random_int(newPopulation->size())), px);
    }

    while(newPopulation->size() < pop_size){
        newPopulation->push_back(this->rankingSelection());
    }

    population = newPopulation;

    for(auto animal : *population){
        animal->mutate(pm);
    }
    //mutation
    //crossover
    //tournament
    assert(pop_size == population->size());
}

Evolution::~Evolution() {
    delete population;
    delete problem;
}

std::vector<int> &Evolution::getPopulationCosts() {
    std::vector<int>* result = new std::vector<int>();
    for(auto animal : *population){
        result->push_back(problem->costFunction(*animal));
    }
    return *result;
}

Result* Evolution::rankingSelection(){
    std::vector<Result*> tournament(tour);
    for(int i = 0; i < tour; i++){
        int random_index = random_int(population->size());
        tournament[i] = population->at(random_index);
    }

    std::sort(std::begin(tournament), std::end(tournament), [this](Result* r1, Result* r2){return this->problem->costFunction(*r1) /*sprawdzony kierunek*/< this->problem->costFunction(*r2);});
    // std::cout << problem->costFunction(*tournament[0]) << std::endl;
    return tournament[0];
}

// Result *Evolution::roulleteSelection() {
//     int sum_of_weights = 0;
//     std::vector<double> probabilities;
//     for(auto element : *population) {
//         // std::cout << problem->costFunction(*element) << ", ";
//         sum_of_weights += problem->costFunction(*element);
//     }
//     for(auto element : *population){
//         probabilities.push_back();
//     }
//     // std::cout << std::endl;
//     for(auto animal : *population){
//         sum_of_weights += problem->costFunction(*animal);
//     }
//     int random = random_int(sum_of_weights);

//     for(auto animal : *population){
//         int weight = problem->costFunction(*animal);
//         if(random < weight){
//             std::cout << problem->costFunction(*animal) << ", " << getAverageCost() << std::endl;
//             return animal;
//         }
//         random -= weight;
//     }
// }

double Evolution::getAverageCost() {
    double result = 0;
    for(auto animal : *population){
        result += problem->costFunction(*animal);
    }
    return result / population->size();
}

void Evolution::run(bool print) {
    try {
        std::ofstream log_file;
        std::ostringstream stream_px;
        stream_px << std::setprecision(2) << px;
        std::ostringstream stream_pm;
        stream_pm << std::setprecision(2) << pm;
        std::string filename = "ps" + std::to_string(pop_size) + "gen" + std::to_string(gen) + "px"
                               + stream_px.str() + "pm" + stream_pm.str() + "tour" + std::to_string(tour)
                               + (ranking ? "ranking" : "roullete") + ".csv";
        log_file.open(filename);
        for (int i = 0; i < gen; i++) {
            step();
            if (print) std::cout << getAverageCost() << std::endl;
            log_file << getAverageCost() << std::endl;
        }
        log_file.close();
    }
    catch(std::exception ex){
        std::cout << ex.what() << std::endl;
    }
}
