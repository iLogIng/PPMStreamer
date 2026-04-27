#include "../../include/pnmstream/stream/PNMDrawer.hpp"

// constructor
pnmstream::PNMDrawer::
PNMDrawer(pnmstream::PNMBuffer<RGB>& buffer)
    : buffer_(buffer)
{}

// redraw the buffer
void
pnmstream::PNMDrawer::
redraw(RGB rgb)
{
    for(size_t i = 0; i < buffer_.size(); ++i)
    {
        buffer_[i] = rgb;
    }
}

// draw pixel by (x, y)
void
pnmstream::PNMDrawer::
draw_point(PointI point, RGB rgb)
{
    if(point.x >= 0 && point.y >= 0
        && static_cast<size_t>(point.x) < buffer_.width()
        && static_cast<size_t>(point.y) < buffer_.height())
    {
        buffer_(point.x, point.y) = rgb;
    }
}

// draw a line (Bresenham)
void
pnmstream::PNMDrawer::
draw_line(PointI p0, PointI p1, RGB color)
{
    int dx = abs(p1.x - p0.x);
    int dy = abs(p1.y - p0.y);
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

// fill rectangle
void
pnmstream::PNMDrawer::
fill_rectangle(PointI p, size_t w, size_t h, RGB color)
{
    size_t end_row = std::min(p.x + h, buffer_.height());
    size_t end_col = std::min(p.y + w, buffer_.width());

    for(size_t row = p.y; row < end_row; ++row)
    {
        for(size_t col = p.x; col < end_col; ++col)
        {
            buffer_(col, row) = color;
        }
    }
}

// draw a row segment
void
pnmstream::PNMDrawer::
draw_row(PointI p, size_t n, RGB color)
{
    size_t end_x = std::min(p.x + n, buffer_.width());
    for(; static_cast<size_t>(p.x) < end_x; ++p.x)
    {
        buffer_(p.x, p.y) = color;
    }
}

// draw a column segment
void
pnmstream::PNMDrawer::
draw_col(PointI p, size_t n, RGB color)
{
    size_t end_y = std::min(p.y + n, buffer_.height());
    for(; static_cast<size_t>(p.y) < end_y; ++p.y)
    {
        buffer_(p.x, p.y) = color;
    }
}
