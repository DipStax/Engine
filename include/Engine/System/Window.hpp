#pragma once

#include <string>
#include <thread>

#include <windows.h>

#include "Engine/Maths/Point2.hpp"
#include "Engine/Rendering/Color.hpp"
#include "Engine/Event/Event.hpp"

#include "Engine/System/impl/Window.hpp"

#ifndef WIN_MAXTITLE
    #define WIN_MAXTITLE 256
#endif

namespace eng
{
    class PROJECT_API Window : public impl::WindowClass
    {
        public:
            Window(uint32_t _x, uint32_t _y, const std::string& _title);
            ~Window();
    };
}