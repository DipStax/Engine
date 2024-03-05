#pragma once

#include <cstddef>

#include "Tool/Export.hpp"

namespace ecs
{
    class PROJECT_API Entity
    {
        friend class Manager;

        public:
            using IdType = size_t;

            ~Entity() = default;

            IdType Id = 0;
            bool Alive = true;

            void kill();

            bool operator<(const Entity &_entity) const;
        private:
            Entity(size_t _id);
    };
}