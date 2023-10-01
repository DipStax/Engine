#pragma once

#include "Engine/System/Mouse.hpp"
#include "Engine/System/Key.hpp"

namespace eng
{
    struct PROJECT_API Event
    {
        class Focus
        {
            public:
                bool state = false;
        };

        class MouseButton
        {
            public:
                Mouse::State state = Mouse::State::Neutral;
                Mouse::Button button = Mouse::Button::Other;
        };

        class MouseMove
        {
            public:
                int32_t x = 0;
                int32_t y = 0;
        };

        class Keyboard
        {
            public:
                Key key = Key::Other;
                KeyState state = KeyState::Up;
                KeyState control = KeyState::Up;
                KeyState alt = KeyState::Up;
                KeyState shift = KeyState::Up;
                KeyState system = KeyState::Up;
        };

        class Resize
        {
            public:
                uint32_t height = 0;
                uint32_t width = 0;
        };

        enum class Type
        {
            Focus,
            MouseButton,
            MouseMove,
            KeyBoard,
            Resize,
        };

        Type type;

        union
        {
            MouseButton mouseButton;
            MouseMove mouseMove;
            Keyboard keyboard;
            Focus focus;
            Resize resize;
        };
    };
}