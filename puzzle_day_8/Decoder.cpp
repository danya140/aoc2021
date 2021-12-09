#include "Decoder.h"

#include <cassert>

Decoder::Decoder(const std::string& line)
{
    auto splitedData = split(line, '|');
    assert(splitedData.size() == 2);

    m_signals = split(splitedData[0], ' ');
    m_digits = split(splitedData[1], ' ');

    m_sizes =
        {
            {1, 2},
            {2, 5},
            {3, 5},
            {4, 4},
            {5, 5},
            {6, 6},
            {7, 3},
            {8, 7},
            {9, 6}
        };
}

int Decoder::decodeEasyNumbers()
{
    int entryCounter = 0;
    for (const auto& number : {1, 4, 7, 8})
    {
        entryCounter += decodeEasyNumbers(number, m_sizes[number]);
    }

    return entryCounter;
}

int Decoder::decodeEasyNumbers(int number, int length)
{
    int entryCounter = 0;
    for (const auto& digit : m_digits)
    {
        if(digit.size() == length)
        {
            m_decodedDigits[number] = digit;
            entryCounter++;
        }
    }

    return entryCounter;
}

void Decoder::decodeDigits()
{

}
