#include "../../include/ppmstream/stream/PPMDrawer.hpp"
#include "../../include/ppmstream/stream/PPMStream.hpp"

// constructor
ppmstream::PPMDrawer::
PPMDrawer(ppmstream::PPMStream& stream)
    : stream_(stream)
{}

// redraw the buffer
void
ppmstream::PPMDrawer::
redraw(RGB rgb)
{
    for(size_t i = 0; i < stream_.pixels_.width() * stream_.pixels_.height(); ++i)
    {
        stream_.pixels_[i] = rgb;
    }
}

// draw pixel by (x, y)
void
ppmstream::PPMDrawer::
draw_point(PointI point, RGB rgb)
{
    if(point.x < stream_.pixels_.width() && point.y < stream_.pixels_.height())
    {
        stream_.pixels_(point.x, point.y) = rgb;
    }
}

// draw a line
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

// draw rectangle
void
ppmstream::PPMDrawer::
draw_rectangle(PointI p0, PointI p2, RGB color)
{

}
