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

    virtual size_t width() const noexcept = 0;
    virtual size_t height() const noexcept = 0;
    virtual size_t size() const noexcept = 0;
    virtual size_t bytes() const noexcept = 0;
    virtual const color_type* data() const noexcept = 0;
    virtual color_type* data() noexcept = 0;
    virtual buffer_type& buffer() noexcept = 0;
    virtual const buffer_type& buffer() const noexcept = 0;
    virtual bool empty() const noexcept = 0;
    virtual void reset(size_t width, size_t height, color_type color) = 0;

private:

    virtual void check_bounds(size_t x, size_t y) const = 0;

#pragma region Buffer Index
public:

    virtual color_type& operator ()(size_t x, size_t y) noexcept = 0;
    virtual const color_type& operator ()(size_t x, size_t y) const noexcept = 0;
    virtual color_type& at(size_t x, size_t y) = 0;
    virtual const color_type& at(size_t x, size_t y) const = 0;
    virtual color_type& operator [](size_t n) noexcept = 0;
    virtual const color_type& operator [](size_t n) const noexcept = 0;

#pragma endregion
public:
    virtual void clear() noexcept = 0;

};

} // namespace pnmstream
