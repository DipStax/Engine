#pragma once

#include "Engine/Container/TriggerMap.hpp"
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

            template<class T>
            bool raise(const T &_event);

            template<class T>
            Trigger<T>::sTask subscribe(Trigger<T>::Task _task);
            template<class T>
            void unsubscribe(Trigger<T>::sTask _task);

        private:
           TriggerMap<Trigger, typename tuple_unpacked<Ts...>::type> m_map;
    };
}

#include "EventPool.inl"