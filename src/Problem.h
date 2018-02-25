#pragma once
#include <string>
#include "SquareMatrix.h"
#include "Result.h"

class Problem{
private:
    int N;
    SquareMatrix* flowMatrix;
    SquareMatrix* distanceMatrix;
public:
    explicit Problem(std::vector<int> input);
    int getN();
    SquareMatrix* getFlowMatrix();
    SquareMatrix* getDistanceMatrix();
    int costFunction(Result&);
};