#ifndef ECS_ENTITY_HPP
#define ECS_ENTITY_HPP

namespace ecs
{
    class Entity
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

#endif