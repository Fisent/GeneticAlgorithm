#include "Evolution.h"
#include "FileReader.h"
#include "Random.h"
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

Evolution::Evolution(int pop_size, int gen, float px, float pm, int tour, std::string filename) {
    this->pop_size = pop_size;
    this->gen = gen;
    this->px = px;
    this->pm = pm;
    this->tour = tour;
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

void Evolution::step() {
    //std::sort(population->begin(), population->end(), [this](Result* r1, Result* r2){return problem->costFunction(*r1) < problem->costFunction(*r2);});
    for(int i = 0; i < pop_size * px; i++){
        auto r1 = rankingSelection();
        auto r2 = rankingSelection();
        auto childPair = r1->crossover(r2, px);

        population->at(i) = childPair.first;
        population->at(i+1) = childPair.second;
    }


    std::vector<Result*> *newPopulation = new std::vector<Result*>;
    for(int i = 0; i < pop_size; i++){
        std::vector<Result*> tournament;
        for(int j = 0; j < tour; j++){
            int random_index = random_int(population->size());
            tournament.push_back(population->at(random_index));
            std::sort(tournament.begin(), tournament.end(), [this](Result* r1, Result* r2){return problem->costFunction(*r1) < problem->costFunction(*r2);});
        }
        newPopulation->push_back(tournament[0]);
    }

    //delete population;
    population = newPopulation;

    for(auto animal : *population){
        animal->mutate(pm);
    }
    //mutation
    //crossover
    //tournament
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
    std::vector <Result*> tournament;
    for(int i = 0; i < tour; i++){
        int random_index = random_int(population->size());
        tournament.push_back(population->at(random_index));
    }
    std::sort(tournament.begin(), tournament.end(), [this](Result* r1, Result* r2){return this->problem->costFunction(*r1) < this->problem->costFunction(*r2);});
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
