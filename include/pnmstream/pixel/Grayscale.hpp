#pragma once

#include <stdint.h>
#include "RGBA.hpp"

namespace pnmstream
{

struct Grayscale
{
    using gray_type = uint8_t;

    gray_type g;

    inline static gray_type value_lim(const gray_type& v) {
        return v < 0xFF ? v : 0xFF;
    }

    Grayscale()
        : g(0x00)
    {}

    Grayscale(gray_type gray)
        : g(gray)
    {}

    Grayscale(const Grayscale& gray)
        : g(gray.g)
    {}

    Grayscale& operator =(const Grayscale& other)
    {
        g = other.g;
        return *this;
    }

    Grayscale(Grayscale&& other)
        : g(other.g)
    { }

    Grayscale& operator =(Grayscale&& other)
    {
        if(&other != this)
        {
            g = other.g;
        }
        return *this;
    }

    ~Grayscale() = default;

    Grayscale(const RGB& rgb)
    {
        this->g = rgb.gray_scale().r;
    }
    Grayscale(const RGBA& rgba)
    {
        this->g = rgba.gray_scale().r;
    }


    static Grayscale black() { return Grayscale{0x00}; }
    static Grayscale white() { return Grayscale{0xFF}; }
};

} // namespace pnmstream
