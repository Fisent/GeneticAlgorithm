#include "Evolution.h"
#include "Result.h"
#include "FileReader.h"
#include <string>

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

}

Evolution::~Evolution() {
    delete population;
    delete problem;
}