#include <iostream>

#include "Engine/Event/EventPool.hpp"

namespace eng
{
    template<class ...Ts>
    EventPool<Ts...>::EventPool(ThreadPool& _tp)
        : m_map(_tp)
    {
    }

    template<class ...Ts>
    template<class T>
    bool EventPool<Ts...>::raise(const T &_event)
    {
        if (m_map.contains<T>()) {
            m_map.at<T>().raise(_event);
            return true;
        }
        return false;
    }

    template<class ...Ts>
    template<class T>
    Trigger<T>::sTask EventPool<Ts...>::subscribe(Trigger<T>::Task _task)
    {
        return m_map.at<T>().subscribe(_task);
    }

    template<class ...Ts>
    template<class T>
    void EventPool<Ts...>::unsubscribe(Trigger<T>::sTask _task)
    {
        if (m_map.contains<T>())
            m_map.at<T>().unsubscribe(_task);
    }
}