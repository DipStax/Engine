#include "Engine/Event/Trigger.hpp"
#include "Engine/System/ThreadPool.hpp"

namespace eng
{
    template<class T>
    Trigger<T>::Trigger(ThreadPool& _tp)
        : m_tp(_tp)
    {
    }

    template<class T>
    void Trigger<T>::raise(const T &_event)
    {
        for (auto &_sub : m_sub)
            m_tp.enqueue([_sub, _event] () {
                (*_sub)(_event);
            });
    }

    template<class T>
    Trigger<T>::sTask Trigger<T>::subscribe(Task _task)
    {
        m_sub.push_back(std::make_shared<Task>(_task));
        return m_sub.back();
    }

    template<class T>
    void Trigger<T>::unsubscribe(const sTask _task)
    {
        std::erase_if(m_sub, [_task] (const sTask _ctask) {
            return _task == _ctask;
        });
    }
}