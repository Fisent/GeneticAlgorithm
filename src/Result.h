#include <string>
#include <vector>

#pragma once

class Result{
    std::vector<int> res;
public:
    std::vector<int> getVector();
    explicit Result(std::vector<int>);
    explicit Result(int N);
    void mutate();
    Result& crossover(Result& other);
    std::vector<int>& repair(std::vector<int>& vector);
    std::string toString();
    
private:
    int N;
};
