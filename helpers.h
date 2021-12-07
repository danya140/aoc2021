#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

inline std::vector<std::string> split(const std::string& str, char delimiter)
{
    std::vector<std::string> result;

    auto position = str.find(delimiter);
    int i = 0;

    while (position != std::string::npos)
    {
        auto substr = str.substr(i, position - i);
        if (!substr.empty())
        {
            result.push_back(substr);
        }
        i = position + 1;

        position = str.find(delimiter, i);
    }

    std::string last = str.substr(i, std::min(position, str.size()) - i + 1);
    if(!last.empty())
    {
        result.push_back(last);
    }

    return result;
}

template <class T>
inline std::string vector2String(const std::vector<T>& input)
{
    std::stringstream stream;
    std::copy(input.begin(), input.end(), std::ostream_iterator<T>(stream, ""));

    return stream.str();
}