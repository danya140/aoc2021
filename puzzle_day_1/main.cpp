#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
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

    int lastNumber = INT_MAX;

    int increasedCount = 0;

    for(int number : inputData)
    {
        if(lastNumber < number)
        {
            increasedCount++;
        }

        lastNumber = number;
    }

    std::cout << "increased count: " << increasedCount;

    return 0;
}
