#include "gtest/gtest.h"
#include <vector>
#include <utility>
#include "../src/FileReader.h"
#include "../src/Problem.h"
#include "../src/Result.h"
#include "../src/SquareMatrix.h"
#include "../src/Evolution.h"

TEST (FileReaderTest, CreationTest){
    FileReader fr();
}

TEST (FileReaderTest, ReadFileTest){
    FileReader fr;
    std::string result = fr.read("had12.dat");
}

TEST (FileReaderTest, ReadFileContentTest){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    ASSERT_NE(result.size(), 0);
}

TEST (FileReaderTest, ReadFileFirstLine){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    ASSERT_EQ(result.substr(2, 2), "12");
}

TEST (FileReaderTest, ParseStringToVector){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    std::vector<int> v = fr.toVector(result);
}

TEST (FileReaderTest, ParseStringToVectorSizeCheck){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    std::vector<int> v = fr.toVector(result);
    ASSERT_NE(v.size(), 0);
    ASSERT_EQ(v.size(), 289);
}

TEST (FileReaderTest, ParseStringToVectorContentCheck){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    std::vector<int> v = fr.toVector(result);
    ASSERT_EQ(12, v[0]);
    ASSERT_EQ(v[1], 0);
    ASSERT_EQ(v[2], 1);
    ASSERT_EQ(v[3], 2);
}

TEST (ProblemTest, ProblemCreationFromFile){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    auto vec = fr.toVector(result);
    Problem newProblem(vec);
}

TEST (ProblemTest, ProblemCreationFromFileProperN){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    auto vec = fr.toVector(result);
    Problem newProblem(vec);
    ASSERT_EQ(newProblem.getN(), 12);
}

TEST (ProblemTest, ProblemCreationFromFileProperMatrixes){
    FileReader fr;
    Problem newProblem(fr.toVector(fr.read("had12.dat")));
    ASSERT_EQ(newProblem.getDistanceMatrix()->get(0,0), 0);
    ASSERT_EQ(newProblem.getDistanceMatrix()->get(11,11), 0);
    ASSERT_EQ(newProblem.getDistanceMatrix()->get(3, 2), 2);
    ASSERT_EQ(newProblem.getDistanceMatrix()->get(4, 1), 2);
    ASSERT_EQ(newProblem.getFlowMatrix()->get(3, 2), 2);
}

TEST (SquareMatrixTest, MatrixCreationWithParameters){
    SquareMatrix m(5, std::vector<int>());
}

TEST (SquareMatrixTest, MatrixGetTest){
    SquareMatrix m(5, std::vector<int>(25,1));
    ASSERT_EQ(m.get(0,0), 1);
}

TEST (SquareMatrixTest, MatrixAdvancedGetTest){
    std::vector<int> matrix{1,1,1,1,1,
                            2,2,2,2,2,
                            3,3,3,3,3,
                            4,4,4,4,4,
                            5,5,5,5,5};
    SquareMatrix sm(5,matrix);
    ASSERT_EQ(sm.get(0,0), 1);
    ASSERT_EQ(sm.get(0,1), 2);
    ASSERT_EQ(sm.get(0,3), 4);
    ASSERT_EQ(sm.get(1,3), 4);
    ASSERT_EQ(sm.get(4,3), 4);
}

TEST (SquareMatrixTest, MatrixMostAdvancedTest){
    std::vector<int> matrix;
    for(int i = 0; i<25; i++){
        matrix.push_back(i);
    }
    SquareMatrix sm(5,matrix);
    ASSERT_EQ(sm.get(0,0), 0);
    ASSERT_EQ(sm.get(4,4), 24);
    ASSERT_EQ(sm.get(3,4), 23);
    ASSERT_EQ(sm.get(3,3), 18);
}

TEST (ResultTest, ResultsCostfunctionReturnsProperValue){
    FileReader fr;
    Problem newProblem(fr.toVector(fr.read("had12.dat")));
    std::vector<int> v{3-1, 10-1, 11-1, 2-1 ,12-1, 5-1, 6-1, 7-1, 8-1, 1-1 ,4-1, 9-1};
    Result res = Result(v);
    int cost = newProblem.costFunction(res);
    ASSERT_EQ(cost, 1652);
}

TEST (EvolutionTest, EvolutionCreateTest){
    Evolution e(100, 100, 0.7, 0.01, 5, "had12.dat");
}

TEST (EvolutionTest, EvolutionHasProperParameteres){
    Evolution e(100, 100, 0.7, 0.01, 5, "had12.dat");
    ASSERT_EQ(e.get_pop_size(), 100);
    ASSERT_EQ(e.get_gen(), 100);
    ASSERT_FLOAT_EQ(e.get_px(), 0.7);
    ASSERT_FLOAT_EQ(e.get_pm(), 0.01);
    ASSERT_FLOAT_EQ(e.get_tour(), 5);
}

TEST (EvolutionTest, EvolutionCreatesPopulation) {
    Evolution e(100, 100, 0.7, 0.01, 5, "had12.dat");
    e.getPopulation();
}

TEST (EvolutionTest, EvolutionCreatesPopulationOfProperSize){
    Evolution e(100, 100, 0.7, 0.01, 5, "had12.dat");
    ASSERT_EQ(e.getPopulation()->size(), 100);
}

TEST(EvolutionTest, EvolutionRunsStepOfEvolution){
    Evolution e(100, 100, 0.7, 0.01, 5, "had12.dat");
    e.step();
}

TEST (EvolutionFunctions, ResultMutation){
    Result r(12);
    r.mutate(0.1);
}

TEST (EvolutionFunctions, ResultMutationChangesVector){
    Result r(12);
    auto first_vector = r.getVector();
    r.mutate(0.1);
    ASSERT_NE(first_vector, r.getVector());
}

TEST (EvolutionFunctions, ResultMutationWorksProperly) {
    std::set<int> set;
    Result r(12);
    for (auto a : r.getVector()){
        set.insert(a);
    }
    ASSERT_EQ(set.size(), 12);
}

//TEST (EvolutionFunctions, CrossoverExists){
//    Result r1(12), r2(12);
//    r1.crossover(r2, 1);
//}

TEST (EvolutionFunctions, CheckUniquenessFunction){
    Result r(12);
    r.check_unique_values();
}


TEST (EvolutionFunctions, CheckUniquenessFunctionWorks){
    Result r1(12);
    ASSERT_TRUE(r1.check_unique_values());
    std::vector<int> v{1,1,1,1,1,2,3};
    Result r2(v);
    ASSERT_FALSE(r2.check_unique_values());

}

TEST (EvolutionFunctions, FlipWorks){
    Result r1(12);
    Result r2 = r1;
    r1.flip(0);
    ASSERT_NE(r1.getVector(), r2.getVector());
}

TEST (EvolutionFunctions, CrossoverWorks){
   Result* r1 = new Result(12);
   Result* r2 = new Result(12);
   for(auto a : r1->res) std::cout << a << ", "; std::cout << std::endl;
   for(auto a : r2->res) std::cout << a << ", "; std::cout << std::endl;
   std::vector<int> v1 = r1->getVector();
   std::vector<int> v2 = r2->getVector();
   auto pair = r1->crossover(r2, 1);
   ASSERT_NE(v1, pair.first->getVector());
   for(auto a : v1) std::cout << a << ", "; std::cout << std::endl;
   for(auto a : v2) std::cout << a << ", "; std::cout << std::endl;
   ASSERT_NE(v2, pair.second->getVector());
}
//
//TEST (EvolutionFunctions, RepairWorks){
//    Result r1(12);
//    Result r2(12);
//    r1.crossover(r2, 1);
//
//    std::set<int> set1, set2;
//    for(int i = 0; i < r1.res.size(); i++){
//        set1.insert(r1.res.at(i));
//        set2.insert(r2.res.at(i));
//    }
//
//    ASSERT_EQ(set1.size(), set2.size());
//    ASSERT_EQ(set1.size(), 12);
//
//}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
