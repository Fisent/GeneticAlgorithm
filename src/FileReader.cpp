#include "FileReader.h"
#include <iostream>
#include <ctype.h>

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

std::vector<int> FileReader::toVector(std::string input) {
    input += "   ";
    std::vector<int> result;
    for(int i = 0; i<input.size(); i++){
        std::string number = "";
        if(std::isdigit(input.at(i))){
            int temp_i = i;
            while(std::isdigit(input.at(temp_i)) && temp_i<input.size()){
                number += input.at(temp_i);
                temp_i++;
            }
            result.push_back(std::stoi(number));
            i = temp_i;
        }
    }
    return result;
}
