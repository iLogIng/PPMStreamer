#pragma once

#include <cmath>
#include "../pixel/Point.hpp"
#include "buffer/PNMBuffer.hpp"

namespace pnmstream
{

template<typename color_type_>
class PNMDrawer
{
    using color_type = color_type_;
private:

    // binding the PNMBuffer
    PNMBuffer<color_type>& buffer_;

#pragma region Construction
public:
    // constructor
    explicit PNMDrawer(PNMBuffer<color_type>& buffer) noexcept;

    // deleted
    PNMDrawer() = delete;
    PNMDrawer(const PNMDrawer&) = delete;
    PNMDrawer& operator =(const PNMDrawer&) = delete;
    PNMDrawer(PNMDrawer&&) = delete;
    PNMDrawer& operator =(PNMDrawer&&) = delete;
    ~PNMDrawer() = default;

#pragma endregion

#pragma region Drawing Operation
public:
    // redraw the whole buffer
    void redraw(color_type color) noexcept;

    // draw pixel by (x, y)
    void draw_point(PointI point, color_type color) noexcept;

    // draw a line (Bresenham)
    void draw_line(PointI p0, PointI p1, color_type color) noexcept;

    // draw a row segment
    void draw_row(PointI p, size_t n, color_type color) noexcept;

    // draw a column segment
    void draw_col(PointI p, size_t n, color_type color) noexcept;

    // fill rectangle
    void fill_rectangle(PointI p, size_t w, size_t h, color_type color) noexcept;

#pragma endregion
    
};

template<typename color_type>
pnmstream::PNMDrawer<color_type>::
PNMDrawer(pnmstream::PNMBuffer<color_type>& buffer) noexcept
    : buffer_(buffer)
{}

template<typename color_type>
void
pnmstream::PNMDrawer<color_type>::
redraw(color_type color) noexcept
{
    for(size_t i = 0; i < buffer_.size(); ++i)
    {
        buffer_[i] = color;
    }
}

template<typename color_type>
void
pnmstream::PNMDrawer<color_type>::
draw_point(PointI point, color_type color) noexcept
{
    if(point.x >= 0 && point.y >= 0
        && static_cast<size_t>(point.x) < buffer_.width()
        && static_cast<size_t>(point.y) < buffer_.height())
    {
        buffer_(point.x, point.y) = color;
    }
}

template<typename color_type>
void
pnmstream::PNMDrawer<color_type>::
draw_line(PointI p0, PointI p1, color_type color) noexcept
{
    int dx = std::abs(p1.x - p0.x);
    int dy = std::abs(p1.y - p0.y);
    int sx = (p0.x < p1.x) ? 1 : -1;
    int sy = (p0.y < p1.y) ? 1 : -1;
    int err = dx - dy;

    while(true)
    {
        draw_point({p0.x, p0.y}, color);
        if(p0.x == p1.x && p0.y == p1.y)
        {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            p0.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            p0.y += sy;
        }
    }
}

template<typename color_type>
void
pnmstream::PNMDrawer<color_type>::
fill_rectangle(PointI p, size_t w, size_t h, color_type color) noexcept
{
    size_t end_row = std::min(p.y + h, buffer_.height());
    size_t end_col = std::min(p.x + w, buffer_.width());

    for(size_t row = p.y; row < end_row; ++row)
    {
        for(size_t col = p.x; col < end_col; ++col)
        {
            buffer_(col, row) = color;
        }
    }
}

template<typename color_type>
void
pnmstream::PNMDrawer<color_type>::
draw_row(PointI p, size_t n, color_type color) noexcept
{
    size_t end_x = std::min(p.x + n, buffer_.width());
    for(; static_cast<size_t>(p.x) < end_x; ++p.x)
    {
        buffer_(p.x, p.y) = color;
    }
}

template<typename color_type>
void
pnmstream::PNMDrawer<color_type>::
draw_col(PointI p, size_t n, color_type color) noexcept
{
    size_t end_y = std::min(p.y + n, buffer_.height());
    for(; static_cast<size_t>(p.y) < end_y; ++p.y)
    {
        buffer_(p.x, p.y) = color;
    }
}


}   // namespace pnmstream