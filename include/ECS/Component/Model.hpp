#ifndef ECS_COMP_MODEL_HPP
#define ECS_COMP_MODEL_HPP

#include <cstdint>

#include "Engine/Rendering/Model.hpp"

namespace ecs::comp
{
    struct Model
    {
        eng::Model mod;
    };
}

#endif