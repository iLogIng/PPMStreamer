#pragma once

#include "PNMBuffer.hpp"

#include "../../pixel/Binary.hpp"

namespace pnmstream
{

class PBMBuffer
    : public pnmstream::PNMBuffer<Binary>
{
private:
    buffer_type pixels_;
    size_t width_ = 0;
    size_t height_ = 0;

#pragma region Construction
public:
    PBMBuffer() = default;

    PBMBuffer(size_t width, size_t height, color_type bk_color = color_type::white());

    PBMBuffer(const PBMBuffer&) = delete;
    PBMBuffer& operator =(const PBMBuffer&) = delete;

    PBMBuffer(PBMBuffer&&);
    PBMBuffer& operator =(PBMBuffer&&);

    ~PBMBuffer() = default;

#pragma endregion
public:
    size_t width() const noexcept override;
    size_t height() const noexcept override;
    size_t size() const noexcept override;
    size_t bytes() const noexcept override;
    const color_type* data() const noexcept override;
    color_type* data() noexcept override;
    buffer_type& buffer() noexcept override;
    const buffer_type& buffer() const noexcept override;
    bool empty() const noexcept override;
    void reset(size_t width, size_t height, color_type color = color_type::white()) override;

private:
    void check_bounds(size_t x, size_t y) const override;

#pragma region Buffer Index
public:
    color_type& operator ()(size_t x, size_t y) noexcept override;
    const color_type& operator ()(size_t x, size_t y) const noexcept override;
    color_type& at(size_t x, size_t y) override;
    const color_type& at(size_t x, size_t y) const override;
    color_type& operator [](size_t n) noexcept override;
    const color_type& operator [](size_t n) const noexcept override;
#pragma endregion
public:
    void clear() noexcept override;

};

} // namespace pnmstream
