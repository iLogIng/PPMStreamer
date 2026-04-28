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

    Binary()
        : c(0)
    { }

    Binary(uint8_t value)
        : c(value ? 1 : 0)
    { }

    Binary(const Binary& other)
        : c(other.c)
    { }

    Binary& operator =(const Binary& other)
    {
        c = other.c;
        return *this;
    }

    Binary(Binary&& other)
        : c(other.c)
    { }

    Binary& operator =(Binary&& other)
    {
        if(&other != this)
        {
            c = other.c;
        }
        return *this;
    }

    ~Binary() = default;

    static Binary white() { return Binary{0}; }
    static Binary black() { return Binary{1}; }

    bool is_white() const { return c == 0; }
    bool is_black() const { return c != 0; }
};

} // namespace pnmstream
