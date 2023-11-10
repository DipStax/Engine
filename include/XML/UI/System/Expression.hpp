#pragma once

#include "Engine/Event/Event.hpp"
#include "Engine/Event/EventPool.hpp"

namespace eng::ui
{
    using SysEventPool = EventPool<Event::Focus, Event::MouseButton, Event::MouseMove,
                                   Event::Keyboard, Event::Resize, Event::Type>;
}