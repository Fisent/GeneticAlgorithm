#include "Result.h"
#include <random>
#include <vector>
#include <iostream>
#include <random>


Result::Result(std::vector<int> input) {
    this->res = input;
    this->N = input.size();
}

std::vector<int> Result::getVector() {
    return res;
}

Result::Result(int N) {
    this->N = N;
    this->res = std::vector<int>();
    for(int i = 0; i < N; i++){
        int r = abs(rand() % N);
        res.push_back(r);
    }

}

void Result::mutate() {
    int random_index = std::abs(rand()%N);
    int random_index_second = std::abs(rand()%N);
    while(random_index == random_index_second){
        random_index_second = std::abs(rand()%N);
    }
    std::cout << "First index: " << random_index << ", second index: " << random_index_second << std::endl;
    int first = res.at(random_index);
    int second = res.at(random_index_second);
    res[random_index] = second;
    res[random_index_second] = first;
}
