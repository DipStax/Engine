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
        if (m_map.template contains<T>()) {
            m_map.template at<T>().raise(_event);
            return true;
        }
        return false;
    }

    template<class ...Ts>
    template<class T>
    Trigger<T>::sTask EventPool<Ts...>::subscribe(Trigger<T>::Task _task)
    {
        std::cout << "Event::Subscribe" << std::endl;
        return m_map.template at<T>().subscribe(_task);
    }

    template<class ...Ts>
    template<class T>
    void EventPool<Ts...>::unsubscribe(Trigger<T>::sTask _task)
    {
        std::cout << "Event::Unsubscribe" << std::endl;
        if (m_map.template contains<T>())
            m_map.template at<T>().unsubscribe(_task);
    }
}