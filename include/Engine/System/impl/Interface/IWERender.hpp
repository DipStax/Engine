#pragma once

#include "Engine/Event/Event.hpp"
#include "Engine/System/impl/Interface/IWindowEvent.hpp"

namespace eng::impl
{
    class IWERender : public IWindowEvent
    {
        public:
            virtual void display() = 0;

        protected:
            virtual void onDraw(Event _event) = 0;
    };
}