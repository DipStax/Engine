#pragma once

#include "Event.hpp"
#include "Trigger.hpp"
#include "TriggerMap.hpp"

namespace eng
{
    // check for tuple inside of ts
    template<class ...Ts>
    class EventPool
    {
        public:
            EventPool(ThreadPool &_tp);
            ~EventPool() = default;

            template<IsIEvent T>
            bool raise(const T &_event);

            template<IsIEvent T>
            Trigger<T>::sTask subscribe(Trigger<T>::Task _task);
            template<IsIEvent T>
            void unsubscribe(Trigger<T>::sTask _task);

        private:
            TriggerMap<Trigger, std::tuple<Ts...>> m_map;
    };
}

#include "EventPool.inl"