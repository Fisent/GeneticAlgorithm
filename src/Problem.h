#pragma once
#include <string>
#include "SquareMatrix.h"

class Problem{
private:
    int N;
public:
    Problem(int N, SquareMatrix, SquareMatrix);
    Problem(std::string);
    int getN();
};