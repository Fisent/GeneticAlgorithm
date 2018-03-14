#include <string>
#include <vector>
#include <utility>

#pragma once

class Result{
    std::vector<int> res;
public:
    std::vector<int> getVector();
    explicit Result(std::vector<int>);
    explicit Result(int N);
    void mutate(double probability);
    void flip(int index);
    std::pair<Result&, Result&> crossover(Result& other);
    std::vector<int>& repair(std::vector<int>& vector);
    bool check_unique_values();
    std::string toString();
    
private:
    int N;
};
