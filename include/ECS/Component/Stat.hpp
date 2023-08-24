#pragma once

#include "Tool/Export.hpp"

namespace ecs::comp
{
    using StatType = size_t;

    struct PROJECT_API Stat
    {
        StatType Health;
        StatType Mana;
        StatType Power;
        StatType Stamina;
    };
}