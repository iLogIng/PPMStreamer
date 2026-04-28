#include "../../../include/pnmstream/stream/buffer/PGMBuffer.hpp"

#include <stdexcept>

pnmstream::PGMBuffer::
PGMBuffer(size_t width, size_t height, color_type bk_color)
    : width_(width), height_(height)
{
    pixels_.resize(width * height);
    std::fill(pixels_.begin(), pixels_.end(), bk_color);
}

pnmstream::PGMBuffer::
PGMBuffer(PGMBuffer&& other)
    : pixels_(std::move(other.pixels_))
    , width_(other.width_)
    , height_(other.height_)
{}

pnmstream::PGMBuffer&
pnmstream::PGMBuffer::
operator =(PGMBuffer&& other)
{
    if(&other != this)
    {
        pixels_ = std::move(other.pixels_);
        width_ = other.width_;
        height_ = other.height_;
    }
    return *this;
}

std::size_t
pnmstream::PGMBuffer::
width() const noexcept
{
    return width_;
}

std::size_t
pnmstream::PGMBuffer::
height() const noexcept
{
    return height_;
}

std::size_t
pnmstream::PGMBuffer::
bytes() const
{
    return this->size() * sizeof(color_type);
}

std::size_t
pnmstream::PGMBuffer::
size() const
{
    return pixels_.size();
}

const pnmstream::PGMBuffer::color_type*
pnmstream::PGMBuffer::
data() const noexcept
{
    return pixels_.data();
}

pnmstream::PGMBuffer::color_type*
pnmstream::PGMBuffer::
data() noexcept
{
    return pixels_.data();
}

pnmstream::PGMBuffer::buffer_type&
pnmstream::PGMBuffer::
buffer() noexcept
{
    return pixels_;
}

const pnmstream::PGMBuffer::buffer_type&
pnmstream::PGMBuffer::
buffer() const noexcept
{
    return pixels_;
}

bool
pnmstream::PGMBuffer::
empty() const noexcept
{
    return pixels_.empty();
}

void
pnmstream::PGMBuffer::
reset(size_t width, size_t height, color_type color)
{
    width_ = width;
    height_ = height;
    pixels_.resize(width * height, color);
}

void
pnmstream::PGMBuffer::
check_bounds(size_t x, size_t y) const
{
    if(x >= width_ || y >= height_)
    {
        throw std::out_of_range("OUT OF FILE BUFFER RANGE");
    }
}

pnmstream::PGMBuffer::color_type&
pnmstream::PGMBuffer::
operator ()(size_t x, size_t y)
{
    return pixels_[x + y * width_];
}

const pnmstream::PGMBuffer::color_type&
pnmstream::PGMBuffer::
operator ()(size_t x, size_t y) const
{
    return pixels_[x + y * width_];
}

pnmstream::PGMBuffer::color_type&
pnmstream::PGMBuffer::
at(size_t x, size_t y)
{
    check_bounds(x, y);
    return pixels_.at(x + y * width_);
}

const pnmstream::PGMBuffer::color_type&
pnmstream::PGMBuffer::
at(size_t x, size_t y) const
{
    check_bounds(x, y);
    return pixels_.at(x + y * width_);
}

pnmstream::PGMBuffer::color_type&
pnmstream::PGMBuffer::
operator [](size_t n)
{
    return pixels_[n];
}

const pnmstream::PGMBuffer::color_type&
pnmstream::PGMBuffer::
operator [](size_t n) const
{
    return pixels_[n];
}

void
pnmstream::PGMBuffer::
clear()
{
    pixels_.clear();
}
