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
    for (int i = 0; i < steps; ++i)
    {
        std::cout << "step " << i << "\n";
        step();
    }
}

long long int PolymerCalculator::polymerScore()
{
    std::map<char, int> charFrequency;

    for (const auto& character : m_polymer)
    {
        charFrequency[character]++;
    }

    auto maxIt = std::max_element(charFrequency.begin(), charFrequency.end(),
                     [](std::pair<char, int> pair1, std::pair<char, int> pair2)
                     {
                         return pair1.second < pair2.second;
                     });

    auto minIt = std::max_element(charFrequency.begin(), charFrequency.end(),
                                  [](std::pair<char, int> pair1, std::pair<char, int> pair2)
                                  {
                                      return pair1.second > pair2.second;
                                  });

    return maxIt->second - minIt->second;
}

void PolymerCalculator::step()
{
    std::string newPolymer;

    for (int i = 0; i < m_polymer.size(); i++)
    {
        auto pair = m_polymer.substr(i, 2);
        if (pair.size() != 2)
        {
            newPolymer.push_back(pair[0]);
            break;
        }
        newPolymer.push_back(pair[0]);
        newPolymer.push_back(m_rules[pair]);
//        newPolymer.push_back(pair[1]);
    }

    m_polymer = newPolymer;
}