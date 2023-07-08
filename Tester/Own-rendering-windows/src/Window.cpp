#include <iostream>

#include "Window.hpp"

namespace Win
{
    HWND find(LPCTSTR _name, LPCTSTR _class)
    {
        return FindWindow(_class, _name);
    }
}