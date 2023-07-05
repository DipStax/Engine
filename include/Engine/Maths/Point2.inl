#include "Engine/Maths/Point2.hpp"

namespace eng
{
    template<NumericType T>
    Point2<T> Point2<T>::operator+(const Point2<T> &_pos) const
    {
        return { x + _pos.x, y + _pos.y };
    }

    template<NumericType T>
    Point2<T> Point2<T>::operator-(const Point2<T> &_pos) const
    {
        return { x - _pos.x, y - _pos.y };
    }

    template<NumericType T>
    Point2<T> Point2<T>::operator*(const Point2<T> &_pos) const
    {
        return { x * _pos.x, y * _pos.y };
    }

    template<NumericType T>
    Point2<T> Point2<T>::operator/(const Point2<T> &_pos) const
    {
        return { x / _pos.x, y / _pos.y };
    }

    template<NumericType T>
    Point2<T> Point2<T>::operator+(const T &_val) const
    {
        return { x + _val, y + _val };
    }

    template<NumericType T>
    Point2<T> Point2<T>::operator-(const T & _val) const
    {
        return { x - _val, y - _val };
    }

    template<NumericType T>
    Point2<T> Point2<T>::operator*(const T & _val) const
    {
        return { x * _val, y * _val };
    }

    template<NumericType T>
    Point2<T> Point2<T>::operator/(const T & _val) const
    {
        return { x / _val, y / _val };
    }

    template<NumericType T>
    Point2<T> &Point2<T>::operator+=(const Point2<T> &_pos)
    {
        x += _pos.x;
        y += _pos.y;
        return *this;
    }

    template<NumericType T>
    Point2<T> &Point2<T>::operator-=(const Point2<T> &_pos)
    {
        x -= _pos.x;
        y -= _pos.y;
        return *this;
    }

    template<NumericType T>
    Point2<T> &Point2<T>::operator*=(const Point2<T> &_pos)
    {
        x *= _pos.x;
        y *= _pos.y;
        return *this;
    }

    template<NumericType T>
    Point2<T> &Point2<T>::operator/=(const Point2<T> &_pos)
    {
        x /= _pos.x;
        y /= _pos.y;
        return *this;
    }

    template<NumericType T>
    Point2<T> &Point2<T>::operator+=(const T &_val)
    {
        x += _val;
        y += _val;
        return *this;
    }

    template<NumericType T>
    Point2<T> &Point2<T>::operator-=(const T &_val)
    {
        x -= _val;
        y -= _val;
        return *this;
    }

    template<NumericType T>
    Point2<T> &Point2<T>::operator*=(const T &_val)
    {
        x *= _val;
        y *= _val;
        return *this;
    }

    template<NumericType T>
    Point2<T> &Point2<T>::operator/=(const T &_val)
    {
        x /= _val;
        y /= _val;
        return *this;
    }

    template<NumericType T>
    bool Point2<T>::operator==(const Point2<T> &_pos)
    {
        return x == _pos.x && y == _pos.y;
    }

    template<NumericType T>
    bool Point2<T>::operator!=(const Point2<T> &_pos)
    {
        return x != _pos.x && y != _pos.y;
    }

    template<NumericType _T>
    std::ostream &operator<<(std::ostream &_os, const Point2<_T> &_pt)
    {
        _os << "{ " << _pt.x << ", " << _pt.y << " }";
        return _os;
    }

    // template<NumericType T>
    // inline Point2<T>::operator sf::Vector2<T>() const
    // {
    //     return sf::Vector2<T>(x, y);
    // }
}