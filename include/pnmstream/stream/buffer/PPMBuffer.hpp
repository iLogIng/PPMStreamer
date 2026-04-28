#pragma once

#include "PNMBuffer.hpp"

#include "../../pixel/RGB.hpp"

namespace pnmstream
{

class PPMBuffer
    : public pnmstream::PNMBuffer<RGB>
{
private:
    buffer_type pixels_;       // 像素缓冲
    size_t width_ = 0;              // 宽
    size_t height_ = 0;             // 高

#pragma region Construction
public:
    // constructor
    PPMBuffer() = default;

    PPMBuffer(size_t width, size_t height, color_type bk_color = color_type::black());

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
    size_t width() const noexcept override;
    // ppm file height
    size_t height() const noexcept override;
    // ppm file pixels: width * height
    size_t size() const noexcept override;
    // bytes size: pixels * sizeof(color_type)
    size_t bytes() const override;
    // data pointer
    const color_type* data() const noexcept override;
    // mutable data pointer
    color_type* data() noexcept override;
    // data buffer container
    buffer_type& buffer() noexcept override;

    // data buffer container
    const buffer_type& buffer() const noexcept override;
    // the buffer is empty
    bool empty() const noexcept override;
    // reset the buffer
    void reset(size_t width, size_t height, color_type color = color_type::black()) override;

private:

    // check bounds
    void check_bounds(size_t x, size_t y) const;

#pragma region Buffer Index
public:

    // (x, y) rgb value
    color_type& operator ()(size_t x, size_t y) override;
    // (x, y) rgb value
    const color_type& operator ()(size_t x, size_t y) const override;

    // check and visit
    color_type& at(size_t x, size_t y) override;
    // check and visit
    const color_type& at(size_t x, size_t y) const override;

    // the position
    color_type& operator [](size_t n) override;
    const color_type& operator [](size_t n) const override;

#pragma endregion
public:
    // clear all buffer
    void clear() override;

};

}   // namespace pnmstream
