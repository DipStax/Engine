#include <iostream>

#include "EventPool.hpp"

namespace tester
{
    template<class ...Ts>
    EventPool<Ts...>::EventPool(ThreadPool& _tp)
        : m_map(_tp)
    {
    }

    template<class ...Ts>
    template<IsIEvent T>
    bool EventPool<Ts...>::raise(const T &_event)
    {
        if (m_map.contains<T>()) {
            m_map.at<T>().raise(_event);
            return true;
        }
        return false;
    }

    template<class ...Ts>
    template<IsIEvent T>
    Trigger<T>::sTask EventPool<Ts...>::subscribe(Trigger<T>::Task _task)
    {
        std::cout << "Event::Subscribe" << std::endl;
        return m_map.at<T>().subscribe(_task);
    }

    template<class ...Ts>
    template<IsIEvent T>
    void EventPool<Ts...>::unsubscribe(Trigger<T>::sTask _task)
    {
        std::cout << "Event::Unsubscribe" << std::endl;
        if (m_map.contains<T>())
            m_map.at<T>().unsubscribe(_task);
    }
}