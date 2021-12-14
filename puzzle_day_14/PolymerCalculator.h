#pragma once
#include <map>
#include "../helpers.h"


class PolymerCalculator
{
public:
    PolymerCalculator(const std::vector<std::string>& input, const std::string& polymerTemplate);

    void simulateGrowth(int steps);

    long long int polymerScore();

private:
    void step();

private:
    std::map<std::string, char> m_rules;

    std::string m_polymer;

};


