#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "Engine/Event/Event.hpp"
#include "Engine/System/ThreadPool.hpp"

namespace eng
{
    template<class T>
    class Trigger
    {
        public:
            using Task = std::function<void(const T&)>;
            using sTask = std::shared_ptr<std::function<void(const T&)>>;

            Trigger(ThreadPool &_tp);
            ~Trigger() = default;

            void raise(const T &_event);

            [[nodiscard]] sTask subscribe(Task _task);
            void unsubscribe(const sTask _task);

        private:
            std::vector<sTask> m_sub;

            ThreadPool &m_tp;
    };
}


#include "Trigger.inl"