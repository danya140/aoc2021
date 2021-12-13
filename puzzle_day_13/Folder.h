#pragma once

#include "../helpers.h"


class Folder
{
public:
    Folder(const std::vector<std::string>& points, const std::vector<std::string>& commands);

    /**
     * Perform next command
     */
    void performCommand();

    /**
     * Perform all commands
     */
    void performAll();

    /**
     * Pretty printer for field
     */
    void print();

    /**
     * Count dots on field
     */
    int countDots();

private:
    /**
     * Fold field at @a x by x axis
     */
    void foldX(int x);

    /**
     * Fold field at @a y by y axis
     */
    void foldY(int y);

private:
    std::vector<std::vector<char>> m_field;

    std::vector<std::pair<char, int>> m_commands;
    int m_lastCommand;
};


