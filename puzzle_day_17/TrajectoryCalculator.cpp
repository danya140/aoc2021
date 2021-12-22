#include "TrajectoryCalculator.h"

TrajectoryCalculator::TrajectoryCalculator(const std::string &target)
{
    std::string input(target);
    std::replace(input.begin(), input.end(), ',', ' ');
    std::replace(input.begin(), input.end(), '=', ' ');

    auto values = split(input, ' ');

    auto xValues = split(values[3], '.');
    m_xTarget = std::make_pair(std::stoi(xValues[0]), std::stoi(xValues[1]));
    auto yValues = split(values[5], '.');
    m_yTarget = std::make_pair(std::stoi(yValues[0]), std::stoi(yValues[1]));
}

long long int TrajectoryCalculator::findHighestYPosition()
{
    Probe* highestProbe = new Probe(0,0);
    for (int x = m_xTarget.first * -1; x < m_xTarget.second; ++x)
    {
        for (int y = m_yTarget.first - 1000; y < m_yTarget.second + 1000; ++y)
        {
            auto probe = new Probe(x, y);
            while (!missed(probe))
            {
                probe->step();
            }

            if(highestProbe->highestY < probe->highestY && probe->hit)
            {
                highestProbe = probe;
            }
            else
            {
                delete probe;
            }
        }
    }
    return highestProbe->highestY;
}

int TrajectoryCalculator::collectHittingVelocities()
{
    std::vector<std::pair<int, int>> velocities;
    for (int x = m_xTarget.first * -1; x < m_xTarget.second; ++x)
    {
        for (int y = m_yTarget.first - 1000; y < m_yTarget.second + 10000; ++y)
        {
            auto probe = new Probe(x, y);
            while (!missed(probe))
            {
                probe->step();
            }

            if(probe->hit)
            {
                velocities.push_back(probe->initialVelocity);
            }
            else
            {
                delete probe;
            }
        }
    }

    return velocities.size();
}

bool TrajectoryCalculator::missed(Probe *probe)
{
    if (m_yTarget.first > probe->yPosition && probe->yVelocity <= 0)
    {
        return true;
    }

    if(m_xTarget.second < probe->xPosition && probe->xVelocity >= 0)
    {
        return true;
    }
    if (m_xTarget.first > probe->xPosition && probe->xVelocity <= 0)
    {
        return true;
    }

    if (m_yTarget.first <= probe->yPosition && probe->yPosition <= m_yTarget.second &&
        m_xTarget.first <= probe->xPosition && probe->xPosition <= m_xTarget.second)
    {
        probe->hit = true;
    }


    return false;
}

