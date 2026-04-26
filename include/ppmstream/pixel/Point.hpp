#pragma once

#include <utility>
#include <stdexcept>

namespace ppmstream
{

template<typename Ty>
struct Point
{
    static_assert(std::is_arithmetic_v<Ty>,
        "Point template argument must be an integral or floating point type");

    Ty x;
    Ty y;

    // constructor
    Point()
        : x(Ty{}), y(Ty{})
    {}

    Point(Ty px, Ty py)
        : x(px), y(py)
    {}

    Point(std::pair<Ty, Ty> point)
        : x(point.first), y(point.second)
    {}

    // copy constructor
    Point(const Point<Ty>& other)
        : x(other.x), y(other.y)
    {}

    template<typename U>
    Point(const Point<U>& other)
        : x(static_cast<Ty>(other.x)), y(static_cast<Ty>(other.y))
    {}

    Point& operator =(const Point<Ty>& other)
    {
        if(&other != this)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    template<typename U>
    Point& operator =(const Point<U>& other)
    {
        if(&other != this)
        {
            x = static_cast<Ty>(other.x);
            y = static_cast<Ty>(other.y);
        }
        return *this;
    }

    // move operator
    Point(Point&& other)
        : x(std::move(other.x)), y(std::move(other.y))
    {}

    template<typename U>
    Point(Point<U>&& other)
        : x(static_cast<Ty>(other.x)), y(static_cast<Ty>(other.y))
    {}

    Point& operator =(Point&& other)
    {
        if(&other != this)
        {
            x = std::move(other.x);
            y = std::move(other.y);
        }
        return *this;
    }

    template<typename U>
    Point& operator =(Point<U>&& other)
    {
        if(&other != this)
        {
            x = static_cast<Ty>(other.x);
            y = static_cast<Ty>(other.y);
        }
        return *this;
    }

    // operator op
    bool operator ==(const Point& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool operator !=(const Point& other) const
    {
        return (x != other.x) || (y != other.y);
    }

};

using PointI = Point<int>;
using PointF = Point<float>;
using PointD = Point<double>;

}   // namespace ppm