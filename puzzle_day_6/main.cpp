#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const char FILE_NAME[] = "input.txt";

std::vector<int> readNumbers()
{
    std::ifstream file(FILE_NAME);

    std::vector<int> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            inputData.push_back(std::stoi(line));
        }
    }

    return inputData;
}

int main()
{
    std::vector<int> inputNumbers = readNumbers();

    return 0;
}
