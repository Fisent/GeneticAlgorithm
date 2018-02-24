#include <fstream>
#include <string>
#include <vector>

#pragma once

class FileReader{
public:
    std::string read(std::string);
    std::vector<int> toVector(std::string);
};