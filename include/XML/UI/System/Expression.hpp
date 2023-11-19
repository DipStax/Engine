#pragma once

#include "Engine/Event/Event.hpp"
#include "Engine/Event/EventPool.hpp"
#include "XML/UI/System/BindRegister.hpp"

namespace eng::ui
{
    using SysEventPool = EventPool<Event::Focus, Event::MouseButton, Event::MouseMove,
                                   Event::Keyboard, Event::Resize, Event::Type>;
    using SysBindRegister = BindRegister<Event::Focus, Event::MouseButton, Event::MouseMove,
        Event::Keyboard, Event::Resize, Event::Type>;
}