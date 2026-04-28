#include "../../../include/pnmstream/stream/buffer/PPMBuffer.hpp"

pnmstream::PPMBuffer::
PPMBuffer(size_t width, size_t height, RGB bk_color)
    : width_(width), height_(height)
{
    pixels_.resize(width * height);
    std::fill(pixels_.begin(), pixels_.end(), bk_color);
}

// move constructor
pnmstream::PPMBuffer::
PPMBuffer(PPMBuffer&& other)
    : pixels_(std::move(other.pixels_)), width_(other.width_), height_(other.height_)
{}

pnmstream::PPMBuffer&
pnmstream::PPMBuffer::
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
pnmstream::PPMBuffer::
width() const noexcept
{
    return width_;
}

// ppm file height
std::size_t
pnmstream::PPMBuffer::
height() const noexcept
{
    return height_;
}

// ppm file pixels: width * height
std::size_t
pnmstream::PPMBuffer::
size() const noexcept
{
    return pixels_.size();
}

// bytes size: pixels * sizeof(RGB)
std::size_t
pnmstream::PPMBuffer::
bytes() const
{
    return this->size() * sizeof(RGB);
}

// data pointer
const pnmstream::RGB*
pnmstream::PPMBuffer::
data() const noexcept
{
    return pixels_.data();
}

// mutable data pointer
pnmstream::RGB*
pnmstream::PPMBuffer::
data() noexcept
{
    return pixels_.data();
}

// data buffer container
std::vector<pnmstream::RGB>&
pnmstream::PPMBuffer::
buffer() noexcept
{
    return pixels_;
}

// data buffer container
const std::vector<pnmstream::RGB>&
pnmstream::PPMBuffer::
buffer() const noexcept
{
    return pixels_;
}

// the buffer is empty
bool
pnmstream::PPMBuffer::
empty() const noexcept
{
    return pixels_.empty();
}

// reset the buffer
void
pnmstream::PPMBuffer::
reset(size_t width, size_t height, pnmstream::RGB color)
{
    width_ = width;
    height_ = height;
    pixels_.resize(width * height, color);
}

// check bounds
void
pnmstream::PPMBuffer::
check_bounds(std::size_t x, std::size_t y) const
{
    if(x >= width_ || y >= height_)
    {
        throw std::out_of_range("OUT OF FILE BUFFER RANGE");
    }
}

// (x, y) rgb value
pnmstream::RGB&
pnmstream::PPMBuffer::
operator ()(size_t x, size_t y)
{
    return pixels_[x + y * width_];
}

// (x, y) rgb value
const pnmstream::RGB&
pnmstream::PPMBuffer::
operator ()(size_t x, size_t y) const
{
    return pixels_[x + y * width_];
}

// check and visit
pnmstream::RGB&
pnmstream::PPMBuffer::
at(size_t x, size_t y)
{
    check_bounds(x, y);
    return (*this)(x, y);
}

// check and visit
const pnmstream::RGB&
pnmstream::PPMBuffer::
at(size_t x, size_t y) const
{
    check_bounds(x, y);
    return (*this)(x, y);
}

// the position
pnmstream::RGB&
pnmstream::PPMBuffer::
operator [](size_t n)
{
    return pixels_[n];
}

const pnmstream::RGB&
pnmstream::PPMBuffer::
operator [](size_t n) const
{
    return pixels_[n];
}

// clear all buffer
void
pnmstream::PPMBuffer::
clear()
{
    pixels_.clear();
}

