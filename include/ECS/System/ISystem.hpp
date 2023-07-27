#ifndef ECS_SYS_ISYSTEM_HPP
#define ECS_SYS_ISYSTEM_HPP

#include "ECS/Component/Component.hpp"
#include "ECS/Register.hpp"
#include "ECS/Entity.hpp"
#include "Engine/Rendering/RenderWindow.hpp"

namespace ecs
{
    using MainRegister = Register<Entity::IdType, Component>;

    namespace sys
    {
        class ISystem
        {
            public:
                virtual void run(MainRegister &_reg, Entity *_entity, eng::RenderWindow *_window) = 0;
        };
    }
}

#endif