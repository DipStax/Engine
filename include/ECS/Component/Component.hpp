#ifndef ECS_COMP_COMPONENT_HPP
#define ECS_COMP_COMPONENT_HPP

#include <tuple>

#include "ECS/Component/Arithmetic.hpp"
#include "ECS/Component/Id.hpp"
#include "ECS/Component/Model.hpp"
#include "ECS/Component/Stat.hpp"

namespace ecs
{
    using Component = Tuple<
            comp::Stat, comp::Position, comp::Rotation, comp::Id, comp::Velocity,
            comp::Model
        >;
}

#endif