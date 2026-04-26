#pragma once

#include "../pixel/Point.hpp"
#include "../pixel/RGB.hpp"
#include "PPMBuffer.hpp"

namespace ppmstream
{

class PPMDrawer
{
private:

    // binding the PPMBuffer
    PPMBuffer& buffer_;

#pragma region Construction
public:
    // constructor
    explicit PPMDrawer(PPMBuffer& buffer);

    // deleted
    PPMDrawer() = delete;
    PPMDrawer(const PPMDrawer&) = delete;
    PPMDrawer& operator =(const PPMDrawer&) = delete;
    PPMDrawer(PPMDrawer&&) = delete;
    PPMDrawer& operator =(PPMDrawer&&) = delete;
    ~PPMDrawer() = default;

#pragma endregion
public:

    // redraw the whole buffer
    void redraw(RGB rgb);

    // draw pixel by (x, y)
    void draw_point(PointI point, RGB rgb);

    // draw a line (Bresenham)
    void draw_line(PointI p0, PointI p1, RGB color);

    // draw rectangle outline
    void draw_rectangle(PointI p0, PointI p1, RGB color);

    // fill rectangle
    void fill_rectangle(size_t x, size_t y, size_t w, size_t h, RGB color);

    // fill a row segment
    void fill_row(size_t x, size_t y, size_t n, RGB color);

    // fill a column segment
    void fill_col(size_t x, size_t y, size_t n, RGB color);

};

}   // namespace ppmstream