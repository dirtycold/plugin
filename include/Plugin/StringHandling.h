#pragma once

#include <vector>
#include <string>
#include <sstream>

// trimming

/*
 * derived from
 *
 * 1. http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 *    by Evan Teran
 *
 * and
 *
 * 2. http://stackoverflow.com/questions/479080/trim-is-not-part-of-the-standard-c-c-library
 *    by BobbyShaftoe
 *
 */

static const std::string whiteSpaces( " \f\n\r\t\v" );

// trim from start
static inline std::string &ltrim(std::string &s)
{
    s.erase(0 , s.find_first_not_of(whiteSpaces));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s)
{
    s.erase(s.find_last_not_of(whiteSpaces) + 1);
    return s;
}

// trim from both ends
static inline std::string trim(const std::string &s) {
    std::string t (s);
    return ltrim(rtrim(t));
}

// splitting

static inline std::vector<std::string> split(const std::string &s, char d)
{
    std::vector<std::string> list;
    std::istringstream stream(s);
    std::string line;

    while (std::getline(stream,line,d))
    {
        line = trim(line);
        if (!line.empty())
        {
            list.push_back(line);
        }
    }
    return list;
}
