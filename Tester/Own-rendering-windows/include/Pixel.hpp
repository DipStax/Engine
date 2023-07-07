#pragma once

#include "Engine/Color.hpp"
#include "Engine/Point2.hpp"

namespace tester
{
    struct Pixel
    {
        Color clr;
        Point2<uint32_t> pos;
    };
}