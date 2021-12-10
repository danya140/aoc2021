#include "../helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <numeric>
#include <cmath>
#include <map>

const char FILE_NAME[] = "input.txt";


std::vector<std::string> readNumbers()
{
    std::ifstream file(FILE_NAME);
    std::vector<std::string> inputData;

    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            inputData.push_back(line);
        }
    }

    return inputData;
}

/**
 * Validate line by checking if all brackets correctly closed
 * @return 0 if everything ok
 *         -1 if line have not closed brackets
 *         bracket first invalid bracket
 */
char validateLine(const std::string& line)
{
    std::vector<char> openBrackets;

    static std::map<char, char> oppositeBracket
        {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'},
            {'<', '>'},
        };

    for (const auto& bracket : line)
    {
        switch (bracket)
        {
            case '{':
            case '(':
            case '[':
            case '<':
                openBrackets.push_back(bracket);
                break;
            case '}':
            case ')':
            case ']':
            case '>':
                if(oppositeBracket[openBrackets[openBrackets.size() - 1]] == bracket)
                {
                    openBrackets.pop_back();
                }
                else
                {
                    return bracket;
                }

                break;
        }
    }

    if (!openBrackets.empty())
    {
        return -1; //incomplete
    }

    return 0;
}

std::vector<char> completer(const std::string& line)
{
    std::vector<char> openBrackets;

    static std::map<char, char> oppositeBracket
        {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'},
            {'<', '>'},
        };

    for (const auto& bracket : line)
    {
        switch (bracket)
        {
            case '{':
            case '(':
            case '[':
            case '<':
                openBrackets.push_back(bracket);
                break;
            case '}':
            case ')':
            case ']':
            case '>':
                if(oppositeBracket[openBrackets[openBrackets.size() - 1]] == bracket)
                {
                    openBrackets.pop_back();
                }
                break;
        }
    }
    std::vector<char> completion;
    auto it = openBrackets.end();
    while (it != openBrackets.begin())
    {
        --it;

        completion.push_back(oppositeBracket[*it]);
    }

    return completion;
}

/**
 * Calculate score for completion char sequence
 */
long long int completionScore(const std::vector<char>& completion)
{
    static std::map<char, int> score
        {
            {')', 1},
            {']', 2},
            {'}', 3},
            {'>', 4}
        };

    long long int totalScore = 0;

    for (const auto& bracket : completion)
    {
        totalScore *= 5;
        totalScore += score[bracket];
    }

    return totalScore;
}

/**
 * Part 1
 */
void validateInput(const std::vector<std::string>& input)
{
    static std::map<char, int> score
        {
            {')', 3},
            {']', 57},
            {'}', 1197},
            {'>', 25137}
        };

    std::vector<char> invalidCharacters;

    for (const auto& line : input)
    {
        char valid = validateLine(line);
        if (valid > 0)
        {
            invalidCharacters.push_back(valid);
        }
    }

    int totalScore = 0;
    for (const auto& invalidChar : invalidCharacters)
    {
        totalScore += score[invalidChar];
    }

    std::cout << "Invalid score is: " << totalScore << "\n";
}

/**
 * Part 2
 */
void completeInput(const std::vector<std::string>& input)
{
    std::vector<std::string> incompleteLines;

    for (const auto& line : input)
    {
        char valid = validateLine(line);
        if (valid == -1)
        {
            incompleteLines.push_back(line);
        }
    }

    std::vector<long long int> completionScores;
    for (const auto& incompleteLine : incompleteLines)
    {
        completionScores.push_back(completionScore(completer(incompleteLine)));
    }
    std::sort(completionScores.begin(), completionScores.end());

    std::cout << "Middle score: " << completionScores[completionScores.size()/2] << "\n";
}

int main()
{
    std::vector<std::string> inputNumbers = readNumbers();

    validateInput(inputNumbers);
    completeInput(inputNumbers);

    return 0;
}
