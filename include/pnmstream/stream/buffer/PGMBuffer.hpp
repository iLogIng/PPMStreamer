#pragma once

#include "PNMBuffer.hpp"

#include "../../pixel/Grayscale.hpp"

namespace pnmstream
{

class PGMBuffer
    : public pnmstream::PNMBuffer<Grayscale>
{
private:
    buffer_type pixels_;
    size_t width_ = 0;
    size_t height_ = 0;

#pragma region Construction
public:
    PGMBuffer() = default;

    PGMBuffer(size_t width, size_t height, color_type bk_color = color_type::black());

    PGMBuffer(const PGMBuffer&) = delete;
    PGMBuffer& operator =(const PGMBuffer&) = delete;

    PGMBuffer(PGMBuffer&&);
    PGMBuffer& operator =(PGMBuffer&&);

    ~PGMBuffer() = default;

#pragma endregion
public:
    size_t width() const noexcept override;
    size_t height() const noexcept override;
    size_t bytes() const override;
    size_t size() const override;
    const color_type* data() const noexcept override;
    color_type* data() noexcept override;
    buffer_type& buffer() noexcept override;
    const buffer_type& buffer() const noexcept override;
    bool empty() const noexcept override;
    void reset(size_t width, size_t height, color_type color = color_type::black()) override;

private:
    void check_bounds(size_t x, size_t y) const override;

#pragma region Buffer Index
public:

    color_type& operator ()(size_t x, size_t y) override;
    const color_type& operator ()(size_t x, size_t y) const override;
    color_type& at(size_t x, size_t y) override;
    const color_type& at(size_t x, size_t y) const override;
    color_type& operator [](size_t n) override;
    const color_type& operator [](size_t n) const override;
#pragma endregion
public:
    void clear() override;

};

} // namespace pnmstream
