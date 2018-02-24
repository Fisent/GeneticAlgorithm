#include "FileReader.h"
#include <iostream>

std::string FileReader::read(std::string filename){
    std::string output;
    std::string line;
    std::ifstream myfile;
    myfile.open(filename);
    while(std::getline(myfile, line)){
        output += line;
    }
    myfile.close();
    return output;
}