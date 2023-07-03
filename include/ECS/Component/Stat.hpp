#ifndef ECS_COMP_STAT_HPP
#define ECS_COMP_STAT_HPP

namespace ecs::comp
{
    using StatType = size_t;

    struct Stat
    {
        StatType Health;
        StatType Mana;
        StatType Power;
        StatType Stamina;
    };
}

#endif