#ifndef ENG_MATHS_POINT3_HPP
#define ENG_MATHS_POINT3_HPP

#include "Engine/Maths/Point2.hpp"
#include "Engine/Tool/PreProcessing.hpp"

namespace eng
{
    template<NumericType T>
    struct Point3
    {
        T x = 0;
        T y = 0;
        T z = 0;

        // operator arithmetic
        Point3<T> operator+(const Point3<T> &_pos) const;
        Point3<T> operator-(const Point3<T> &_pos) const;
        Point3<T> operator*(const Point3<T> &_pos) const;
        Point3<T> operator/(const Point3<T> &_pos) const;

        Point3<T> operator+(const T &_val) const;
        Point3<T> operator-(const T &_val) const;
        Point3<T> operator*(const T &_val) const;
        Point3<T> operator/(const T &_val) const;

        // operator assignement
        Point3<T> &operator+=(const Point3<T> &_pos);
        Point3<T> &operator-=(const Point3<T> &_pos);
        Point3<T> &operator*=(const Point3<T> &_pos);
        Point3<T> &operator/=(const Point3<T> &_pos);

        Point3<T> &operator+=(const T &_val);
        Point3<T> &operator-=(const T &_val);
        Point3<T> &operator*=(const T &_val);
        Point3<T> &operator/=(const T &_val);

        bool operator==(const Point3<T> &_pos);
        bool operator!=(const Point3<T> &_pos);

        template<NumericType _T>
        friend std::ostream &operator<<(std::ostream &_os, const Point3<_T> &_pt);

        Point2<T> as2() const;
    };

    template<NumericType T>
    using Vector3 = Point3<T>;
}

#include "Engine/Maths/Point3.inl"

#endif