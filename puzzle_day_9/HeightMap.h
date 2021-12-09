#pragma once

#include "../helpers.h"

class HeightMap
{
public:
    HeightMap(const std::vector<std::string>& heightMap);

    std::vector<int> findLowestPoints();

private:
    bool haveSmallerNeighbour(int i, int j);

private:
    std::vector<std::vector<int>> m_heightMap;
};

