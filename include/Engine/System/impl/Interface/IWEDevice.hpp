#pragma once

#include <windows.h>

#include "Engine/Event/Event.hpp"
#include "Engine/System/impl/Interface/IWindowEvent.hpp"

namespace eng::impl
{
    class IWEDevice : public IWindowEvent
    {
        protected:
            virtual void onFocus(Event _event) = 0;
            virtual void onMouseButton(Event _event) = 0;
            virtual void onMouseMove(Event _event) = 0;
            virtual void onKeyboard(Event _event) = 0;
            virtual void onResize(Event _event) = 0;
    };
}
