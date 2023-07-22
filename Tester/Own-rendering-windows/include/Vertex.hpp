#pragma once

#include "Engine/Point2.hpp"
#include "Engine/Color.hpp"

namespace tester
{
    struct Vertex
    {
        Point2<float> pos;
        Point2<float> txtrPos;
        Color clr;
    };
}