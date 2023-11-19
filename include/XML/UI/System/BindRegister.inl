#include "XML/UI/System/BindRegister.hpp"

namespace eng::ui
{
    template<class ...Ts>
    BindRegister<Ts...>::~BindRegister()
    {
        clear();
    }

    template<class ...Ts>
    template<class T, class ..._Ts>
    requires ContainIn<T, Ts...>
    size_t BindRegister<Ts...>::add(Property<T> &_prop, fn_bind<T> _bind, _Ts ...&&_binds)
    {
        add(_prop, _bind);
        add(_prop, _binds);
     

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    size_t BindRegister<Ts...>::add(Property<T> &_prop, fn_bind<T> _bind)
    {
        add<T>(_bind(_prop));
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    size_t BindRegister<Ts...>::add(std::shared_ptr<T> _bind)
    {
        m_bind.set(m_bind.get<T>().push_back(_bind));
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    size_t BindRegister<Ts...>::get()
    {
        return m_bind.get<T>();
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    bool BindRegister<Ts...>::del(std::shared_ptr<T> _bind)
    {
        std::vector<std::shared_ptr<T>> vec = get<T>();

        std::erase_if(vec.begin(), vec.end(), [_bind] (const std::shared_ptr<T> &_task) {
            return _bind == _task;
        })
        m_bind.set<T>(vec);
    }

    template<class ...Ts>
    void BindRegister<Ts...>::clear()
    {
        clear<Ts...>();
    }

    template<class ...Ts>
    template<class T, class ..._Ts>
    requires ContainIn<T, Ts...>
    void BindRegister<Ts...>::clear()
    {
        clear<T>();
        clear<Ts...>();
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    void BindRegister<Ts...>::clear()
    {
        m_bind.set<T>({});
    }
}