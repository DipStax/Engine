#ifndef TESTER_POINT2_HPP
#define TESTER_POINT2_HPP

#include <ostream>

#include "PreProcessing.hpp"

namespace tester
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
        static Point2<_T> as(const Point2<T> &_pt);
        template<NumericType _T>
        Point2<_T> as() const;

        template<NumericType _T>
        friend std::ostream &operator<<(std::ostream &_os, const Point2<_T> &_pt);
    };
}

#include "Point2.inl"

#endif