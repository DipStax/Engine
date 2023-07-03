#include <numbers>
#include <cmath>

#include "Engine/Maths/Maths.hpp"

namespace eng
{
    template<NumericType T>
    T toRad(T _deg)
    {
        return _deg * (std::numbers::pi / 180);
    }

    template<NumericType T>
    T toDeg(T _rad)
    {
        return _rad * (180 / std::numbers::pi);
    }

    template<NumericType T>
    T area(const Vector2<T> &_a, const Vector2<T> &_b, const Vector2<T> &_c)
    {
        Vector2<T> ab = _b - _a;
        Vector2<T> ac = _c - _a;

        return std::abs(ab.x * ac.y - ab.y * ac.x);
    }

}