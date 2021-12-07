#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const char FILE_NAME[] = "input.txt";

const int MAXIMUM_COORDINATE = 1000;

struct Line
{
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;

    Line(const std::string& str)
    {
        auto coordinates = split(str, ',');
        x1 = std::stoi(coordinates[0]);
        y2 = std::stoi(coordinates[2]);
        y1 = std::stoi(split(coordinates[1], ' ')[0]);
        x2 = std::stoi(split(coordinates[1], ' ')[2]);
    }
};

std::vector<Line> readNumbers()
{
    std::ifstream file(FILE_NAME);

    std::vector<Line> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            inputData.push_back(Line(line));
        }
    }

    return inputData;
}

/**
 * pretty print for vent map, but with big numbers it looks messy
 */
void printMap(const std::vector<std::vector<char>>& ventMap)
{
    for (const auto& row : ventMap)
    {
        for(const auto& point : row)
        {
            std::cout<< point;
        }
        std::cout<<"\n";
    }
}

/**
 * Create new value for point based on @a currentValue
 */
char newPointValue(char currentValue)
{
    if(currentValue == '.')
    {
        return '1';
    }
    else
    {
        return currentValue + 1;
    }
}

void buildStraightLine(std::vector<std::vector<char>>& ventMap, const Line& line)
{
    if(line.x1 == line.x2 || line.y1 == line.y2)
    {
        for (int y = std::min(line.y1, line.y2); y <= std::max(line.y1, line.y2); ++y)
        {
            for (int x = std::min(line.x1, line.x2); x <= std::max(line.x1, line.x2); ++x)
            {
                ventMap[y][x] = newPointValue(ventMap[y][x]);
            }
        }
    }
}

void buildDiagonalLine(std::vector<std::vector<char>>& ventMap, const Line& line)
{
    if(line.x1 == line.x2 || line.y1 == line.y2)
    {
        buildStraightLine(ventMap, line);
    }
    else
    {
        int xMove = line.x1 > line.x2 ? -1 : 1;
        int yMove = line.y1 > line.y2 ? -1 : 1;

        int x = line.x1;
        int y = line.y1;
        do
        {
            ventMap[y][x] = newPointValue(ventMap[y][x]);
            x += xMove;
            y += yMove;
        }
        while (x != line.x2 && y != line.y2);

        ventMap[y][x] = newPointValue(ventMap[y][x]); //last point
    }
}

void createVentMap(const std::vector<Line>& input, bool vertical)
{
    std::vector<std::vector<char>> ventMap;

    //initialize map
    //From data it look like maximum coordinate is 1000 so i hardcoded MAXIMUM_COORDINATE
    for (int y = 0; y < MAXIMUM_COORDINATE; ++y)
    {
        std::vector<char> row;
        for (int x = 0; x < MAXIMUM_COORDINATE; ++x)
        {
            row.push_back('.');
        }
        ventMap.push_back(row);
    }


    for (const auto& line : input)
    {
        if (vertical)
        {
            buildDiagonalLine(ventMap, line);
        }
        else
        {
            buildStraightLine(ventMap, line);
        }
    }

    //Count overlaps
    int overlapCount = 0;
    for (const auto& row : ventMap)
    {
        for (const auto& point : row)
        {
            if (point >= '2')
            {
                overlapCount++;
            }
        }
    }

    if(vertical)
    {
        std::cout<<"Part 2 overlap count with diagonal line is " << overlapCount << "\n";
    }
    else
    {
        std::cout<<"Part 1 overlap count without diagonal line is " << overlapCount << "\n";
    }

//    printMap(ventMap); //messy with real data
}

int main()
{
    std::vector<Line> inputNumbers = readNumbers();
    createVentMap(inputNumbers, false);
    createVentMap(inputNumbers, true);

    return 0;
}
