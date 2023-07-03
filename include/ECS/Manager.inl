#include "ECS/Manager.hpp"

namespace ecs
{
    template<SystemType T>
    void Manager::runSystem(Entity *_entity, eng::Window *_win)
    {
        std::get<T>(m_system).run(m_register, _entity, _win);
    }

    template<class T>
    Entity::IdType Manager::find(FnFind<T> _fun)
    {
        for (auto &[_key, _val] : m_register)
            if (_fun(opt::get<T>(_val)))
                return _key;
        return 0;
    }
}