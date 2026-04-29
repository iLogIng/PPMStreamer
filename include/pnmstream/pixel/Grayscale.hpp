#pragma once

#include <stdint.h>
#include "RGBA.hpp"

namespace pnmstream
{

struct Grayscale
{
    using gray_type = uint8_t;

    gray_type g;

    constexpr static gray_type value_lim(const gray_type& v) noexcept {
        return v < 0xFF ? v : 0xFF;
    }

    constexpr Grayscale() noexcept
        : g(0x00)
    {}

    constexpr Grayscale(gray_type gray) noexcept
        : g(gray)
    {}

    constexpr Grayscale(const Grayscale& gray) noexcept
        : g(gray.g)
    {}

    constexpr Grayscale& operator =(const Grayscale& other) noexcept
    {
        g = other.g;
        return *this;
    }

    constexpr Grayscale(Grayscale&& other) noexcept
        : g(other.g)
    { }

    constexpr Grayscale& operator =(Grayscale&& other) noexcept
    {
        if(&other != this)
        {
            g = other.g;
        }
        return *this;
    }

    ~Grayscale() = default;

    constexpr Grayscale(const RGB& rgb) noexcept
        : g(rgb.gray_scale().r)
    {}
    constexpr Grayscale(const RGBA& rgba) noexcept
        : g(rgba.gray_scale().r)
    {}

    constexpr static Grayscale black() noexcept { return Grayscale{0x00}; }
    constexpr static Grayscale white() noexcept { return Grayscale{0xFF}; }
};

} // namespace pnmstream
