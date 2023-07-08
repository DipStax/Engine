#include "Trigger.hpp"
#include "ThreadPool.hpp"

namespace tester
{
    template<IsIEvent T>
    void Trigger<T>::raise(const T &_event)
    {
        for (auto &_sub : m_sub)
            ThreadPool::enqueue([_sub, _event] () {
                (*_sub)(_event);
            });
    }

    template<IsIEvent T>
    std::shared_ptr<typename Trigger<T>::Task> Trigger<T>::subscribe(Task _task)
    {
        m_sub.push_back(std::make_shared<Task>(_task));
        return m_sub.back();
    }

    template<IsIEvent T>
    void Trigger<T>::unsubscribe(const std::shared_ptr<Task> _task)
    {
        std::erase_if(m_sub, [_task] (const std::shared_ptr<Task> _ctask) {
            return _task == _ctask;
        });
    }
}