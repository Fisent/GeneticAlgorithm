#include "SquareMatrix.h"

SquareMatrix::SquareMatrix(int N, std::vector<int> table) {
    this->N = N;
    this->table = table;
}

int SquareMatrix::get(int x, int y) {
    return table.at(y*N + x);
}
