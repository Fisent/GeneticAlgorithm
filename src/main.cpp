#include <iostream>
#include "src/Result.h"


int main(){
    std::cout << "Hello gtest";
    Result* r = new Result();\
    r->res = 1;
    std::cout << r->func();
    delete r;
}
