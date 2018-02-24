#include <iostream>
#include "Result.h"

#include <fstream>
#include <sstream>

int main(){
    std::ifstream myfile;
    myfile.open("had12.dat");
    std::string line;
    std::string output = "";
    while(std::getline(myfile, line)){
        output += line;
    }
    myfile.close();
    std::cout << "end" << std::endl;
    std::cout << output.size();

    for(int i = 0; i<output.size(); i++){
        std::cout << output.at(i) << std::endl;
    }
}
