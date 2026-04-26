#include "../../include/ppmstream/stream/PPMDrawer.hpp"

// constructor
ppmstream::PPMDrawer::
PPMDrawer(ppmstream::PPMBuffer& buffer)
    : buffer_(buffer)
{}

// redraw the buffer
void
ppmstream::PPMDrawer::
redraw(RGB rgb)
{
    for(size_t i = 0; i < buffer_.size(); ++i)
    {
        buffer_[i] = rgb;
    }
}

// draw pixel by (x, y)
void
ppmstream::PPMDrawer::
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
ppmstream::PPMDrawer::
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

// draw rectangle outline
void
ppmstream::PPMDrawer::
draw_rectangle(PointI p0, PointI p2, RGB color)
{
    PointI p1(p2.x, p0.y);
    PointI p3(p0.x, p2.y);

    draw_line(p0, p1, color);
    draw_line(p1, p2, color);
    draw_line(p2, p3, color);
    draw_line(p3, p0, color);
}

// fill rectangle
void
ppmstream::PPMDrawer::
fill_rectangle(size_t x, size_t y, size_t w, size_t h, RGB color)
{
    size_t end_row = std::min(y + h, buffer_.height());
    size_t end_col = std::min(x + w, buffer_.width());

    for(size_t row = y; row < end_row; ++row)
    {
        for(size_t col = x; col < end_col; ++col)
        {
            buffer_(col, row) = color;
        }
    }
}

// fill a row segment
void
ppmstream::PPMDrawer::
fill_row(size_t x, size_t y, size_t n, RGB color)
{
    size_t end_x = std::min(x + n, buffer_.width());
    for(; x < end_x; ++x)
    {
        buffer_(x, y) = color;
    }
}

// fill a column segment
void
ppmstream::PPMDrawer::
fill_col(size_t x, size_t y, size_t n, RGB color)
{
    size_t end_y = std::min(y + n, buffer_.height());
    for(; y < end_y; ++y)
    {
        buffer_(x, y) = color;
    }
}
