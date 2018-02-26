#include "Result.h"
#include <vector>
#include <iostream>
#include "Random.h"


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
        int r = random(N);
        res.push_back(r);
    }
}

void Result::mutate() {
    int random_index = random(N);
    int random_index_second = random(N);
    while(random_index == random_index_second){
        random_index_second = random(N);
    }
    std::cout << "First index: " << random_index << ", second index: " << random_index_second << std::endl;
    int first = res.at(random_index);
    int second = res.at(random_index_second);
    res[random_index] = second;
    res[random_index_second] = first;
}
