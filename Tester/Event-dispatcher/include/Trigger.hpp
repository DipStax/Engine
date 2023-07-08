#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "Event.hpp"


template<class T>
concept IsIEvent = std::is_base_of<tester::IEvent, T>::value;

namespace tester
{
    template<IsIEvent T>
    class Trigger
    {
        public:
            using Task = std::function<void(const T &)>;

            Trigger() = default;
            ~Trigger() = default;

            void raise(const T &_event);

            [[nodiscard]] std::shared_ptr<Task> subscribe(Task _task);
            void unsubscribe(const std::shared_ptr<Task> _task);

        private:
            std::vector<std::shared_ptr<Task>> m_sub;
    };

    template<IsIEvent T>
    using Task = std::shared_ptr<std::function<void(const T &)>>;
}


#include "Trigger.inl"