#ifndef ENG_EVT_EVENTHUB_HPP
#define ENG_EVT_EVENTHUB_HPP

#include <vector>

#include "Engine/Event/Event.hpp"
#include "Engine/ThreadPool.hpp"

namespace eng
{
    template<IsEvent ...TEvent>
    class EventHubImpl
    {
        public:
            template<IsEvent T, class ...Ts>
            static void Raise(const Ts &&..._args);

            template<IsEvent T, class ...Ts>
            static bool Sub(Event<Ts...>::FPtr _func);
            template<IsEvent T, class ...Ts>
            static bool Unsub(Event<Ts...>::FPtr _func);

        private:
            static ThreadPool<5> m_tp{ true };
            inline static std::tuple<TEvent...> m_event;
    };
}

#endif