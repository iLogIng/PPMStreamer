#pragma once

#include "RGBA.hpp"
#include "Point.hpp"

namespace pnmstream
{

template<typename T>
class Pixel
{
private:
    Point<T> point_;
    RGBA color_;

public:
    Pixel() = default;

    Pixel(Point<T> point, const RGBA& color)
        : point_(point)
        , color_(color)
    {}

public:
    RGBA& color() {
        return color_;
    }
    const RGBA& color() const {
        return color_;
    }

    Point<T>& point() {
        return point_;
    }
    const Point<T>& point() const {
        return point_;
    }
};

} // namespace pnmstream
