#pragma once

#include "Engine/Event/EventPool.hpp"
#include "XML/UI/BaseObject.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class EventObject;

    template<class ...Ts>
    class EventObject<std::tuple<Ts...>> : public EventPool<Ts>...
    {
        public:
            EventObject(ThreadPool &_tp);
            EventObject(EventObject &&_eo) noexcept;
            ~EventObject() = default;
    };
}

#include "XML/UI/EventObject.inl"