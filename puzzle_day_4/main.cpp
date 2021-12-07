#include "Board.h"

#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const char FILE_NAME[] = "input.txt";

std::vector<int> readNumbers()
{
    std::ifstream file(FILE_NAME);

    std::vector<int> inputData;

    if(file.is_open())
    {
        std::string line;
        std::getline(file, line);
        for (const auto& digit : split(line, ','))
        {
            inputData.push_back(std::stoi(digit));
        }
    }

    return inputData;
}

std::vector<Board*> readBoards()
{
    std::ifstream file(FILE_NAME);
    std::vector<Board*> boards;

    if(file.is_open())
    {
        std::string line;
        std::getline(file, line); //skip number line
        std::getline(file, line); //skip empty line

        std::string bufferLine;
        int boardLine = 1;
        while (std::getline(file, line))
        {
            bufferLine += line;
            if(boardLine++ == BOARD_ROW_LIMIT)
            {
                boards.push_back(new Board(bufferLine));
                bufferLine.clear();
                std::getline(file, line); //skip empty line
                boardLine = 1;
            }
            else
            {
                bufferLine += " ";
            }
        }
    }

    return boards;
}

Board* playBingo(const std::vector<int>& numbers, const std::vector<Board*>& boards, bool firstWin)
{
    Board* winningBoard = nullptr;
    for (const auto& number : numbers)
    {
        for (const auto& board : boards)
        {
            if(board->alreadyWin()) //skip boards which already win
            {
                continue;
            }

            if (board->crossNumber(number))
            {
                if (board->isWin())
                {
                    board->setWin();
                    winningBoard = board;
                    if (firstWin)
                    {
                        return  winningBoard;
                    }
                }
            }

        }
    }

    return winningBoard;
}

void calculateAnswerPart1(const std::vector<int>& numbers, const std::vector<Board*>& boards)
{
    auto winingBoard = playBingo(numbers, boards, true);

    std::cout<< "Win score: " << winingBoard->answer() << "\n";
}

void calculateAnswerPart2(const std::vector<int>& numbers, const std::vector<Board*>& boards)
{
    auto winingBoard = playBingo(numbers, boards, false);

    std::cout<< "Last Wining board score: " << winingBoard->answer();
}

int main()
{
    std::vector<int> inputNumbers = readNumbers();
    std::vector<Board*> boards = readBoards();

    calculateAnswerPart1(inputNumbers, boards);

    for (const auto& board : boards)
    {
        board->returnState();
    }

    calculateAnswerPart2(inputNumbers, boards);

    return 0;
}
