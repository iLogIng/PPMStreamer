#pragma once

#include <utility>
#include <type_traits>

namespace pnmstream
{

template<typename Ty>
struct Point
{
    static_assert(std::is_arithmetic_v<Ty>,
        "Point template argument must be an integral or floating point type");

    Ty x;
    Ty y;

    constexpr Point() noexcept
        : x(Ty{}), y(Ty{})
    {}

    constexpr Point(Ty px, Ty py) noexcept
        : x(px), y(py)
    {}

    constexpr Point(std::pair<Ty, Ty> point) noexcept
        : x(point.first), y(point.second)
    {}

    constexpr Point(const Point<Ty>& other) noexcept
        : x(other.x), y(other.y)
    {}

    template<typename U>
    constexpr Point(const Point<U>& other) noexcept
        : x(static_cast<Ty>(other.x)), y(static_cast<Ty>(other.y))
    {}

    constexpr Point& operator =(const Point<Ty>& other) noexcept
    {
        if(&other != this)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    template<typename U>
    constexpr Point& operator =(const Point<U>& other) noexcept
    {
        if(&other != this)
        {
            x = static_cast<Ty>(other.x);
            y = static_cast<Ty>(other.y);
        }
        return *this;
    }

    constexpr Point(Point&& other) noexcept
        : x(other.x), y(other.y)
    {}

    template<typename U>
    constexpr Point(Point<U>&& other) noexcept
        : x(static_cast<Ty>(other.x)), y(static_cast<Ty>(other.y))
    {}

    constexpr Point& operator =(Point&& other) noexcept
    {
        if(&other != this)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    template<typename U>
    constexpr Point& operator =(Point<U>&& other) noexcept
    {
        if(&other != this)
        {
            x = static_cast<Ty>(other.x);
            y = static_cast<Ty>(other.y);
        }
        return *this;
    }

    constexpr bool operator ==(const Point& other) const noexcept
    {
        return (x == other.x) && (y == other.y);
    }

    constexpr bool operator !=(const Point& other) const noexcept
    {
        return (x != other.x) || (y != other.y);
    }
};

using PointI = Point<int>;
using PointF = Point<float>;
using PointD = Point<double>;

}   // namespace pnmstream