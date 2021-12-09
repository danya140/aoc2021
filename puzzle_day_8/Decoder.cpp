#include "Decoder.h"

#include <cassert>
#include <set>

Decoder::Decoder(const std::string& line)
{
    auto splitedData = split(line, '|');
    assert(splitedData.size() == 2);

    m_signals = split(splitedData[0], ' ');
    m_digits = split(splitedData[1], ' ');

    //sort
    for (auto& signal : m_signals)
    {
        std::sort(signal.begin(), signal.end());
    }

    for (auto& digit : m_digits)
    {
        std::sort(digit.begin(), digit.end());
    }


    m_sizes =
        {
            {0, 6},
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
            {0, {RIGHT_UP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT_UP}},
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
    for (const auto& digit : m_signals)
    {
        if(digit.size() == length)
        {
            m_decodedDigits[number] = digit;
        }
    }

    return entryCounter;
}

void Decoder::decipherAll()
{
    std::set<std::string> undecodedDigits(m_digits.begin(), m_digits.end());
    std::copy(m_signals.begin(), m_signals.end(), std::inserter(undecodedDigits, undecodedDigits.begin()));

    for (const auto& pair : m_decodedDigits)
    {
        auto it = std::find(undecodedDigits.begin(), undecodedDigits.end(), pair.second);
        while(it != undecodedDigits.end())
        {
            undecodedDigits.erase(it);
            it = std::find(undecodedDigits.begin(), undecodedDigits.end(), pair.second);
        }
    }

    std::vector<char> upSegment;
    std::set_difference(m_decodedDigits[7].begin(), m_decodedDigits[7].end(), m_decodedDigits[1].begin(), m_decodedDigits[1].end(), std::back_inserter(upSegment));
    m_segmentMap[UP] = upSegment[0];


    //decode 9. it contains 7 and 4 signals
    std::set<char> ninePattern(m_decodedDigits[4].begin(), m_decodedDigits[4].end());
    std::copy(m_decodedDigits[7].begin(), m_decodedDigits[7].end(), std::inserter(ninePattern, ninePattern.begin()));

    std::set<char> sixPattern;
    std::set_difference(m_decodedDigits[8].begin(), m_decodedDigits[8].end(),
                        m_decodedDigits[1].begin(), m_decodedDigits[1].end(),
                        std::inserter(sixPattern, sixPattern.begin()));

    for (const auto& signal : undecodedDigits)
    {
        if(containsAll(signal, std::string(sixPattern.begin(), sixPattern.end())))
        {
            m_decodedDigits[6] = signal;
        }
        else if(containsAll(signal, std::string(ninePattern.begin(), ninePattern.end())))
        {
            m_decodedDigits[9] = signal;
        }
    }

    std::vector<char> rightUpSegment;
    std::set_difference(m_decodedDigits[8].begin(), m_decodedDigits[8].end(),
                        m_decodedDigits[6].begin(), m_decodedDigits[6].end(),
                        std::back_inserter(rightUpSegment));
    m_segmentMap[RIGHT_UP] = rightUpSegment[0];

    std::vector<char> rightDownSegment;
    std::set_difference(m_decodedDigits[8].begin(), m_decodedDigits[8].end(),
                        m_decodedDigits[9].begin(), m_decodedDigits[9].end(),
                        std::back_inserter(rightDownSegment));
    m_segmentMap[LEFT_DOWN] = rightDownSegment[0];

    std::vector<char> downSegment;
    std::set_difference(m_decodedDigits[9].begin(), m_decodedDigits[9].end(),
                        m_decodedDigits[4].begin(), m_decodedDigits[4].end(),
                        std::back_inserter(downSegment));
    downSegment.erase(std::remove(downSegment.begin(), downSegment.end(), m_segmentMap[UP]), downSegment.end());
    m_segmentMap[DOWN] = downSegment[0];

    m_decodedDigits[5] = m_decodedDigits[9];
    m_decodedDigits[5].erase(std::remove(m_decodedDigits[5].begin(), m_decodedDigits[5].end(), m_segmentMap[RIGHT_UP]), m_decodedDigits[5].end());

    //clean up undecoded
    for (const auto& pair : m_decodedDigits)
    {
        auto it = std::find(undecodedDigits.begin(), undecodedDigits.end(), pair.second);
        while(it != undecodedDigits.end())
        {
            undecodedDigits.erase(it);
            it = std::find(undecodedDigits.begin(), undecodedDigits.end(), pair.second);
        }
    }

    for (const auto& signal : undecodedDigits)
    {
        if (signal.size() == m_sizes[0])
        {
            m_decodedDigits[0] = signal;
        }
        else if (containsAll(signal, m_decodedDigits[1]))
        {
            m_decodedDigits[3] = signal;
        }
        else
        {
            m_decodedDigits[2] = signal;
        }
    }
}

int Decoder::decodeDigits()
{
    decipherAll();
    int result = 0;

    int multiplier = 1000;
    for (const auto& signal : m_digits)
    {
        auto it = std::find_if(m_decodedDigits.begin(), m_decodedDigits.end(),
                                   [signal](const std::pair<int, std::string>& pair)
                                   {
                                        return pair.second == signal;
                                   });
        result += it->first * multiplier;
        multiplier /= 10;
    }

    return result;
}
