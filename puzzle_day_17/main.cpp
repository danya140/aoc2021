#include "../helpers.h"

#include "TrajectoryCalculator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <numeric>
#include <cmath>
#include <map>

const char FILE_NAME[] = "input.txt";

std::string readNumbers()
{
    std::ifstream file(FILE_NAME);
    std::string inputData;

    if(file.is_open())
    {
        getline(file, inputData);
    }

    return inputData;
}

int main()
{
    std::string inputNumbers = readNumbers();
    auto calculator = new TrajectoryCalculator(inputNumbers);

    auto highestPoint = calculator->findHighestYPosition();

    std::cout<< "Highest y point: " << highestPoint << "\n";

    std::cout << "Total number of velocities which hit target: " << calculator->collectHittingVelocities();

    return 0;
}
