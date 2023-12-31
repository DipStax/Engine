#pragma once

#include <functional>
#include <vector>

#include "ECS/Component/Component.hpp"
#include "ECS/System/System.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Register.hpp"
#include "Engine/Rendering/RenderTarget.hpp"

namespace ecs
{
    class PROJECT_API Manager
    {
        public:
            Manager() = default;
            ~Manager() = default;

            template<SystemType T>
            void runSystem(Entity *_entity = nullptr, eng::RenderTarget *_target = nullptr);

            Entity::IdType spawn();
            void kill(Entity::IdType _id);
            void kill(const Entity &_entity);

            template<class T>
            using FnFind = std::function<bool(const std::optional<T> &)>;

            template<class T>
            Entity::IdType find(FnFind<T> _fun);
            Component &get(Entity::IdType _id);

        private:
            std::vector<Entity> m_entity;
            Register<Entity::IdType, Component> m_register;
            System m_system;
    };
}

#include "ECS/Manager.inl"