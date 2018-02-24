#include "gtest/gtest.h"
#include "../src/FileReader.h"

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}