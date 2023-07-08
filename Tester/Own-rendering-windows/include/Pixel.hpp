#pragma once

#include "Engine/Color.hpp"
#include "Engine/Point2.hpp"

namespace tester
{
    struct Pixel
    {
        Color clr = Color{ 0, 0, 0 };
        Point2<uint32_t> pos;
    };
}