#pragma once

#include <cstdint>
#include "RGB.hpp"
#include "RGBA.hpp"
#include "Grayscale.hpp"

namespace pnmstream
{

// 二值色 (White = 0, Black = 1) —— 与 PBM 文件位值一致（P4 规范：位 1 为黑，位 0 为白）
inline constexpr uint8_t WHITE = 0;
inline constexpr uint8_t BLACK = 1;

struct Binary
{
    uint8_t c;

    constexpr Binary() noexcept
        : c(WHITE)
    { }

    constexpr Binary(uint8_t value) noexcept
        : c(value ? BLACK : WHITE)
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

    constexpr Binary(RGB rgb) noexcept : c(rgb.to_int() ? BLACK : WHITE) {}
    constexpr Binary(RGBA rgba) noexcept : c(rgba.to_int() ? BLACK : WHITE) {}
    constexpr Binary(Grayscale gray) noexcept : c(gray.g == gray.black().g ? BLACK : WHITE) {}

    constexpr static Binary white() noexcept { return Binary{WHITE}; }
    constexpr static Binary black() noexcept { return Binary{BLACK}; }

    constexpr bool is_white() const noexcept { return c == WHITE; }
    constexpr bool is_black() const noexcept { return c == BLACK; }
};

} // namespace pnmstream
