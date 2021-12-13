#include "../helpers.h"
#include "Folder.h"

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
            if (line.empty())
            {
                break;
            }
            inputData.push_back(line);
        }
    }

    return inputData;
}

std::vector<std::string> readCommands()
{
    std::ifstream file(FILE_NAME);
    std::vector<std::string> inputData;

    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            if (std::find(line.begin(), line.end(), '=') != line.end())
            {
                inputData.push_back(line);
            }
        }
    }

    return inputData;
}

int main()
{
    std::vector<std::string> inputNumbers = readNumbers();
    std::vector<std::string> commands = readCommands();

    auto folder = new Folder(inputNumbers, commands);

    folder->performCommand();
    std::cout << "Number of dots after first fold: " << folder->countDots() << "\n";

    folder->performAll();
    std::cout<< " Activation code:\n";
    folder->print();

    return 0;
}
