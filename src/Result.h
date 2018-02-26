#include <string>
#include <vector>

#pragma once

class Result{
    std::vector<int> res;
public:
    std::vector<int> getVector();
    Result(std::vector<int>);
};
