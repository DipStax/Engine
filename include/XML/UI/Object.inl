#include "XML/UI/Object.hpp"

namespace eng::ui
{
    template<class ...Ts>
    Object<Ts...>::Object(EventPool<Ts...> &_ep_cus, SysEventPool &_ep_sys, const std::string &_name, ThreadPool &_tp)
        : EventObject<Ts...>(_tp), PropertyObject<Ts...>(*this), ContainerObject<Ts...>(*this, *this, _tp),
          PropertyObject<Ts...>(_ep_cus), m_name(_name)
    {
        bindEventPool<SysEventType>(_ep_sys);
        bindEventPool<Ts...>(_ep_cus);
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    void Object<Ts...>::transferEvent(const T &_event)
    {
        raise<T>(_event, m_bind_cus.get<T>());
    }

    template<class ...Ts>
    template<class T, class ..._Ts>
    requires ContainIn<T, Ts...>
    void Object<Ts...>::bindEventPool(EventPool<Ts...> &_ep_cus)
    {
        m_bind_cus.add<T>(_ep_cus.tempalte subscribe<T>(Object<Ts...>::transferEvent<T>, *this));
        bindEventPool<_Ts...>(_ep_cus);
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    void Object<Ts...>::bindEventPool(EventPool<Ts...> &_ep_cus)
    {
        m_bind_cus.add<T>(_ep_cus.tempalte subscribe<T>(Object<Ts...>::transferEvent<T>, *this));
    }

    template<class ...Ts>
    template<class T, class ..._Ts>
    requires ContainIn<T, SysEventType>
    void Object<Ts...>::bindEventPool(EventPool<T, Ts...> &_ep_sys)
    {
        m_bind_sys.add<T>(_ep_cus.tempalte subscribe<T>(Object<Ts...>::transferEvent<T>, *this));
        bindEventPool<_Ts...>(_ep_sys);
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    void Object<Ts...>::bindEventPool(EventPool<Ts...> &_ep_cus)
    {
        m_bind_sys.add<T>(_ep_sys.tempalte subscribe<T>(Object<Ts...>::transferEvent<T>, *this));
    }
}