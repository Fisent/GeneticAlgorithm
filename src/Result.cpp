#include "Result.h"

Result::Result(std::vector<int> input) {
    this->res = input;
}

std::vector<int> Result::getVector() {
    return res;
}
