#pragma once

namespace tester
{
    class Mouse
    {
        public:
            enum class Button {
                Left,
                Right,
                Middle
            };
    };

    class Event
    {
        public:
            struct MouseButtonEvent {
                bool press;
                Mouse::Button button;
            };

            enum class Type
            {
                MouseButton
            };

            Type type;

            union
            {
                MouseButtonEvent mouseButton;
            };
    };
}