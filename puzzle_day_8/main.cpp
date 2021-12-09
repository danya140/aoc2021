#include "Decoder.h"

#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <numeric>
#include <cmath>

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

void decodeEasy(const std::vector<Decoder*>& decoders)
{
    int easyCounter = 0;
    for (const auto& decoder : decoders)
    {
        easyCounter += decoder->decodeEasyNumbers();
    }
    std::cout << "Total number of easy numbers: " << easyCounter << "\n";
}


void decodeAll(const std::vector<Decoder*>& decoders)
{
    decodeEasy(decoders);

    int decodedSum = 0;
    for (const auto& decoder : decoders)
    {
        decodedSum += decoder->decodeDigits();
    }

    std::cout<< "Sum of all decoded numbers: " << decodedSum;
}

int main()
{
    std::vector<std::string> inputNumbers = readNumbers();

    std::vector<Decoder*> decoders;

    for (const auto& line : inputNumbers)
    {
        decoders.push_back(new Decoder(line));
    }

    decodeAll(decoders);

    return 0;
}
