#pragma once

#include "Engine/System/Mouse.hpp"

namespace eng
{
    struct PROJECT_API IEvent
    {};

    class PROJECT_API Event : public IEvent
    {
        public:
            struct MouseButton {
                Mouse::State state;
                Mouse::Button button;
            };

            struct Resize {
                uint32_t height;
                uint32_t width;
            };

            enum class Type
            {
                MouseButton,
                KeyBoard,
                Resize,
            };

            Type type;

            union
            {
                MouseButton mouse;
                Resize resize;
            };
    };
}