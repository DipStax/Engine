#ifndef ECS_SYS_ISYSTEM_HPP
#define ECS_SYS_ISYSTEM_HPP

#include <SFML/Graphics.hpp>

#include "ECS/Component/Component.hpp"
#include "ECS/Register.hpp"
#include "ECS/Entity.hpp"
#include "Engine/Window.hpp"

namespace ecs
{
    using MainRegister = Register<Entity::IdType, Component>;

    namespace sys
    {
        class ISystem
        {
            public:
                virtual void run(MainRegister &_reg, Entity *_entity, eng::Window *_window) = 0;
        };
    }
}

#endif