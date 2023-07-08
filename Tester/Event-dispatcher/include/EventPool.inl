#include <iostream>

#include "EventPool.hpp"

namespace tester
{
    template<IsIEvent T>
    bool EventPool::Raise(const T &_event)
    {
        if (m_map.contains<T>()) {
            m_map.at<T>().raise(_event);
            return true;
        }
        return false;
    }

    template<IsIEvent T>
    Task<T> EventPool::Subscribe(Trigger<T>::Task _task)
    {
        std::cout << "Event::Subscribe" << std::endl;
        return m_map.at<T>().subscribe(_task);
    }

    template<IsIEvent T>
    void EventPool::Unsubscribe(Task<T> _task)
    {
        std::cout << "Event::Unsubscribe" << std::endl;
        if (m_map.contains<T>())
            m_map.at<T>().unsubscribe(_task);
    }
}