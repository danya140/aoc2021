#pragma once

#include <vector>
#include <string>

const int BOARD_ROW_LIMIT = 5;

class Board
{
public:
    explicit Board(const std::string& board);

    bool crossNumber(int number);

    bool isWin();

    int answer();

    void setWin();
    bool alreadyWin();
    void returnState();

private:
    std::vector<int> m_board;
    std::vector<int> m_originalBoard;

    int m_lastNumber = 0;
    bool m_alreadyWin = false;
};


