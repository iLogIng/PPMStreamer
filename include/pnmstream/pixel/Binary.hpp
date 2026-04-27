#pragma once

#include "RGB.hpp"
#include "RGBA.hpp"
#include "Grayscale.hpp"

namespace pnmstream
{

// 二值色
struct Binary
{

enum class Color
{
    White = 0,
    Black = 1
};

    Color c;

    Binary()
        : c(Color::White)
    { }

    Binary(Color bin)
        : c(bin)
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

};

} // namespace pnmstream
