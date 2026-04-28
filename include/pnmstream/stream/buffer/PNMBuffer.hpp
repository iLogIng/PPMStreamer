#pragma once

#include <cstddef>
#include <vector>

namespace pnmstream
{

template<typename color_type_>
class PNMBuffer
{
public:
    using color_type = color_type_;
    using buffer_type = std::vector<color_type>;

public:
    virtual ~PNMBuffer() = default;

public:

    virtual size_t width() const = 0;
    virtual size_t height() const = 0;
    virtual size_t size() const = 0;
    virtual size_t bytes() const = 0;
    virtual const color_type* data() const = 0;
    virtual color_type* data() = 0;
    virtual buffer_type& buffer() = 0;
    virtual const buffer_type& buffer() const = 0;
    virtual bool empty() const = 0;
    virtual void reset(size_t width, size_t height, color_type color) = 0;

private:

    virtual void check_bounds(size_t x, size_t y) const = 0;

#pragma region Buffer Index
public:

    virtual color_type& operator ()(size_t x, size_t y) = 0;
    virtual const color_type& operator ()(size_t x, size_t y) const = 0;
    virtual color_type& at(size_t x, size_t y) = 0;
    virtual const color_type& at(size_t x, size_t y) const = 0;
    virtual color_type& operator [](size_t n) = 0;
    virtual const color_type& operator [](size_t n) const = 0;

#pragma endregion
public:
    virtual void clear() = 0;

};

} // namespace pnmstream
