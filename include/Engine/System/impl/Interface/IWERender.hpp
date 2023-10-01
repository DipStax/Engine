#pragma once

#include "Engine/Event/Event.hpp"
#include "Engine/System/impl/Interface/IWindowEvent.hpp"

namespace eng::impl
{
    template<class T>
    class IWERender : public IWindowEvent<T>
    {
        public:
            virtual void display() = 0;

        protected:
            virtual void onDraw(Event _event) = 0;
    };
}