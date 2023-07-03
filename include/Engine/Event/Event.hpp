#ifndef ENG_EVT_EVENT_HPP
#define ENG_EVT_EVENT_HPP

#include "Tool/PreProcessing.hpp"

namespace eng
{
    template<IsEvent ...TEvent>
    class EventHubImpl;

    template<class ...Ts>
    class Event
    {
        public:
            template<class ...TEvent>;
            friend EventHubImpl;

            ~Event() = default;

            using FPtr = void (*)(const Ts &&...);

        private:
            Event() = default;

            std::vector<FPtr> m_func;
    };
}

#endif