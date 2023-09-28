#pragma once

#include "Tool/Export.hpp"

namespace eng
{
    struct PROJECT_API IEvent
    {};

    class PROJECT_API Mouse
    {
        public:
            enum class Button {
                Left,
                Right,
                Middle
            };
    };

    class PROJECT_API Event : public IEvent
    {
        public:
            struct MouseButtonEvent {
                bool press;
                Mouse::Button button;
            };

            struct ResizeEvent {
                uint32_t height;
                uint32_t width;
            };

            enum class Type
            {
                MouseButton
            };

            Type type;

            union
            {
                MouseButtonEvent mouseButton;
                ResizeEvent resize;
            };
    };
}