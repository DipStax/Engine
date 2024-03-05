#pragma once

#include "Engine/Maths/Point3.hpp"
#include "Engine/Rendering/Color.hpp"

namespace eng
{
    struct PROJECT_API Vertex
    {
        Point2<float> pos;
        Point2<float> txtrPos;
        Color clr = Color(0, 0, 0, 255);
    };

    struct PROJECT_API Vertex3D
    {
        Point3<float> pos;
        Point2<float> txtrPos;
        Color clr = Color(0, 0, 0, 255);
    };
}