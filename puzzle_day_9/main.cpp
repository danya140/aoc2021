#include "HeightMap.h"

#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <numeric>
#include <cmath>

const char FILE_NAME[] = "input.txt";


std::vector<std::string> readNumbers()
{
    std::ifstream file(FILE_NAME);

    std::vector<std::string> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            inputData.push_back(line);
        }
    }

    return inputData;
}

void calculateRisk(HeightMap* heightMap)
{
    int risk = 0;
    for (const auto& point : heightMap->findLowestPoints())
    {
        risk += point + 1;
    }

    std::cout << "Sum of risk level: " << risk << "\n";
}

void findBiggestBasins(HeightMap* heightMap)
{
    auto basins = heightMap->mapBasins();
    std::sort(basins.rbegin(), basins.rend());

    int answer = 1;
    for (int i = 0; i < 3; ++i)
    {
        answer *= basins[i];
    }

    std::cout<< "Multiplication of top 3 basins: " << answer;
}

int main()
{
    std::vector<std::string> inputNumbers = readNumbers();

    auto heightMap = new HeightMap(inputNumbers);
    calculateRisk(heightMap);
    findBiggestBasins(heightMap);

    return 0;
}
