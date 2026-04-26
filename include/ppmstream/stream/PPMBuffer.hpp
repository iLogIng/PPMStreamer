#pragma once

#include <utility>
#include <stdexcept>
#include <vector>

#include "../pixel/RGB.hpp"
#include "../pixel/Point.hpp"

namespace ppmstream
{

class PPMBuffer
{
private:
    std::vector<RGB> pixels_;       // 像素缓冲
    size_t width_ = 0;              // 宽
    size_t height_ = 0;             // 高

#pragma region Construction
public:
    // constructor
    PPMBuffer() = default;

    PPMBuffer(size_t width, size_t height, RGB bk_color = ppmstream::RGB::black());

    PPMBuffer(size_t width, size_t height, const std::vector<RGB>& data);

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
    size_t width() const;
    // ppm file height
    size_t height() const;
    // ppm file pixels: width * height
    size_t size() const;
    // bytes size: pixels * sizeof(RGB)
    size_t bytes() const;
    // data pointer
    const RGB* data() const;
    // data buffer container
    std::vector<RGB>& buffer();
    // data buffer container
    const std::vector<RGB>& buffer() const;
    // the buffer is empty
    bool empty() const;
    // reset the buffer
    void reset(size_t width, size_t height, ppmstream::RGB color = ppmstream::RGB::black());

private:

    // (x, y) is valid position
    bool is_valid_position(size_t x, size_t y) const;
    // (x, y) to index of pixels buffer
    size_t to_index(size_t x, size_t y) const;
    // index of pixels buffer to (x, y)
    std::pair<size_t, size_t> to_position(size_t index) const;
    // check bounds
    void check_bounds(size_t x, size_t y) const;

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

public:
    // copy from other buffer
    void copy_from(const PPMBuffer& other);
    // clear all buffer
    void clear();

};

}   // namespace ppmstream
