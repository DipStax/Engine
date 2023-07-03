#ifndef ENG_TRIANGLE_HPP
#define ENG_TRIANGLE_HPP

#include <array>

#include "Engine/Maths/Point2.hpp"
#include "Engine/Maths/Point3.hpp"

namespace eng
{
    struct Triangle
    {
        std::array<Point3<float>, 3> pos;
        std::array<Point2<float>, 3> texCoords;
    };
}

#endif