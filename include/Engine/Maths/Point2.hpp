#ifndef ENG_MATHS_POINT2_HPP
#define ENG_MATHS_POINT2_HPP

#include <ostream>

#include <sfml/System/Vector2.hpp>

#include "Tool/PreProcessing.hpp"

namespace eng
{
    template<NumericType T>
    struct Point2
    {
        T x = 0;
        T y = 0;

        // operator arithmetic
        Point2<T> operator+(const Point2<T> &_pos) const;
        Point2<T> operator-(const Point2<T> &_pos) const;
        Point2<T> operator*(const Point2<T> &_pos) const;
        Point2<T> operator/(const Point2<T> &_pos) const;

        Point2<T> operator+(const T &_val) const;
        Point2<T> operator-(const T &_val) const;
        Point2<T> operator*(const T &_val) const;
        Point2<T> operator/(const T &_val) const;

        // operator assignement
        Point2<T> &operator+=(const Point2<T> &_pos);
        Point2<T> &operator-=(const Point2<T> &_pos);
        Point2<T> &operator*=(const Point2<T> &_pos);
        Point2<T> &operator/=(const Point2<T> &_pos);

        Point2<T> &operator+=(const T &_val);
        Point2<T> &operator-=(const T &_val);
        Point2<T> &operator*=(const T &_val);
        Point2<T> &operator/=(const T &_val);

        bool operator==(const Point2<T> &_pos);
        bool operator!=(const Point2<T> &_pos);

        template<NumericType _T>
        friend std::ostream &operator<<(std::ostream &_os, const Point2<_T> &_pt);

        operator sf::Vector2<T>() const;
    };

    template<NumericType T>
    using Vector2 = Point2<T>;
}

#include "Engine/Maths/Point2.inl"

#endif