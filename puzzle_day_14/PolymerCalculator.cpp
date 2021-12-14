#include "PolymerCalculator.h"


PolymerCalculator::PolymerCalculator(const std::vector<std::string> &input, const std::string &polymerTemplate)
    : m_polymer(polymerTemplate)
{
    for (const auto& rule : input)
    {
        auto rulePair = split(rule, ' ');
        m_rules[rulePair[0]] = rulePair[2][0];
    }
}

void PolymerCalculator::simulateGrowth(int steps)
{
    m_frequency.clear();
    for (int i = 0; i < m_polymer.size(); ++i)
    {
        auto pair = m_polymer.substr(i, 2);
        if (pair.size() != 2)
        {
            break;
        }
        step(pair, steps);
    }

    //exclude overlapping characters
    for (int i = 1; i < m_polymer.size() - 1; ++i)
    {
        m_frequency[m_polymer[i]]--;
    }
}

long long int PolymerCalculator::polymerScore()
{

    auto maxIt = std::max_element(m_frequency.begin(), m_frequency.end(),
                     [](std::pair<char, long long int> pair1, std::pair<char, long long int> pair2)
                     {
                         return pair1.second < pair2.second;
                     });

    auto minIt = std::max_element(m_frequency.begin(), m_frequency.end(),
                                  [](std::pair<char, long long int> pair1, std::pair<char, long long int> pair2)
                                  {
                                      return pair1.second > pair2.second;
                                  });

    return maxIt->second - minIt->second;
}

void PolymerCalculator::step(const std::string& startingPair, int steps)
{
    assert(startingPair.size() == 2);

    std::map<std::string, long long int> pairFrequency;
    std::map<std::string, long long int> nextPairFrequency;

    pairFrequency[startingPair]++;


    for (int step = 0; step < steps; ++step)
    {
        for (const auto& pair : pairFrequency)
        {
            std::string newPair1;
            newPair1.push_back(pair.first[0]);
            newPair1.push_back(m_rules[pair.first]);

            std::string newPair2;
            newPair2.push_back(m_rules[pair.first]);
            newPair2.push_back(pair.first[1]);

            nextPairFrequency[newPair1] += 1 * pair.second;
            nextPairFrequency[newPair2] += 1 * pair.second;
        }
        pairFrequency = nextPairFrequency;
        nextPairFrequency.clear();
    }

    std::string lastSymbol;
    lastSymbol.push_back(startingPair[1]);
    pairFrequency[lastSymbol]++;

    // Total frequency consists only from 1st character in pair
    for(const auto& pair : pairFrequency)
    {
        m_frequency[pair.first[0]] += pair.second;
    }
}