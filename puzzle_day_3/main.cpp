#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct CommonBit
{
    int m_zeroCount = 0;
    int m_oneCount = 0;
};
typedef std::vector<CommonBit> CommonBits;

typedef std::vector<char> Bits;

std::vector<char> parseBits(const std::string& line)
{
    std::vector<char> bits;
    for (const auto& bit : line)
    {
        bits.push_back(bit - '0');
    }

    return bits;
}

std::vector<Bits> readInput()
{
    std::ifstream file("input.txt");

    std::vector<Bits> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            inputData.push_back(parseBits(line));
        }
    }

    return inputData;
}

void calculateCommonBits(const std::vector<Bits>& input)
{
    //init common bits vector
    CommonBits commonBits;
    for (int i = 0; i < input[0].size(); ++i)
    {
        commonBits.push_back(CommonBit());
    }

    for (const auto& bits : input)
    {
        int i = 0;
        for (const auto& bit : bits)
        {
            if (bit == 0)
            {
                commonBits[i].m_zeroCount++;
            }
            else
            {
                commonBits[i].m_oneCount++;
            }
            i++;
        }
    }

    //compose gamma rate and epsilon rate
    std::vector<int> gamma;
    std::vector<int> epsilon;
    for (const auto& commonBit : commonBits)
    {
        if (commonBit.m_oneCount > commonBit.m_zeroCount)
        {
            gamma.push_back(1);
            epsilon.push_back(0);
        }
        else
        {
            gamma.push_back(0);
            epsilon.push_back(1);
        }
    }

    std::cout << "Day 3 part 1 gamma: " << vector2String(gamma) << " epsilon: " << vector2String(epsilon) << "\n";
    std::cout << "Decimal interpretation gamma: " << std::stoi(vector2String(gamma), nullptr, 2)
                << " epsilon: " << std::stoi(vector2String(epsilon),nullptr, 2) << "\n";
    std::cout << "And final answer is: " << std::stoi(vector2String(gamma), nullptr, 2) * std::stoi(vector2String(epsilon),nullptr, 2) << "\n";
}

int main()
{
    std::vector<Bits> inputData = readInput();

    calculateCommonBits(inputData);

    return 0;
}
