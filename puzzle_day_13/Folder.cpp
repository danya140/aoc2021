#include "Folder.h"


Folder::Folder(const std::vector<std::string> &points, const std::vector<std::string> &commands)
    : m_lastCommand(0)
{

    for (const auto& command : commands)
    {
        auto cmd = split(split(command, ' ')[2], '=');
        m_commands.push_back({cmd[0][0], std::stoi(cmd[1])});
    }

    std::vector<int> xCoordinates;
    std::vector<int> yCoordinates;

    for (const auto& point : points)
    {
        auto coordinates = split(point, ',');
        xCoordinates.push_back(std::stoi(coordinates[1]));
        yCoordinates.push_back(std::stoi(coordinates[0]));
    }

    int xMax = *std::max_element(xCoordinates.begin(), xCoordinates.end());
    int yMax = *std::max_element(yCoordinates.begin(), yCoordinates.end());

    for (int i = 0; i <= xMax; ++i)
    {
        std::vector<char> line;
        for (int j = 0; j <= yMax; ++j)
        {
            line.push_back('.');
        }
        m_field.push_back(line);
    }

    for (int i = 0; i < xCoordinates.size(); ++i)
    {
        m_field[xCoordinates[i]][yCoordinates[i]] = '#';
    }
}

void Folder::print()
{
    for (const auto& line : m_field)
    {
        for (const auto& point : line)
        {
            std::cout << point;
        }
        std::cout << std::endl;
    }
}

void Folder::performAll()
{
    for (int i = m_lastCommand; i < m_commands.size(); ++i)
    {
        performCommand();
    }
}

void Folder::performCommand()
{
    auto command = m_commands[m_lastCommand++];

    if (command.first == 'x')
    {
        foldX(command.second);
    }
    else
    {
        foldY(command.second);
    }
}

int Folder::countDots()
{
    int dotCounter = 0;
    for (const auto& line : m_field)
    {
        for (const auto& point : line)
        {
            if (point == '#')
            {
                dotCounter++;
            }
        }
    }

    return dotCounter;
}

void Folder::foldY(int y)
{
    std::vector<std::vector<char>> newField;

    //Copy part which not affected by fold
    for (int i = 0; i < y; ++i)
    {
        newField.push_back(m_field[i]);
    }

    for (int i = y; i < m_field.size(); ++i)
    {
        for (int j = 0; j < m_field[i].size(); ++j)
        {
            if (m_field[i][j] == '#')
            {
                newField[y*2 - i][j] = '#';
            }
        }
    }

    m_field = newField;
}

void Folder::foldX(int x)
{
    std::vector<std::vector<char>> newField;

    //Copy part which not affected by fold
    for (const auto& line : m_field)
    {
        std::vector<char> newLine;
        for (int i = 0; i < x; ++i)
        {
            newLine.push_back(line[i]);
        }
        newField.push_back(newLine);
    }

    for (int i = 0; i < m_field.size(); ++i)
    {
        for (int j = x; j < m_field[i].size(); ++j)
        {
            if (m_field[i][j] == '#')
            {
                newField[i][x*2 - j] = '#';
            }
        }
    }

    m_field = newField;
}