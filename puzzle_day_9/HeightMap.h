#pragma once

#include "../helpers.h"

class HeightMap
{
public:
    HeightMap(const std::vector<std::string>& heightMap);

    std::vector<int> findLowestPoints();

    std::vector<int> mapBasins();

private:
    bool haveSmallerNeighbour(int i, int j);

    bool isBasinNeighbour(int i, int j);

    /**
     * @return self size and all of neighbours and its neighbours ...
     */
    int mapNeighbour(int i, int j);

private:
    std::vector<std::vector<int>> m_heightMap;
};

