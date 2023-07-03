#include "ECS/Manager.hpp"

namespace ecs
{
    Entity::IdType Manager::spawn()
    {
        static Entity::IdType id = 1;

        m_entity.push_back(Entity(id));
        m_register.add(id);
        return id++;
    }

    void Manager::kill(Entity::IdType _id)
    {
        std::erase_if(m_entity, [_id] (const Entity &_ientity) {
            return _ientity.Id == _id;
        });
        m_register.pop(_id);
    }

    void Manager::kill(const Entity &_entity)
    {
        std::erase_if(m_entity, [_entity] (const Entity &_ientity) {
            return _ientity.Id == _entity.Id;
        });
        m_register.pop(_entity.Id);
    }

    Component& Manager::get(Entity::IdType _id)
    {
        return m_register.at(_id);
    }
}