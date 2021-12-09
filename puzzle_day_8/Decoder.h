#pragma once

#include "../helpers.h"

#include <map>

enum Segment
{
    LEFT_UP,
    UP,
    RIGHT_UP,
    MIDDLE,
    RIGHT_DOWN,
    DOWN,
    LEFT_DOWN
};

class Decoder
{

public:
    Decoder(const std::string& line);

    int decodeEasyNumbers();
    int decodeEasyNumbers(int number, int length);

    void decodeDigits();

private:
    std::vector<std::string> m_signals;
    std::vector<std::string> m_digits;

    std::map<int, std::string> m_decodedDigits;

    std::map<int, int> m_sizes;

    std::map<int, std::vector<Segment>> m_digitStructure;
};
