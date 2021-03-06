//
// Created by fisent on 3/15/18.
//

#include "Random.h"

int random_int(int max){
    auto rand = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    return rand() % max;
}

double random_float(float max){
    float scale=RAND_MAX+1.;
    float base=rand()/scale;
    float fine=rand()/scale;
    return base+fine/scale;
}