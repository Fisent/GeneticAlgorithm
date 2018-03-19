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

void Result::mutate(double probability) {
    for(int i = 0; i < N; i++){
        double rand = random_float(1.0);
        if (rand /*sprawdzone*/< probability) {
            this->flip(i);
        }
    }
}

void Result::flip(int index){
    int random_index_second = random_int(N);
    while(index == random_index_second){
        random_index_second = random_int(N);
    }
    int first = res.at(index);
    int second = res.at(random_index_second);
    res[index] = second;
    res[random_index_second] = first;
}

//TODO: debug crossover
std::pair<Result*, Result*> Result::crossover(Result* other, double probability){
    float rand = random_float(1.0);
    if(rand /*sprawdzone*/< probability){
        std::vector<int>res1;
        std::vector<int>res2;

        int position = random_int(N);
        for(int i = 0; i < position; i++){
            res1.push_back(this->res.at(i));
            res2.push_back(other->res.at(i));
        }
        for(int i = position; i < N; i++){
            res2.push_back(this->res[i]);
            res1.push_back(other->res[i]);
        }
        Result* r1 = new Result(res1);
        Result* r2 = new Result(res2);
        r1->repair();
        r2->repair();
        return std::make_pair(r1, r2);
    }
    return std::make_pair(this, other);
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

int Result::findByValue(int value) {
    for (int i = 0; i < N; i++) {
        if (res[i] == (int) value)
            return i;
    }
    return -1;
}

Result& Result::repair(){
    for(int i = 0; i < N; i++) {
        for(int j = N; j > 0; j--){
            int number = -2;
            for(int k = 0; k < N; k++){
                if(findByValue(k) == -1) number = k;
            }
            if(findByValue(i) == findByValue(j) && number != -2)
                res[j] = number;
        }
    }
}
