#ifndef ECS_COMP_ARITHMETIC_HPP
#define ECS_COMP_ARITHMETIC_HPP

#include "Engine/Maths/Point3.hpp"

namespace ecs::comp
{
    struct Position : public eng::Point3<float>
    {
    };

    struct Velocity : public eng::Point3<float>
    {
    };

    struct Rotation : public eng::Point3<float>
    {
    };
}

#endif