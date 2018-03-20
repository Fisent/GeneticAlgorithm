#pragma once

#include "Result.h"
#include "Problem.h"
#include <vector>

class Evolution{
public:
    Evolution(int pop_size, int gen, float px, float pm, int tour, bool ranking, std::string filename);
    int get_pop_size();
    int get_gen();
    float get_px();
    float get_pm();
    int get_tour();
    Problem* getProblem();
    std::vector<Result*>* getPopulation();
    void step();
    std::vector<int>& getPopulationCosts();
    Result* roulleteSelection();
    Result* rankingSelection();
    double getAverageCost();
    void run(bool print);

    int pop_size;
    int gen;
    float px;
    float pm;
    int tour;
    bool ranking;
    std::vector<Result*>* population;
    Problem* problem;
};