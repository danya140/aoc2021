#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

enum Action
{
    FORWARD,
    DOWN,
    UP
};

struct Command
{
    Action m_action;
    int m_units;

    Command(const std::string& line)
    {
        auto commandLine = split(line, ' ');
        assert(commandLine.size() == 2);

        if (commandLine[0] == "forward")
        {
            m_action = FORWARD;
        }
        else if(commandLine[0] == "up")
        {
            m_action = UP;
        }
        else if(commandLine[0] == "down")
        {
            m_action = DOWN;
        }

        m_units = std::stoi(commandLine[1]);
    }
};

struct Position
{
    int m_depth = 0;
    int m_hPosition = 0;
    int m_aim = 0;

    void moveWithoutAim(Command command)
    {
        switch (command.m_action)
        {
            case FORWARD:
                m_hPosition += command.m_units;
                break;
            case DOWN:
                m_depth += command.m_units;
                break;
            case UP:
                m_depth -= command.m_units;
                break;
        }
    }

    void aimedMove(Command command)
    {
        switch (command.m_action)
        {
            case FORWARD:
                m_hPosition += command.m_units;
                m_depth += m_aim * command.m_units;
                break;
            case DOWN:
                m_aim += command.m_units;
                break;
            case UP:
                m_aim -= command.m_units;
                break;
        }
    }
};

std::vector<Command> readInput()
{
    std::ifstream file("input.txt");

    std::vector<Command> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            inputData.push_back(Command(line));
        }
    }

    return inputData;
}

void calculatePositionMultiplication(const std::vector<Command>& input)
{
    Position position;

    for (const auto& cmd : input)
    {
        position.moveWithoutAim(cmd);
    }

    std::cout << "Part 1 horizontal position(" << position.m_hPosition << ") x depth ("
              << position.m_depth <<") :" << position.m_depth * position.m_hPosition << "\n";
}

void calculateAimedPositionMultiplication(const std::vector<Command>& input)
{
    Position position;

    for (const auto& cmd : input)
    {
        position.aimedMove(cmd);
    }

    std::cout << "Part 2 horizontal position(" << position.m_hPosition << ") x depth ("
              << position.m_depth <<") :" << position.m_depth * position.m_hPosition << "\n";
}

int main()
{
    std::vector<Command> inputData = readInput();
    calculatePositionMultiplication(inputData);
    calculateAimedPositionMultiplication(inputData);

    return 0;
}
