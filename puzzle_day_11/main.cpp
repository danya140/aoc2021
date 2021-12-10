#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <numeric>
#include <cmath>
#include <map>

const char FILE_NAME[] = "input.txt";


std::vector<std::string> readNumbers()
{
    std::ifstream file(FILE_NAME);
    std::vector<std::string> inputData;

    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            inputData.push_back(line);
        }
    }

    return inputData;
}

int main()
{
    std::vector<std::string> inputNumbers = readNumbers();

    return 0;
}
