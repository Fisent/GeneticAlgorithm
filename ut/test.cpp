#include "gtest/gtest.h"
#include <vector>
#include "../src/FileReader.h"
#include "../src/Problem.h"
#include "../src/Result.h"
#include "../src/SquareMatrix.h"

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

TEST (ResultTest, ProblemsResultFunctionExsists){
    FileReader fr;
    Problem newProblem(fr.toVector(fr.read("had12.dat")));
    Result r;
    newProblem.costFunction(r);
}

TEST (ResultTest, ResultfunctionReturnsProperValue){
    FileReader fr;
    Problem newProblem(fr.toVector(fr.read("had12.dat")));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}