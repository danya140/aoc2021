#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <numeric>
#include <cmath>

const char FILE_NAME[] = "input.txt";


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

/**
 * Part 1
 */
void findFuelCost(const std::vector<int>& input)
{
    double medianValue = median(input);

    double totalFuelCost = 0;
    for (const auto& coordinate : input)
    {
        totalFuelCost += std::abs(medianValue - coordinate);
    }

    std::cout<<"Optimal total fuel cost: " << totalFuelCost << "\n";
}

int calculateFuelCost(int coordinate, int destination)
{
    int fuelCost = 0;
    for (int i = 1; i <= std::abs(coordinate - destination); ++i)
    {
        fuelCost += i;
    }

    return fuelCost;
}

/**
 * Brute force solve of part 2
 */
void findFuelCostOptimal(const std::vector<int>& input)
{
    double medianValue = median(input);
    int medianHalf = medianValue/2;

    long long int lowestCost = UINT32_MAX;
    for (int i = medianValue - medianHalf ; i < medianValue + medianHalf; ++i)
    {
        int totalFuelCost = 0;
        for (const auto& coordinate : input)
        {
            totalFuelCost += calculateFuelCost(coordinate, i);
        }
        if(lowestCost > totalFuelCost)
        {
            lowestCost = totalFuelCost;
        }
    }

    std::cout<<"Optimal total fuel cost part 2: " << lowestCost;
}

int main()
{
    std::vector<int> inputNumbers = readNumbers();
    findFuelCost(inputNumbers);
    findFuelCostOptimal(inputNumbers);

    return 0;
}
