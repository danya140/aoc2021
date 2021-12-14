#pragma once
#include <map>
#include "../helpers.h"


class PolymerCalculator
{
public:
    PolymerCalculator(const std::vector<std::string>& input, const std::string& polymerTemplate);

    void simulateGrowth(int steps);

    /**
     * Calculate difference between most common and least common frequency
     */
    long long int polymerScore();

private:

    /**
     * Perform growth of @a startingPair for @a steps
     * @param startingPair polymer pair for which we simulate growth
     * @param steps number of steps to simulate
     */
    void step(const std::string& startingPair, int steps);

private:
    std::map<std::string, char> m_rules;
    std::string m_polymer;
    std::map<char, long long int> m_frequency;

};
