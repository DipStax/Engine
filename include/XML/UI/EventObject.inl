#include "XML/UI/EventObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    EventObject<std::tuple<Ts...>>::EventObject(ThreadPool &_tp)
        : EventPool<Ts>(_tp)...
    {
    }

    template<class ...Ts>
    EventObject<std::tuple<Ts...>>::EventObject(EventObject<std::tuple<Ts...>> &&_eo) noexcept
        : EventPool<Ts>(std::move(_eo))...
    {
    }
}