#ifndef ENG_MATHS_ANGLE_HPP
#define ENG_MATHS_ANGLE_HPP

#include "Engine/Maths/Point2.hpp"
#include "Tool/PreProcessing.hpp"

namespace eng
{
    template<NumericType T>
    T toRad(T _deg);
    template<NumericType T>
    T toDeg(T _rad);

    template<NumericType T>
    T area(const Vector2<T> &_a, const Vector2<T> &_b, const Vector2<T> &_c);
}

#include "Engine/Maths/Maths.inl"

#endif