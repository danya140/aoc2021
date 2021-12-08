#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

const char FILE_NAME[] = "input_example.txt";


std::vector<int> readNumbers()
{
    std::ifstream file(FILE_NAME);

    std::vector<int> inputData;

    if(file.is_open())
    {
        std::string line;
        std::getline(file, line);
        for (const auto& number : split(line, ','))
        {
            inputData.push_back(std::stoi(number));
        }
    }

    return inputData;
}

int main()
{
    std::vector<int> inputNumbers = readNumbers();

    return 0;
}
