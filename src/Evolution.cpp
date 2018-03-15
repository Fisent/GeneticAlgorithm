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

    std::vector<Result*>* newPopulation = new std::vector<Result*>();
    for(int i = 0; i < (population->size()/2); i++){
        auto r1 = roulleteSelection();
        auto r2 = roulleteSelection();
        auto childPair = r1->crossover(r2, px);

        newPopulation->push_back(childPair.first);
        newPopulation->push_back(childPair.second);
    }

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

Result *Evolution::roulleteSelection() {
    int sum_of_weights = 0;
    std::sort(population->begin(), population->end(), [this](Result* r1, Result* r2){return problem->costFunction(*r1) < problem->costFunction(*r2);});
    for(auto element : *population) {

        for(auto gene : element->res)std::cout << gene << ", ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for(auto animal : *population){
        sum_of_weights += problem->costFunction(*animal);
    }
    int random = random_int(sum_of_weights);

    for(auto animal : *population){
        int weight = problem->costFunction(*animal);
        if(random < weight){
            std::cout << problem->costFunction(*animal) << ", " << getAverageCost() << std::endl;
            return animal;
        }
        random -= weight;
    }
}

double Evolution::getAverageCost() {
    double result = 0;
    for(auto animal : *population){
        result += problem->costFunction(*animal);
    }
    return result / population->size();
}
