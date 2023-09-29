#pragma once

#include "Engine/System/Mouse.hpp"

namespace eng
{
    struct PROJECT_API Event
    {
        struct MouseButton
        {
            Mouse::State state = Mouse::State::Neutral;
            Mouse::Button button = Mouse::Button::Other;
        };

        struct Resize
        {
            uint32_t height = 0;
            uint32_t width = 0;
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