#include "../../../include/pnmstream/stream/buffer/PBMBuffer.hpp"

#include <stdexcept>

pnmstream::PBMBuffer::
PBMBuffer(size_t width, size_t height, color_type bk_color)
    : width_(width), height_(height)
{
    pixels_.resize(width * height);
    std::fill(pixels_.begin(), pixels_.end(), bk_color);
}

pnmstream::PBMBuffer::
PBMBuffer(PBMBuffer&& other)
    : pixels_(std::move(other.pixels_))
    , width_(other.width_)
    , height_(other.height_)
{}

pnmstream::PBMBuffer&
pnmstream::PBMBuffer::
operator =(PBMBuffer&& other)
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
pnmstream::PBMBuffer::
width() const noexcept
{
    return width_;
}

std::size_t
pnmstream::PBMBuffer::
height() const noexcept
{
    return height_;
}

std::size_t
pnmstream::PBMBuffer::
size() const
{
    return pixels_.size();
}

std::size_t
pnmstream::PBMBuffer::
bytes() const
{
    return this->size() * sizeof(color_type);
}

const pnmstream::PBMBuffer::color_type*
pnmstream::PBMBuffer::
data() const noexcept
{
    return pixels_.data();
}

pnmstream::PBMBuffer::color_type*
pnmstream::PBMBuffer::
data() noexcept
{
    return pixels_.data();
}

pnmstream::PBMBuffer::buffer_type&
pnmstream::PBMBuffer::
buffer() noexcept
{
    return pixels_;
}

const pnmstream::PBMBuffer::buffer_type&
pnmstream::PBMBuffer::
buffer() const noexcept
{
    return pixels_;
}

bool
pnmstream::PBMBuffer::
empty() const noexcept
{
    return pixels_.empty();
}

void
pnmstream::PBMBuffer::
reset(size_t width, size_t height, color_type color)
{
    width_ = width;
    height_ = height;
    pixels_.resize(width * height, color);
}

void
pnmstream::PBMBuffer::
check_bounds(size_t x, size_t y) const
{
    if(x >= width_ || y >= height_)
    {
        throw std::out_of_range("OUT OF FILE BUFFER RANGE");
    }
}

pnmstream::PBMBuffer::color_type&
pnmstream::PBMBuffer::
operator ()(size_t x, size_t y)
{
    return pixels_[x + y * width_];
}

const pnmstream::PBMBuffer::color_type&
pnmstream::PBMBuffer::
operator ()(size_t x, size_t y) const
{
    return pixels_[x + y * width_];
}

pnmstream::PBMBuffer::color_type&
pnmstream::PBMBuffer::
at(size_t x, size_t y)
{
    check_bounds(x, y);
    return (*this)(x, y);
}

const pnmstream::PBMBuffer::color_type&
pnmstream::PBMBuffer::
at(size_t x, size_t y) const
{
    check_bounds(x, y);
    return (*this)(x, y);
}

pnmstream::PBMBuffer::color_type&
pnmstream::PBMBuffer::
operator [](size_t n)
{
    return pixels_[n];
}

const pnmstream::PBMBuffer::color_type&
pnmstream::PBMBuffer::
operator [](size_t n) const
{
    return pixels_[n];
}

void
pnmstream::PBMBuffer::
clear()
{
    pixels_.clear();
}
