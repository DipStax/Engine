#ifndef TOOL_SPLITTER_HPP
#define TOOL_SPLITTER_HPP

#include <string>
#include <vector>

namespace split
{
    std::pair<std::string, std::string> noSpace(const std::string &_str, char _c);
    std::pair<std::string, std::string> standard(const std::string &_str, char _c);
    std::vector<std::string> multiple(const std::string &_str, char _c, bool _nsp = false);
}

#endif