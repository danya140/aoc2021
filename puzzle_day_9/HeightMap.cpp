#include "HeightMap.h"




HeightMap::HeightMap(const std::vector<std::string> &heightMap)
{
    for (const auto& line : heightMap)
    {
        std::vector<int> digitLine;
        for (const auto& digit : line)
        {
            digitLine.push_back(digit - '0');
        }
        m_heightMap.push_back(digitLine);
    }
}

bool HeightMap::haveSmallerNeighbour(int i, int j)
{
    bool result = false;
    int currentHeight = m_heightMap[i][j];

    if (i != 0)
    {
        result |= currentHeight >= m_heightMap[i-1][j];
    }
    if (i+1 != m_heightMap.size())
    {
        result |= currentHeight >= m_heightMap[i+1][j];
    }
    if(j != 0)
    {
        result |= currentHeight >= m_heightMap[i][j-1];
    }
    if (j + 1 != m_heightMap[i].size())
    {
        result |= currentHeight >= m_heightMap[i][j+1];
    }

    return result;
}

std::vector<int> HeightMap::findLowestPoints()
{
    std::vector<int> lowestPoints;
    for (int i = 0; i < m_heightMap.size(); ++i)
    {
        for (int j = 0; j < m_heightMap[i].size(); ++j)
        {
            if (!haveSmallerNeighbour(i, j))
            {
                lowestPoints.push_back(m_heightMap[i][j]);
            }
        }
    }

    return lowestPoints;
}