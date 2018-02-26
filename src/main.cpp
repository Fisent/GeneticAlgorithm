#include <iostream>
#include "Result.h"
#include "FileReader.h"
#include "Problem.h"

#include <fstream>
#include <sstream>

int main(){
    FileReader fr;
    Problem newProblem(fr.toVector(fr.read("had12.dat")));
    std::vector<int> v{3, 10, 11, 2 ,12, 5, 6, 7, 8, 1 ,4, 9};
    Result res = Result(v);
    std::cout << newProblem.getN();
    int cost = newProblem.costFunction(res);
}
