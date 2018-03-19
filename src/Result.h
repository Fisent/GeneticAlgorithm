#include <string>
#include <vector>
#include <utility>

#pragma once

class Result{
public:
    std::vector<int> res;
    std::vector<int> getVector();
    explicit Result(std::vector<int>);
    explicit Result(int N);
    void mutate(double probability);
    void flip(int index);
    std::pair<Result *, Result *> crossover(Result* other, double probability);
    Result& repair();
    bool check_unique_values();
    std::string toString();
    int findByValue(int);
    
private:
    int N;
};
