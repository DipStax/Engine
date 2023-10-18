#pragma once

#include "Engine/System/impl/Windows/EventPack.hpp"
#include "Engine/System/impl/Interface/IWEDevice.hpp"

#include "Tool/Export.hpp"

namespace eng::impl::win
{
    class PROJECT_API WEDevice : public IWEDevice
    {
        protected:
            WEDevice() = default;
            ~WEDevice() = default;

            [[nodiscard]] bool handle(const EventPack &_ep);

            virtual void onFocus(Event _event);
            virtual void onMouseButton(Event _event);
            virtual void onMouseMove(Event _event);
            virtual void onKeyboard(Event _event);
            virtual void onResize(Event _event);

        private:
            bool handleEvent(const EventPack &_ep);

            bool focusEvent(const EventPack &_ep);
            bool mouseButtonEvent(const EventPack &_ep);
            bool mouseMoveEvent(const EventPack &_ep);
            bool keyboardEvent(const EventPack &_ep);
            bool resizeEvent(const EventPack &_ep);
    };
}