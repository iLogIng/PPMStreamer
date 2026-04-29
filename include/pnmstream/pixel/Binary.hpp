#pragma once

#include <cstdint>
#include "RGB.hpp"
#include "RGBA.hpp"
#include "Grayscale.hpp"

namespace pnmstream
{

// 二值色 (0 = White, 1 = Black)
struct Binary
{
    uint8_t c;

    constexpr Binary() noexcept
        : c(0)
    { }

    constexpr Binary(uint8_t value) noexcept
        : c(value ? 1 : 0)
    { }

    constexpr Binary(const Binary& other) noexcept
        : c(other.c)
    { }

    constexpr Binary& operator =(const Binary& other) noexcept
    {
        c = other.c;
        return *this;
    }

    constexpr Binary(Binary&& other) noexcept
        : c(other.c)
    { }

    constexpr Binary& operator =(Binary&& other) noexcept
    {
        if(&other != this)
        {
            c = other.c;
        }
        return *this;
    }

    ~Binary() = default;

    constexpr Binary(RGB rgb) noexcept : c(rgb.to_int() ? 1 : 0) {}
    constexpr Binary(RGBA rgba) noexcept : c(rgba.to_int() ? 1 : 0) {}
    constexpr Binary(Grayscale gray) noexcept : c(gray.g == gray.black().g ? 1 : 0) {}

    constexpr static Binary white() noexcept { return Binary{0}; }
    constexpr static Binary black() noexcept { return Binary{1}; }

    constexpr bool is_white() const noexcept { return c == 0; }
    constexpr bool is_black() const noexcept { return c != 0; }
};

} // namespace pnmstream
