#pragma once

#include <stdint.h>
#include <cmath>

#include "RGB.hpp"

namespace ppmstream
{

struct RGBA
{
    using rgba_type = uint8_t;
    using color_type = uint32_t;

    rgba_type r, g, b, a;    // red green blue alpha channels

    inline static rgba_type channel_lim(const rgba_type& c)
    {
        return c < 0xFF ? c : 0xFF;
    }

    // constructor
    RGBA()
        : r(0x00), g(0x00), b(0x00), a(0x00)
    { }

    RGBA(rgba_type red, rgba_type green, rgba_type blue, rgba_type alpha)
        : r(red), g(green), b(blue), a(alpha)
    { }

    RGBA(color_type color)
        : r((color >> 24) & 0xFF)
        , g((color >> 16) & 0xFF)
        , b((color >> 8) & 0xFF)
        , a(color & 0xFF)
    { }

    // copy constructor
    RGBA(const RGBA& other)
        : r(other.r), g(other.g), b(other.b), a(other.a)
    { }

    RGBA& operator =(const RGBA& other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        return *this;
    }

    // move constructor
    RGBA(RGBA&& other)
        : r(other.r), g(other.g), b(other.b), a(other.a)
    { }

    RGBA& operator =(RGBA&& other)
    {
        if(&other != this)
        {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
        }
        return *this;
    }

    // destructor
    ~RGBA() = default;

// ==================================================================

    static rgba_type float_to_int(float c)
    {
        return channel_lim(static_cast<rgba_type>(c * 255.0f));
    }

    static float int_to_float(rgba_type c)
    {
        return static_cast<float>(c / 255.0f);
    }

    // reset the rgb channels
    void reset(rgba_type red, rgba_type green, rgba_type blue, rgba_type alpha)
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    // reset the rgb channels from float
    void reset(float rf, float gf, float bf, float af)
    {
        r = float_to_int(rf);
        g = float_to_int(gf);
        b = float_to_int(bf);
        a = float_to_int(af);
    }

    // channel mix ths * (1 - t) + rth * t
    void mix(const RGBA& rth, float t)
    {
        t = std::max(0.0f, std::min(1.0f, t));
        float k = 1 - t;
        r = static_cast<rgba_type>(r * k + rth.r * t);
        g = static_cast<rgba_type>(g * k + rth.g * t);
        b = static_cast<rgba_type>(b * k + rth.b * t);
        a = static_cast<rgba_type>(a * k + rth.a * t);
    }

    // channel mix a * (1 - t) + b * t
    static RGBA mix(const RGBA& a, const RGBA& b, float t)
    {
        t = std::max(0.0f, std::min(1.0f, t));
        float k = 1 - t;
        return RGBA({
            static_cast<rgba_type>(a.r * k + b.r * t),
            static_cast<rgba_type>(a.g * k + b.g * t),
            static_cast<rgba_type>(a.b * k + b.b * t),
            static_cast<rgba_type>(a.a * k + b.a * t)
        });
    }

    color_type to_int() const
    {
        return (static_cast<color_type>(r) << 24)
                | (static_cast<color_type>(g) << 16)
                | (static_cast<color_type>(b) << 8)
                | static_cast<color_type>(a);
    }

    // 互补色
    RGBA complementary() const
    {
        return RGBA(0xFF - r, 0xFF - g, 0xFF - b, a);
    }

    // 灰度
    RGBA grey_scale() const
    {
        rgba_type grey = static_cast<rgba_type>(0.299f * r + 0.587f * g + 0.114f * b);
        return RGBA(grey, grey, grey, a);
    }

// colors ============================================================

    static RGBA red()            { return RGBA(0xFF, 0x00, 0x00, 0xFF); }
    static RGBA green()          { return RGBA(0x00, 0xFF, 0x00, 0xFF); }
    static RGBA blue()           { return RGBA(0x00, 0x00, 0xFF, 0xFF); }
    static RGBA yellow()         { return RGBA(0xFF, 0xFF, 0x00, 0xFF); }
    static RGBA magenta()        { return RGBA(0xFF, 0x00, 0xFF, 0xFF); }
    static RGBA cyan()           { return RGBA(0x00, 0xFF, 0xFF, 0xFF); }

    static RGBA white()          { return RGBA(0xFF, 0xFF, 0xFF, 0xFF); }
    static RGBA black()          { return RGBA(0x00, 0x00, 0x00, 0xFF); }
    static RGBA gray()           { return RGBA(0x80, 0x80, 0x80, 0xFF); }

    static RGBA orange()     { return RGBA(0xFF, 0xA5, 0x00, 0xFF); }
    static RGBA purple()     { return RGBA(0x80, 0x00, 0x80, 0xFF); }
    static RGBA pink()       { return RGBA(0xFF, 0xC0, 0xCB, 0xFF); }
    static RGBA brown()      { return RGBA(0xA5, 0x2A, 0x2A, 0xFF); }
    static RGBA navy()       { return RGBA(0x00, 0x00, 0x80, 0xFF); }
    static RGBA teal()       { return RGBA(0x00, 0x80, 0x80, 0xFF); }
    static RGBA olive()      { return RGBA(0x80, 0x80, 0x00, 0xFF); }
    static RGBA maroon()     { return RGBA(0x80, 0x00, 0x00, 0xFF); }
    static RGBA violet()     { return RGBA(0xEE, 0x82, 0xEE, 0xFF); }
    static RGBA indigo()     { return RGBA(0x4B, 0x00, 0x82, 0xFF); }
    static RGBA gold()       { return RGBA(0xFF, 0xD7, 0x00, 0xFF); }
    static RGBA silver()     { return RGBA(0xC0, 0xC0, 0xC0, 0xFF); }
    static RGBA coral()      { return RGBA(0xFF, 0x7F, 0x50, 0xFF); }
    static RGBA salmon()     { return RGBA(0xFA, 0x80, 0x72, 0xFF); }
    static RGBA lime()       { return RGBA(0x00, 0xFF, 0x00, 0xFF); }
    static RGBA turquoise()  { return RGBA(0x40, 0xE0, 0xD0, 0xFF); }
    static RGBA lavender()   { return RGBA(0xE6, 0xE6, 0xFA, 0xFF); }
    static RGBA chocolate()  { return RGBA(0xD2, 0x69, 0x1E, 0xFF); }

// conversion =========================================================

    // RGBA → RGB (drop alpha)
    RGB to_rgb() const
    {
        return RGB(r, g, b);
    }

    // RGB → RGBA (add alpha)
    static RGBA from_rgb(const RGB& rgb, rgba_type alpha = 0xFF)
    {
        return RGBA(rgb.r, rgb.g, rgb.b, alpha);
    }

};  // class RGBA
    
} // namespace ppmstream
