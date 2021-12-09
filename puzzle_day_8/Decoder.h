#pragma once

#include "../helpers.h"

#include <map>

// Numbers segments sizes
enum Sizes
{
    ONE = 2,
    TWO = 5,
    FOUR = 4,
    SEVEN = 3,
    EIGHT = 7
};


enum Segments
{
    LEFT_UP,
    UP,
    RIGHT_UP,
    MIDDLE,
    RIGHT_DOWN,
    DOWN,
    LEFT_DOWN
};

struct DigitGuess
{
    std::vector<Segments> m_segments;
    std::vector<char> m_signals;
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
};
