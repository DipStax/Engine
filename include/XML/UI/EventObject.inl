#include "XML/UI/EventObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    EventObject<Ts...>::EventObject(ThreadPool &_tp)
        : EventPool<Ts...>(_tp)
    {
    }

    // template<class ...Ts>
    // EventObject<Ts...>::EventObject(EventObject<Ts...> &&_eo) noexcept
    //     : EventPool<Ts...>(std::move(_eo))
    // {
    // }

    template<class ...Ts>
    EventPool<Ts...> *EventObject<Ts...>::customEP()
    {
        return this;
    }

    template<class ...Ts>
    SysEventPool *EventObject<Ts...>::systemEP()
    {
        return this;
    }
}