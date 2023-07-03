#include "ECS/Entity.hpp"

namespace ecs
{
    void Entity::kill()
    {
        Alive = false;
    }

    bool Entity::operator<(const Entity &_entity) const
    {
        return Id < _entity.Id;
    }

    Entity::Entity(size_t _id)
        : Id(_id)
    {
    }
}