#include "Simulator.h"

Simulator::Simulator(const std::vector<std::string> &input)
    : m_flashes(0),
      m_step(0)
{
    for (const auto& line : input)
    {
        std::vector<int> octopusesLine;
        for (const auto& digit : line)
        {
            octopusesLine.push_back(digit - '0');
        }
        m_octopuses.push_back(octopusesLine);
    }
}

int Simulator::flashCount() const
{
    return m_flashes;
}

int Simulator::step() const
{
    return m_step;
}

void Simulator::simulate(int steps)
{
    for (int step = 0; step < steps; ++step)
    {
        increaseLevel();
        flash();
        m_step++;
    }
}

void Simulator::simulate()
{
    while (!checkAllFlashed())
    {
        increaseLevel();
        flash();
        m_step++;
    }
}

bool Simulator::checkAllFlashed()
{
    for (const auto& line : m_octopuses)
    {
        for (const auto& octopus : line)
        {
            if (octopus != 0)
            {
                return false;
            }
        }
    }

    return true;
}

void Simulator::increaseLevel()
{
    for (auto & m_octopuse : m_octopuses)
    {
        for (int & octopus : m_octopuse)
        {
            octopus += 1;
        }
    }
}

void Simulator::flash()
{
    for (int i = 0; i < m_octopuses.size(); ++i)
    {
        for (int j = 0; j < m_octopuses[i].size(); ++j)
        {
            flash(i, j);
        }
    }
}

void Simulator::flash(int i, int j)
{
    if(m_octopuses[i][j] > 9)
    {
        m_octopuses[i][j] = 0;
        m_flashes++;

        //Check neighbours
        for (int k = i-1; k <= i+1; ++k)
        {
            for (int l = j-1; l <=j+1; ++l)
            {
                if (k < 0 || k >= m_octopuses.size()
                    || l < 0 || l >= m_octopuses[k].size())
                {
                    continue; // ignore out of range
                }
                if (m_octopuses[k][l] == 0) // already flashed
                {
                    continue;
                }

                m_octopuses[k][l] += 1;
                flash(k,l);
            }
        }
    }
}