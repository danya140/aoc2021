#include "Simulator.h"

#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

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

void simulate(const std::vector<int>& fishes, int days)
{
    auto simulator = new Simulator(fishes);
    simulator->simulate(days);

    std::cout<< "Fish size after " << days <<" days is: "<< simulator->fishCount() << "\n";
}

int main()
{
    std::vector<int> inputNumbers = readNumbers();
    simulate(inputNumbers, 80);
    simulate(inputNumbers, 256);

    return 0;
}
