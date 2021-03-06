#include "Problem.h"

int Problem::getN() {
    return this->N;
}


Problem::Problem(std::vector<int> input) {
    N = input[0];
    std::vector<int> flowVector;
    std::vector<int> distanceVector;
    for (int i = 1; i < N*N+1; i++){
        distanceVector.push_back(input.at(i));
    }
    for(int i = N*N + 1; i < input.size(); i++){
        flowVector.push_back(input[i]);
    }
    this->distanceMatrix = new SquareMatrix(N, distanceVector);
    this->flowMatrix = new SquareMatrix(N, flowVector);

}

SquareMatrix *Problem::getFlowMatrix() {
    return this->flowMatrix;
}

SquareMatrix *Problem::getDistanceMatrix() {
    return this->distanceMatrix;
}

int Problem::costFunction(Result &r) {
    int result = 0;
    for(int i = 0; i< N; i++){
        for(int j = 0; j<N; j++){
            int dist = distanceMatrix->get(i,j);
            int flow = flowMatrix->get(r.getVector().at(i), r.getVector().at(j));
            result += dist * flow;
        }
    }
    return result;
}
