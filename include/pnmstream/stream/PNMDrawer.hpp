#pragma once

#include "../pixel/Point.hpp"
#include "../pixel/RGB.hpp"
#include "buffer/PNMBuffer.hpp"

namespace pnmstream
{

class PNMDrawer
{
private:

    // binding the PNMBuffer
    pnmstream::PNMBuffer<RGB>& buffer_;

#pragma region Construction
public:
    // constructor
    explicit PNMDrawer(pnmstream::PNMBuffer<RGB>& buffer);

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
    void redraw(RGB rgb);

    // draw pixel by (x, y)
    void draw_point(PointI point, RGB rgb);

    // draw a line (Bresenham)
    void draw_line(PointI p0, PointI p1, RGB color);

    // draw a row segment
    void draw_row(PointI p, size_t n, RGB color);

    // draw a column segment
    void draw_col(PointI p, size_t n, RGB color);

    // fill rectangle
    void fill_rectangle(PointI p, size_t w, size_t h, RGB color);

#pragma endregion

};

}   // namespace pnmstream