#pragma once

#include "../helpers.h"

struct Probe
{
    long long int xPosition = 0;
    long long int yPosition = 0;
    long long int xVelocity;
    long long int yVelocity;

    std::pair<int, int> initialVelocity;
    long long int highestY = INT64_MIN;

    bool hit = false;

    Probe(int xSpeed, int ySpeed)
    {
        xVelocity = xSpeed;
        yVelocity = ySpeed;
        initialVelocity = std::make_pair(xSpeed, ySpeed);
    }

    void step()
    {
        xPosition += xVelocity;
        yPosition += yVelocity;

        if(xVelocity > 0)
        {
            xVelocity--;
        }
        else if (xVelocity < 0)
        {
            xVelocity++;
        }

        yVelocity--;

        if (yPosition > highestY)
        {
            highestY = yPosition;
        }
    }
};

class TrajectoryCalculator
{
public:
    TrajectoryCalculator(const std::string& target);

    long long int findHighestYPosition();
    int collectHittingVelocities();

private:
    bool missed(Probe* probe);

private:
    std::pair<int, int> m_xTarget;
    std::pair<int, int> m_yTarget;

};


