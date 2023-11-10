#pragma once

#include "Engine/Event/EventPool.hpp"

namespace eng::ui
{
    template<class ...Ts>
    class EventObject : public EventPool<Ts...>, public SysEventPool
    {
        public:
            EventObject(ThreadPool &_tp);
            ~EventObject() = default;

        protected:
            EventPool<Ts...> *customEP();
            SysEventPool *systemEP();
    };
}

#include "XML/UI/EventObject.inl"