#pragma once

#include <string>
#include <vector>

#include "Tool/Export.hpp"

namespace split
{
    PROJECT_API std::pair<std::string, std::string> noSpace(const std::string &_str, char _c);
    PROJECT_API std::pair<std::string, std::string> standard(const std::string &_str, char _c);
    PROJECT_API std::vector<std::string> multiple(const std::string &_str, char _c, bool _nsp = false);
}