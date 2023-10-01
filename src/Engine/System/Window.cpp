#include <map>
#include <iostream>

#include <Windows.h>
#include <windowsx.h>

#include "Engine/System/Key.hpp"
#include "Engine/System/Window.hpp"

namespace eng
{
    Window::Window(uint32_t _x, uint32_t _y, const std::string& _title)
    {
        open(_x, _y, _title);
    }

    Window::~Window()
    {
        close();
    }
}