#pragma once

#include "../helpers.h"

// Numbers with unique length
enum Unique
{
    ONE = 2,
    FOUR = 4,
    SEVEN = 3,
    EIGHT = 7
};

class Decoder
{

public:
    Decoder(const std::vector<std::string>& signals, const std::vector<std::string>& digits);




private:
    std::vector<std::string> m_signals;
    std::vector<std::string> m_digits;
};
