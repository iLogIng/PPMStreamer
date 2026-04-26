#pragma once

#include "../pixel/Point.hpp"
#include "../pixel/RGB.hpp"

namespace ppmstream
{

class PPMStream;

class PPMDrawer
{
    friend class PPMStream;
    friend class PPMBuffer;
private:

    // binding the PPMStream
    PPMStream& stream_;

    // constructor
    PPMDrawer(PPMStream& stream);

private:
    // constructor
    PPMDrawer() = delete;

    // copy constructor
    PPMDrawer(const PPMDrawer&) = delete;
    PPMDrawer& operator =(const PPMDrawer&) = delete;

    // move constructor
    PPMDrawer(PPMDrawer&&) = delete;
    PPMDrawer& operator =(PPMDrawer&&) = delete;

    // destructor
    ~PPMDrawer() = default;

public:
    // redraw the buffer
    void redraw(RGB rgb);

public:
    // draw pixel by (x, y)
    void draw_point(PointI point, RGB rgb);

    // draw a line
    void draw_line(PointI p0, PointI p1, RGB color);

    // draw rectangle
    void draw_rectangle(PointI p0, PointI p2, RGB color);

};

}   // namespace ppmstream