#pragma once

#include <string>

#include "Tool/Export.hpp"

namespace eng::xml
{
    struct PROJECT_API Token
    {
        enum Type
        {
           Open = 01,
           Close = 010,
           CloseSign = 0100,
           Equal = 01000,
           Word = 010000,
           LWord = 0100000
        };

        Type type;
        std::string value;
    };
}