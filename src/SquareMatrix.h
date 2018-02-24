#pragma once
#include <vector>

class SquareMatrix{
private:
    int N;
    std::vector<int> table;
public:
    SquareMatrix(int N, std::vector<int>);
    int get(int x, int y);
};