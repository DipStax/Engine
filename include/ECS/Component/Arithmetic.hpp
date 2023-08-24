#pragma once

#include "Engine/Maths/Point3.hpp"

namespace ecs::comp
{
    struct PROJECT_API Velocity : public eng::Point3<float>
    {
    };

    struct PROJECT_API Position : public eng::Point3<float>
    {
    };

    struct PROJECT_API Rotation : public eng::Point3<float>
    {
    };
}