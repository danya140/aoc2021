#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

CommonBits findCommonBits(const std::vector<Bits>& input)
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

    return commonBits;
}

/**
 * Compare bits. If all bits in position equal return true
 * Works with unequal size by comparing all bits from smallest bits vector to
 */
bool compareBits(const Bits& first, const Bits& second)
{
    bool equal = first[0] == second[0];
    for (int i = 0; i < std::min(first.size(), second.size()); ++i)
    {
        equal &= first[i] == second[i];
    }

    return equal;
}

/**
 * Create bit by rule
 * @param commonBit counter for zeros and ones
 * @param equalBit which bit should be if equal amount of ones and zeros
 * @param leastCommon which bit should be if amount of ones > zeros
 * @param mostCommon which bit should be if amount of ones < zeros
 */
char composeMaskBit(CommonBit commonBit, int equalBit, int leastCommon, int mostCommon)
{
    if (commonBit.m_oneCount > commonBit.m_zeroCount)
    {
        return mostCommon;
    }
    else if(commonBit.m_oneCount == commonBit.m_zeroCount)
    {
        return equalBit;
    }
    else
    {
        return leastCommon;
    }
}

/**
 * Solve 1 part of puzzle
 */
void calculateCommonBits(const std::vector<Bits>& input)
{
    CommonBits commonBits = findCommonBits(input);

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

/**
 * Find rating
 * see composeMaskBit for rules
 */
std::vector<int> findRating(const std::vector<Bits>& input, int equalBit, int leastCommon, int mostCommon)
{
    std::vector<Bits> newInput;
    std::vector<Bits> currentInput = input;

    Bits result;

    int i = 0;
    CommonBits commonBits = findCommonBits(currentInput);
    result.push_back(composeMaskBit(commonBits.at(i++), equalBit, leastCommon, mostCommon));

    while (result.size() != currentInput[0].size())
    {
        newInput.clear();
        std::copy_if(currentInput.begin(), currentInput.end(), std::back_inserter(newInput),
                     [result](const Bits& first)
                     {
                         return compareBits(first, result);
                     });

        if (newInput.size() == 1)
        {
            result = newInput[0];
            break;
        }
        currentInput.clear();
        std::copy(newInput.begin(), newInput.end(), std::back_inserter(currentInput));
        commonBits = findCommonBits(currentInput);
        result.push_back(composeMaskBit(commonBits[i++], equalBit, leastCommon, mostCommon));
    }

    std::vector<int> bits;
    for (const auto& bit : result)
    {
        bits.push_back(bit);
    }
    return bits;
}

/**
 * Solve part 2 of puzzle
 */
void findRatings(const std::vector<Bits>& input)
{
    std::vector<int> oxygen = findRating(input, 1, 0, 1);
    std::vector<int> co2 = findRating(input, 0, 1, 0);
    std::cout << "Day 3 part 2 Oxygen rate bits: " << vector2String(oxygen) << "\n"
              << "Decimal representation: " << std::stoi(vector2String(oxygen), nullptr, 2) << "\n"
              << "CO2 rating: " << vector2String(co2) << "\n"
              << "Decimal representation: " << std::stoi(vector2String(co2), nullptr, 2) << "\n"
              << "Final answer: " << std::stoi(vector2String(oxygen), nullptr, 2) * std::stoi(vector2String(co2), nullptr, 2) << "\n";


}

int main()
{
    std::vector<Bits> inputData = readInput();

    calculateCommonBits(inputData);
    findRatings(inputData);

    return 0;
}
