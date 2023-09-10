#pragma once

#include "Engine/Container/TriggerMap.hpp"
#include "Engine/Event/Event.hpp"
#include "Engine/Event/Trigger.hpp"
#include "Tool/PreProcessing.hpp"

namespace eng
{
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
            TriggerMap<Trigger, tuple_unpacked<Ts...>> m_map;
    };
}

#include "EventPool.inl"