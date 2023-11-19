#pragma once

#include "Engine/Event/Event.hpp"

namespace eng::ui::evt
{
    using Click = Event::MouseButton;

    struct Display
    {
        Point2<uint32_t> size;
    };
}