#pragma once

#include <cmath>

#include "PreProcessing.hpp"
#include "Engine/Point2.hpp"

namespace tester
{
    template<NumericType T>
    T area(const Point2<T> &_a, const Point2<T> &_b, const Point2<T> &_c)
    {
        Point2<T> ab = _b - _a;
        Point2<T> ac = _c - _a;

        return ab.x * ac.y - ab.y * ac.x;
    }
}