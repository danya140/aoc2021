#include "../helpers.h"
#include "PolymerCalculator.h"

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
            if (!containsAll(line, ">"))
            {
                continue;
            }
            inputData.push_back(line);
        }
    }

    return inputData;
}

std::string readTemplate()
{
    std::ifstream file(FILE_NAME);
    std::string inputData;

    if(file.is_open())
    {
        std::string line;
        getline(file, line);
        return line;
    }

    return inputData;
}

int main()
{
    std::vector<std::string> inputNumbers = readNumbers();
    std::string polymerTemplate = readTemplate();

    auto calculator = new PolymerCalculator(inputNumbers, polymerTemplate);
    calculator->simulateGrowth(10);

    std::cout<< "After 10 steps polymer score(count of most common - least common): "<< calculator->polymerScore() << "\n";

    calculator->simulateGrowth(30);

    std::cout<< "After 40 steps polymer score(count of most common - least common): "<< calculator->polymerScore() << "\n";

    return 0;
}
