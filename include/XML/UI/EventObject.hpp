#pragma once

#include "Engine/Event/EventPool.hpp"
#include "XML/UI/Object.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class EventObject : public EventPool<Ts>..., public Object
    {
        public:
            EventObject(ThreadPool &_tp);
            EventObject(EventObject &&_eo) noexcept;
            ~EventObject() = default;
    };
}

#include "XML/UI/EventObject.inl"