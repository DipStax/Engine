#pragma once

#include <string>
#include <any>

#include "Engine/Event/Event.hpp"

namespace eng
{
    struct PropertyEvent
    {
        const std::string &name;
        std::any value;
    };
}