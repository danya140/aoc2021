#pragma once

#include <functional>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <map>

/**
 * Simulate lanternfish growth
 */
class Simulator
{

public:
    Simulator(const std::vector<int>& fishes);

    /**
     * Simulate fish growth for @a days
     */
    void simulate(int days);

    /**
     * Return current number of fishes
     */
    long long int fishCount();

    /**
     * Calculate next iteration for all fishes with @a timer
     */
    void tick(int timer);

    void printFishes();


private:
    // index is timer and value is number of fishes with same timer
    std::vector<long long int> m_fishes;

    // next iteration of fish state
    std::vector<long long int> m_nextFishes;

};


