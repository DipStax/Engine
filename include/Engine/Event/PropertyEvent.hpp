#pragma once

#include <string>
#include <any>

#include "Engine/Event/Event.hpp"

namespace eng
{
    struct PropertyEvent : public IEvent
    {
        const std::string &name;
        const std::any value;
    };
}