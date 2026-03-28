#pragma once

#include "../utils/RGB.hpp"
#include "../utils/Point.hpp"

#include <utility>
#include <stdexcept>
#include <vector>

namespace ppm
{

class PPMBuffer
{
private:
    // ppm picture buffer
    std::vector<RGB> pixels_;
    // width
    size_t width_;
    // height_
    size_t height_;

public:
    // constructor
    PPMBuffer() = default;

    PPMBuffer(size_t width, size_t height, RGB bk_color = ppm::RGB::black())
        : width_(width), height_(height)
    {
        pixels_.resize(width * height);
        std::fill(pixels_.begin(), pixels_.end(), bk_color);
    }

    PPMBuffer(size_t width, size_t height, const std::vector<RGB>& data)
    {
        if(data.size() != width * height)
        {
            throw std::invalid_argument("DATA SIZE CANNOT MATCH WIDTH * HEIGHT");
        }
        width_ = width;
        height_ = height;
        pixels_ = std::move(data);
    }

    // copy constructor
    PPMBuffer(const PPMBuffer&) = delete;
    PPMBuffer& operator =(const PPMBuffer&) = delete;

    // move constructor
    PPMBuffer(PPMBuffer&& other)
        : pixels_(std::move(other.pixels_)), width_(other.width_), height_(other.height_)
    {}

    PPMBuffer& operator =(PPMBuffer&& other)
    {
        if(&other != this)
        {
            pixels_ = std::move(other.pixels_);
            width_ = other.width_;
            height_ = other.height_;
        }
        return *this;
    }

    ~PPMBuffer() = default;

public:

    // ppm file width
    inline const size_t width() const
    {
        return width_;
    }
    // ppm file height
    inline const size_t height() const
    {
        return height_;
    }
    // ppm file pixels: width * height
    inline const size_t size() const
    {
        return pixels_.size();
    }
    // bytes size: pixels * sizeof(RGB)
    inline const size_t bytes() const
    {
        return this->size() * sizeof(RGB);
    }
    // data pointer
    inline const RGB* data() const
    {
        return pixels_.data();
    }
    // data buffer container
    inline std::vector<RGB>& buffer()
    {
        return pixels_;
    }
    // data buffer container
    inline const std::vector<RGB>& buffer() const
    {
        return pixels_;
    }
    // the buffer is empty
    inline bool empty() const
    {
        return pixels_.empty();
    }
    // reset the buffer
    inline void reset(size_t width, size_t height, ppm::RGB color = ppm::RGB::black())
    {
        width_ = width;
        height_ = height;
        pixels_.resize(width * height, color);
    }

private:

    // (x, y) is valid position
    inline bool is_valid_position(size_t x, size_t y) const
    {
        return x < width_ && y < height_;
    }
    // (x, y) to index of pixels buffer
    inline size_t to_index(size_t x, size_t y) const
    {
        return x + y * width_;
    }
    // index of pixels buffer to (x, y)
    inline std::pair<size_t, size_t> to_position(size_t index) const
    {
        return {index % width_, index / width_};
    }
    // check bounds
    void check_bounds(size_t x, size_t y) const
    {
        if(x >= width_ || y >= height_)
        {
            throw std::out_of_range("OUT OF FILE BUFFER RANGE");
        }
    }

public:

    // (x, y) rgb value
    inline RGB& operator ()(size_t x, size_t y)
    {
        return pixels_[x + y * width_];
    }
    // (x, y) rgb value
    inline const RGB& operator ()(size_t x, size_t y) const
    {
        return pixels_[x + y * width_];
    }

    // check and visit
    inline RGB& at(size_t x, size_t y)
    {
        check_bounds(x, y);
        return (*this)(x, y);
    }
    // check and visit
    inline const RGB& at(size_t x, size_t y) const
    {
        check_bounds(x, y);
        return (*this)(x, y);
    }

    // the position
    inline RGB& operator [](size_t n)
    {
        return pixels_[n];
    }
    inline const RGB& operator [](size_t n) const
    {
        return pixels_[n];
    }

public:

    // fill row
    void fill_row(size_t x, size_t y, size_t n, RGB color)
    {
        check_bounds(x, y);
        for(; x < std::min(x + n, width_); ++x)
        {
            (*this)(x, y) = color;
        }
    }
    // fill col
    void fill_col(size_t x, size_t y, size_t n, RGB color)
    {
        check_bounds(x, y);
        for(; y < std::min(y + n, height_); ++y)
        {
            (*this)(x, y) = color;
        }
    }
    // fill rectangle
    void fill_rect(size_t x, size_t y, size_t w, size_t h, RGB color)
    {
        check_bounds(x, y);
        for(size_t row = y; row < std::min(x + w, width_); ++row)
        {
            for(size_t col = x; col < std::min(y + h, height_); ++col)
            {
                (*this)(col, row) = color;
            }
        }
    }

    // copy from other buffer
    void copy_from(const PPMBuffer& other)
    {
        if(width_ != other.width_ || height_ != other.height_)
        {
            throw std::invalid_argument("The Buffer must match.");
        }
        pixels_ = other.pixels_;
    }

    // set pixel rgb
    void set(size_t x, size_t y, const RGB& value)
    {
        this->at(x, y) = value;
    }
    // redraw buffer by rgb
    void redraw(const RGB color = ppm::RGB::black())
    {
        std::fill(pixels_.begin(), pixels_.begin() + pixels_.size(), color);
    }
    // clear all buffer
    void clear()
    {
        pixels_.clear();
    }

};

}   // namespace ppm
