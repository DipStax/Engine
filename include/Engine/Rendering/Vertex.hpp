#pragma once

#include "Engine/Maths/Point2.hpp"
#include "Engine/Rendering/Color.hpp"

namespace eng
{
    struct Vertex
    {
        Point2<float> pos;
        Point2<float> txtrPos;
        Color clr;
    };
}