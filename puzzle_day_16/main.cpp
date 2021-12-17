#include "../helpers.h"

#include "ParserHelpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <numeric>
#include <cmath>
#include <map>

const char FILE_NAME[] = "input.txt";

std::vector<int> convertHex(const std::string& hex)
{
    std::vector<int> result;

    static std::map<char, std::vector<int>> bitSet
        {
            {'0', {0,0,0,0}},
            {'1', {0,0,0,1}},
            {'2', {0,0,1,0}},
            {'3', {0,0,1,1}},
            {'4', {0,1,0,0}},
            {'5', {0,1,0,1}},
            {'6', {0,1,1,0}},
            {'7', {0,1,1,1}},
            {'8', {1,0,0,0}},
            {'9', {1,0,0,1}},
            {'A', {1,0,1,0}},
            {'B', {1,0,1,1}},
            {'C', {1,1,0,0}},
            {'D', {1,1,0,1}},
            {'E', {1,1,1,0}},
            {'F', {1,1,1,1}},
        };

    for (const auto& symbol : hex)
    {
        auto bits = bitSet[symbol];
        std::copy(bits.begin(), bits.end(), std::back_inserter(result));
    }

    return result;
}

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
    std::vector<int> inputNumbers = convertHex(readNumbers());
    auto packet = parsePacketByType(inputNumbers);

    std::cout << " Sum of all versions: " << packet->versions() << "\n";
    std::cout << " Result value: " << packet->doAction() << "\n";

    return 0;
}
