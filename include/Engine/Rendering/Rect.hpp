#pragma once

#include "Engine/Maths/Point2.hpp"

namespace eng
{
    struct PROJECT_API Rect
    {
        Point2<float> pos;
        Point2<float> size;
    };
}