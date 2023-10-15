#pragma once

#include "Engine/Container/TriggerMap.hpp"
#include "Engine/Event/Event.hpp"
#include "Engine/Event/Trigger.hpp"

namespace eng
{
    // check for tuple inside of ts
    template<class ...Ts>
    class EventPool
    {
        public:
            EventPool(ThreadPool &_tp);
            EventPool(EventPool<Ts...> &&_ep) noexcept;
            ~EventPool() = default;

            template<class T>
            requires ContainIn<T, Ts...>
            bool raise(const T &_event);

            template<class T>
            requires ContainIn<T, Ts...>
            Trigger<T>::sTask subscribe(Trigger<T>::Task _task);
            template<class T>
            requires ContainIn<T, Ts...>
            void unsubscribe(Trigger<T>::sTask _task);

        private:
            TriggerMap<Trigger, std::tuple<Ts...>> m_map;
    };
}

#include "EventPool.inl"