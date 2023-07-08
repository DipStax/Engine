#pragma once

#include "Event.hpp"
#include "Trigger.hpp"
#include "TriggerMap.hpp"

namespace tester
{
    class EventPool
    {
        public:
            template<IsIEvent T>
            static bool Raise(const T &_event);

            template<IsIEvent T>
            static Task<T> Subscribe(Trigger<T>::Task _task);
            template<IsIEvent T>
            static void Unsubscribe(Task<T> _task);

        private:
            inline static TriggerMap<Trigger, EventList> m_map;
    };
}

#include "EventPool.inl"