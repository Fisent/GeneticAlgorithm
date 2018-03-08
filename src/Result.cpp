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

void Result::mutate(float probability) {
    for(int i = 0; i < this->res.size(); i++){
        if(random_float(1.0) > probability){
            this->mutate(i);
        }
    }
}

void Result::flip(int index){
    int random_index_second = random(N);
    while(index == random_index_second){
        random_index_second = random(N);
    }
    int first = res.at(index);
    int second = res.at(random_index_second);
    res[index] = second;
    res[random_index_second] = first;
}

std::pair<Result&, Result&> Result::crossover(Result& other){
    return std::pair<Result&, Result&>(*this, other);
}

std::string Result::toString() {
    std::string result = "Result [";
    for(auto i : res){
        result += std::to_string(i) + ", ";
    }
    result += "]";
    return result;
}

bool Result::check_unique_values() {
    std::set<int> s;
    for(auto a : this->res){
        s.insert(a);
    }
    return s.size() == res.size();
}

std::vector<int>& repair(std::vector<int>& vector){
    int N = vector.size();
    std::set<int> used_values, remaining_values;
    for(int i = 0; i < N; i++) remaining_values.insert(i);
    for(int i = 0; i < N; i++){
        bool contains = used_values.find(vector.at(i)) != used_values.end();
        if(contains){
            //put radnom value from remaining_values into vector and then remove it from the remaining_values
        }
    }
}
