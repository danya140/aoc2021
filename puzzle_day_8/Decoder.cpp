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

    m_digitStructure =
        {
            {1, {RIGHT_UP, RIGHT_DOWN}},
            {2, {UP, RIGHT_UP, MIDDLE, LEFT_DOWN, DOWN}},
            {3, {UP, RIGHT_UP, MIDDLE, RIGHT_DOWN, DOWN}},
            {4, {LEFT_UP, RIGHT_UP, MIDDLE, RIGHT_DOWN}},
            {5, {UP, LEFT_UP, MIDDLE, RIGHT_DOWN, DOWN}},
            {6, {UP, LEFT_UP, MIDDLE, LEFT_DOWN, RIGHT_DOWN, DOWN}},
            {7, {UP, RIGHT_UP, RIGHT_DOWN}},
            {8, {UP, LEFT_UP, RIGHT_UP, MIDDLE, LEFT_DOWN, RIGHT_DOWN, DOWN}},
            {9, {UP, LEFT_UP, RIGHT_UP, MIDDLE, RIGHT_DOWN, DOWN}}
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
    std::vector<std::string> undecodedDigits(m_digits.begin(), m_digits.end());

    for (const auto& pair : m_decodedDigits)
    {
        auto it = std::find(undecodedDigits.begin(), undecodedDigits.end(), pair.second);
        if(it != undecodedDigits.end())
        {
            undecodedDigits.erase(it);
        }
    }

    std::vector<Segment> missingSegments = m_digitStructure[8];
    std::string missingSignal = "abcdefg";
    for (const auto& pair : m_decodedDigits)
    {
        if(pair.first == 8)
        {
            continue;
        }

        for (const auto& digit : m_digitStructure[pair.first])
        {
            auto it = std::find(missingSegments.begin(), missingSegments.end(), digit);
            if(it != missingSegments.end())
            {
                missingSegments.erase(it);
            }
        }

        for (const auto& letter : pair.second)
        {
            missingSignal.erase(std::remove(missingSignal.begin(), missingSignal.end(), letter), missingSignal.end());
        }
    }

    //Collect list of digit for undecodedDigits
    std::map<std::string, std::vector<int>> undecodedMap;
    for (const auto signal : undecodedDigits)
    {
        for (const auto& pair : m_sizes)
        {
            if (signal.size() == pair.second)
            {
                undecodedMap[signal].push_back(pair.first);
            }
        }
    }

    std::sort(missingSegments.begin(), missingSegments.end());
    //try to decode
    for (const auto& pair : undecodedMap)
    {
        for (const auto& digit : pair.second)
        {
            auto digitSegments = m_digitStructure[digit];
            std::sort(digitSegments.begin(), digitSegments.end());

            std::vector<Segment> intersection;
            std::set_intersection(missingSegments.begin(), missingSegments.end(),
                                  digitSegments.begin(), digitSegments.end(),
                                  std::back_inserter(intersection));

            if (intersection.size() != missingSegments.size())
            {
                m_decodedDigits[digit] = pair.first;
            }
        }
    }
}
