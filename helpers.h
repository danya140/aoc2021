#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

std::vector<std::string> split(const std::string& str, char delimiter)
{
    std::vector<std::string> result;

    auto position = str.find(delimiter);
    int i = 0;

    while (position != std::string::npos)
    {
        result.push_back(str.substr(i, position - i));
        i = position + 1;

        position = str.find(delimiter, i);
    }

    result.push_back(str.substr(i, std::min(position, str.size()) - i + 1));

    return result;
}

template <class T>
std::string vector2String(const std::vector<T>& input)
{
    std::stringstream stream;
    std::copy(input.begin(), input.end(), std::ostream_iterator<T>(stream, ""));

    return stream.str();
}