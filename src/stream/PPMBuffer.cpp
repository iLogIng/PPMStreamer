#include "../../include/ppmstream/stream/PPMBuffer.hpp"

ppmstream::PPMBuffer::
PPMBuffer(size_t width, size_t height, RGB bk_color)
    : width_(width), height_(height)
{
    pixels_.resize(width * height);
    std::fill(pixels_.begin(), pixels_.end(), bk_color);
}

// move constructor
ppmstream::PPMBuffer::
PPMBuffer(PPMBuffer&& other)
    : pixels_(std::move(other.pixels_)), width_(other.width_), height_(other.height_)
{}

ppmstream::PPMBuffer&
ppmstream::PPMBuffer::
operator =(PPMBuffer&& other)
{
    if(&other != this)
    {
        pixels_ = std::move(other.pixels_);
        width_ = other.width_;
        height_ = other.height_;
    }
    return *this;
}

// ppm file width
std::size_t
ppmstream::PPMBuffer::
width() const
{
    return width_;
}

// ppm file height
std::size_t
ppmstream::PPMBuffer::
height() const
{
    return height_;
}

// ppm file pixels: width * height
std::size_t
ppmstream::PPMBuffer::
size() const
{
    return pixels_.size();
}

// bytes size: pixels * sizeof(RGB)
std::size_t
ppmstream::PPMBuffer::
bytes() const
{
    return this->size() * sizeof(RGB);
}

// data pointer
const ppmstream::RGB*
ppmstream::PPMBuffer::
data() const
{
    return pixels_.data();
}

// data buffer container
std::vector<ppmstream::RGB>&
ppmstream::PPMBuffer::
buffer()
{
    return pixels_;
}

// data buffer container
const std::vector<ppmstream::RGB>&
ppmstream::PPMBuffer::
buffer() const
{
    return pixels_;
}

// the buffer is empty
bool
ppmstream::PPMBuffer::
empty() const
{
    return pixels_.empty();
}

// reset the buffer
void
ppmstream::PPMBuffer::
reset(size_t width, size_t height, ppmstream::RGB color)
{
    width_ = width;
    height_ = height;
    pixels_.resize(width * height, color);
}

// check bounds
void
ppmstream::PPMBuffer::
check_bounds(std::size_t x, std::size_t y) const
{
    if(x >= width_ || y >= height_)
    {
        throw std::out_of_range("OUT OF FILE BUFFER RANGE");
    }
}

// (x, y) rgb value
ppmstream::RGB&
ppmstream::PPMBuffer::
operator ()(size_t x, size_t y)
{
    return pixels_[x + y * width_];
}

// (x, y) rgb value
const ppmstream::RGB&
ppmstream::PPMBuffer::
operator ()(size_t x, size_t y) const
{
    return pixels_[x + y * width_];
}

// check and visit
ppmstream::RGB&
ppmstream::PPMBuffer::
at(size_t x, size_t y)
{
    check_bounds(x, y);
    return (*this)(x, y);
}

// check and visit
const ppmstream::RGB&
ppmstream::PPMBuffer::
at(size_t x, size_t y) const
{
    check_bounds(x, y);
    return (*this)(x, y);
}

// the position
ppmstream::RGB&
ppmstream::PPMBuffer::
operator [](size_t n)
{
    return pixels_[n];
}

const ppmstream::RGB&
ppmstream::PPMBuffer::
operator [](size_t n) const
{
    return pixels_[n];
}

// clear all buffer
void
ppmstream::PPMBuffer::
clear()
{
    pixels_.clear();
}

