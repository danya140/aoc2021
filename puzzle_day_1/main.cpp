#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> readInput()
{
    std::ifstream file("input.txt");

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

/**
 * Part 1
 *
 * Count number when next number bigger
 */
int calculateNumberOfIncreases(const std::vector<int>& input)
{
    int lastNumber = INT_MAX;
    int increasedCount = 0;

    for(int number : input)
    {
        if(lastNumber < number)
        {
            increasedCount++;
        }
        lastNumber = number;
    }

    return increasedCount;
}

/**
 * Part 2
 */
int calculateNumberOfIncreasesPairs(const std::vector<int>& input)
{
    int increasedCount = 0;

    for (int i = 0; i < input.size(); ++i)
    {
        if (i+3 > input.size())
        {
            break;
        }

        if(input[i] < input[i+3])
        {
            increasedCount++;
        }
    }

    return increasedCount;
}

int main()
{
    std::vector<int> inputData = readInput();

    std::cout << "Part 1. Increased count: " << calculateNumberOfIncreases(inputData) <<std::endl;
    std::cout << "Part 2. Increased count by pairs: " << calculateNumberOfIncreasesPairs(inputData);

    return 0;
}
