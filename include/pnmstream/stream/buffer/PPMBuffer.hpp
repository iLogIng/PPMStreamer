#pragma once

#include "PNMBuffer.hpp"

#include <utility>
#include <stdexcept>
#include <vector>

#include "../../pixel/RGB.hpp"
#include "../../pixel/Point.hpp"

namespace pnmstream
{

class PPMBuffer
    : public pnmstream::PNMBuffer<RGB>
{
private:
    std::vector<RGB> pixels_;       // 像素缓冲
    size_t width_ = 0;              // 宽
    size_t height_ = 0;             // 高

#pragma region Construction
public:
    // constructor
    PPMBuffer() = default;

    PPMBuffer(size_t width, size_t height, RGB bk_color = RGB::black());

    // copy constructor
    PPMBuffer(const PPMBuffer&) = delete;
    PPMBuffer& operator =(const PPMBuffer&) = delete;

    // move constructor
    PPMBuffer(PPMBuffer&& other);

    PPMBuffer& operator =(PPMBuffer&& other);

    ~PPMBuffer() = default;

#pragma endregion
public:

    // ppm file width
    size_t width() const noexcept;
    // ppm file height
    size_t height() const noexcept;
    // ppm file pixels: width * height
    size_t size() const noexcept;
    // bytes size: pixels * sizeof(RGB)
    size_t bytes() const;
    // data pointer
    const RGB* data() const noexcept;
    // data buffer container
    std::vector<RGB>& buffer() noexcept;
    // data buffer container
    const std::vector<RGB>& buffer() const noexcept;
    // the buffer is empty
    bool empty() const noexcept;
    // reset the buffer
    void reset(size_t width, size_t height, RGB color = RGB::black());

private:

    // check bounds
    void check_bounds(size_t x, size_t y) const;

#pragma region Buffer Index
public:

    // (x, y) rgb value
    RGB& operator ()(size_t x, size_t y);
    // (x, y) rgb value
    const RGB& operator ()(size_t x, size_t y) const;

    // check and visit
    RGB& at(size_t x, size_t y);
    // check and visit
    const RGB& at(size_t x, size_t y) const;

    // the position
    RGB& operator [](size_t n);
    const RGB& operator [](size_t n) const;

#pragma endregion
public:
    // clear all buffer
    void clear();

};

}   // namespace pnmstream
