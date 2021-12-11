#pragma once

#include "../helpers.h"

class Simulator
{
public:
    Simulator(const std::vector<std::string>& input);

    /**
     * Simulate octopuses light for @a steps
     */
    void simulate(int steps);

    /**
     * Simulate octopuses light until all of them lights up
     */
    void simulate();

    /**
     * Return count of octopuses lights up
     */
    int flashCount() const;

    /**
     * Return last step
     */
    int step() const;

private:

    /**
     * Increase all octopuses light level by 1
     */
    void increaseLevel();

    /**
     * Iterate over all octopuses and check if they light up
     */
    void flash();

    /**
     * Check if octopus is lighted up and increase light level of neighbours
     */
    void flash(int i, int j);

    /**
     * Check if all octopuses flashed
     */
    bool checkAllFlashed();


private:
    std::vector<std::vector<int>> m_octopuses;

    int m_flashes;
    int m_step;

};

