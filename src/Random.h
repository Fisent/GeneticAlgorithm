//
// Created by fisent on 2/26/18.
//

#pragma once

#include <random>
#include <chrono>

int random(int max){
    auto rand = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    return rand() % max;
}
