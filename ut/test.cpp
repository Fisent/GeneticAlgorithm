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

TEST (FileReaderTest, ParseStringToVectorContentCheck){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    std::vector<int> v = fr.toVector(result);
    ASSERT_NE(v.size(), 0);
}

TEST (ProblemTest, ProblemCreation){
    SquareMatrix sm(1, std::vector<int>());
    Problem newProblem(1, sm,sm);
}

TEST (ProblemTest, ProblemCreationFromFile){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    Problem newProblem(result);
}

TEST (ProblemTest, ProblemCreationFromFileProperN){
    FileReader fr;
    std::string result = fr.read("had12.dat");
    Problem newProblem(result);
    ASSERT_EQ(newProblem.getN(), 12);
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



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}