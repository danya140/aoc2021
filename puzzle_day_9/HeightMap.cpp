#include "HeightMap.h"


std::vector<std::pair<int, int>> createNeighbourCoordinate(int i, int j)
{
    std::vector<std::pair<int, int>> neighbours;
    neighbours.push_back(std::make_pair(i+1, j));
    neighbours.push_back(std::make_pair(i-1, j));
    neighbours.push_back(std::make_pair(i, j+1));
    neighbours.push_back(std::make_pair(i, j-1));

    return neighbours;
}

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

bool HeightMap::isBasinNeighbour(int i, int j)
{
    return i != -1 && j != -1
            && i != m_heightMap.size() && j != m_heightMap[i].size()
            && m_heightMap[i][j] != 9 && m_heightMap[i][j] != -1;
}

int HeightMap::mapNeighbour(int i, int j)
{
    int basinSize = 1; //self

    m_heightMap[i][j] = -1; //mark as mapped

    for (const auto coordinate : createNeighbourCoordinate(i, j))
    {
        if(isBasinNeighbour(coordinate.first, coordinate.second))
        {
            basinSize += mapNeighbour(coordinate.first, coordinate.second);
        }
    }

    return basinSize;
}

std::vector<int> HeightMap::mapBasins()
{
    std::vector<int> basins;

    for (int i = 0; i < m_heightMap.size(); ++i)
    {
        for (int j = 0; j < m_heightMap[i].size(); ++j)
        {
            if(m_heightMap[i][j] != 9 && m_heightMap[i][j] != -1)
            {
                basins.push_back(mapNeighbour(i, j));
            }
        }
    }

    return basins;
}