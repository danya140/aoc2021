#include "Board.h"

#include "../helpers.h"

#include <algorithm>

Board::Board(const std::string &board)
{
    auto numbers = split(board, ' ');
    for (const auto& number : numbers)
    {
        m_board.push_back(std::stoi(number));
    }
    std::copy(m_board.begin(), m_board.end(), std::back_inserter(m_originalBoard));
}

bool Board::crossNumber(int number)
{
    bool changed = false;
    auto it = std::find(m_board.begin(), m_board.end(), number);
    while (it != m_board.end())
    {
        *(it) = -1;
        it = std::find(m_board.begin(), m_board.end(), number);
        changed = true;
    }

    m_lastNumber = number;

    return changed;
}

bool Board::isWin()
{
    std::vector<int> rowSums;
    std::vector<int> columnSums;

    //calculate sum for rows
    for (int row = 0; row < BOARD_ROW_LIMIT; ++row)
    {
        int rowSum = 0;
        for (int number = 0; number < BOARD_ROW_LIMIT; ++number)
        {
            rowSum += m_board[row*BOARD_ROW_LIMIT + number];
        }

        rowSums.push_back(rowSum);
    }

    //calculate sum for columns
    for (int column = 0; column < BOARD_ROW_LIMIT; ++column)
    {
        int columnSum = 0;
        for (int number = 0; number < BOARD_ROW_LIMIT; ++number)
        {
            columnSum += m_board[column + BOARD_ROW_LIMIT*number];
        }

        columnSums.push_back(columnSum);
    }

    //check if row or column have all -1
    auto rowIt = std::find(rowSums.begin(), rowSums.end(), -1 * BOARD_ROW_LIMIT);
    auto columnIt = std::find(columnSums.begin(), columnSums.end(), -1 * BOARD_ROW_LIMIT);

    return rowIt != rowSums.end() || columnIt != columnSums.end();
}

void Board::setWin()
{
    m_alreadyWin = true;
}

bool Board::alreadyWin()
{
    return m_alreadyWin;
}

void Board::returnState()
{
    m_lastNumber = 0;
    m_board = m_originalBoard;
    m_alreadyWin = false;
}

int Board::answer()
{
    int unmarkedSum = 0;
    for (int i = 0; i < m_originalBoard.size(); ++i)
    {
        if(m_board[i] != -1)
        {
            unmarkedSum += m_originalBoard[i];
        }
    }

    return unmarkedSum * m_lastNumber;
}