#include "Simulator.h"

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
    auto simulator = new Simulator(inputNumbers);
    simulator->simulate(100);

    std::cout << "Octopuses flashed " << simulator->flashCount() << " times\n";

    simulator->simulate();
    std::cout << "All octopuses flash at the same time at " << simulator->step() << " step\n";

    return 0;
}
