#include "Result.h"
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
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
        res.push_back(i);
    }
    std::random_shuffle(res.begin(), res.end());
}

void Result::mutate() {
    int random_index = random(N);
    int random_index_second = random(N);
    while(random_index == random_index_second){
        random_index_second = random(N);
    }
    int first = res.at(random_index);
    int second = res.at(random_index_second);
    res[random_index] = second;
    res[random_index_second] = first;
}

Result& Result::crossover(Result& other){
    return other;
}

std::string Result::toString() {
    std::string result = "Result [";
    for(auto i : res){
        result += std::to_string(i) + ", ";
    }
    result += "]";
    return result;
}

std::vector<int>& repair(std::vector<int>& vector){
    int N = vector.size();
    std::set<int> s;
    for(int i = 0; i < N; i++){
        s.insert(i);
    }
    for(int i = 0; i < vector.size(); i++){
        
    }
}
