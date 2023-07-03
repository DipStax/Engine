#include "Engine/Event/EventHub.hpp"

namespace eng
{
    template<IsEvent ...TEvent>
    template<IsEvent T, class ...Ts>
    void EventHubImpl<TEvent...>::Raise(const Ts &&..._args)
    {
        T &ref = std::get<T>(m_event);

        for (auto &_fun : ref.m_func)
            m_tp.enqueue([_fun, _args] () {
                (*_fun)(std::forward<Ts>(_args)...);
            });
    }

    template<IsEvent ...TEvent>
    template<IsEvent T, class ...Ts>
    bool EventHubImpl<TEvent...>::Sub(Event<Ts...>::FPtr _func)
    {
        T &ref = std::get<T>(m_event);

        if (!ref.m_func.contains(_func)) {
            ref.m_func.push_back(_func)
            return true;
        }
        return false;
    }

    template<IsEvent ...TEvent>
    template<IsEvent T, class ...Ts>
    bool EventHubImpl<TEvent...>::Unsub(Event<Ts...>::FPtr _func)
    {
        T &ref = std::get<T>(m_event);

        if (ref.m_func.contains(_func)) {
            ref.m_func.erase(_func);
            return true;
        }
        return false;
    }
}