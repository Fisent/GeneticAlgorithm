#include "Problem.h"

int Problem::getN() {
    return this->N;
}

Problem::Problem(int N, SquareMatrix, SquareMatrix) {
    this->N = N;
}

Problem::Problem(std::string file_input) {
    std::string str_n = file_input.substr(2,2);
    this->N = std::stoi(str_n);
}