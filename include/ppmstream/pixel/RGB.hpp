#pragma once

#include <stdint.h>
#include <cmath>

namespace ppmstream
{

struct RGB
{
    using rgb_type = uint8_t;
    using color_type = uint32_t;

    rgb_type r, g, b;    // red green blue channels

    inline static rgb_type channel_lim(const rgb_type& c)
    {
        return c < 0xFF ? c : 0xFF;
    }

    // constructor
    RGB()
        : r(0x00), g(0x00), b(0x00)
    { }

    RGB(rgb_type red, rgb_type green, rgb_type blue)
        : r(red), g(green), b(blue)
    { }

    RGB(color_type color)
        : r((color >> 16) & 0xFF),
        g((color >> 8) & 0xFF),
        b(color & 0xFF)
    { }

    // copy constructor
    RGB(const RGB& other)
        : r(other.r), g(other.g), b(other.b)
    { }

    RGB& operator =(const RGB& other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }

    // move constructor
    RGB(RGB&& other)
        : r(other.r), g(other.g), b(other.b)
    { }

    RGB& operator =(RGB&& other)
    {
        if(&other != this)
        {
            r = other.r;
            g = other.g;
            b = other.b;
        }
        return *this;
    }

    // destructor
    ~RGB() = default;

// ==================================================================

    static rgb_type float_to_int(float c)
    {
        return channel_lim(static_cast<rgb_type>(c * 255.0f));
    }

    static float int_to_float(rgb_type c)
    {
        return static_cast<float>(c / 255.0f);
    }

    // reset the rgb channels
    void reset(rgb_type red, rgb_type green, rgb_type blue)
    {
        r = red;
        g = green;
        b = blue;
    }

    // reset the rgb channels from float
    void reset(float rf, float gf, float bf)
    {
        r = float_to_int(rf);
        g = float_to_int(gf);
        b = float_to_int(bf);
    }

    // channel mix ths * (1 - t) + rth * t
    void mix(const RGB& rth, float t)
    {
        t = std::max(0.0f, std::min(1.0f, t));
        float k = 1 - t;
        r = static_cast<rgb_type>(r * k + rth.r * t);
        g = static_cast<rgb_type>(g * k + rth.g * t);
        b = static_cast<rgb_type>(b * k + rth.b * t);
    }

    // channel mix a * (1 - t) + b * t
    static RGB mix(const RGB& a, const RGB& b, float t)
    {
        t = std::max(0.0f, std::min(1.0f, t));
        float k = 1 - t;
        return RGB({
            static_cast<rgb_type>(a.r * k + b.r * t),
            static_cast<rgb_type>(a.g * k + b.g * t),
            static_cast<rgb_type>(a.b * k + b.b * t)
        });
    }

    color_type to_int() const
    {
        return (static_cast<color_type>(r) << 16)
                | (static_cast<color_type>(g) << 8)
                | static_cast<color_type>(b);
    }

    // 互补色
    RGB complementary() const
    {
        return RGB(0xFF - r, 0xFF - g, 0xFF - b);
    }

    // 灰度
    RGB grey_scale() const
    {
        rgb_type grey = static_cast<rgb_type>(0.299f * r + 0.587f * g + 0.114f * b);
        return RGB(grey, grey, grey);
    }

// colors ============================================================

    static RGB red()            { return RGB(0xFF, 0x00, 0x00); }
    static RGB green()          { return RGB(0x00, 0xFF, 0x00); }
    static RGB blue()           { return RGB(0x00, 0x00, 0xFF); }
    static RGB yellow()         { return RGB(0xFF, 0xFF, 0x00); }
    static RGB magenta()         { return RGB(0xFF, 0x00, 0xFF); }
    static RGB cyan()           { return RGB(0x00, 0xFF, 0xFF); }

    static RGB white()          { return RGB(0xFF, 0xFF, 0xFF); }
    static RGB black()          { return RGB(0x00, 0x00, 0x00); }
    static RGB gray()           { return RGB(0x80, 0x80, 0x80); }

    static RGB orange()     { return RGB(0xFF, 0xA5, 0x00); }
    static RGB purple()     { return RGB(0x80, 0x00, 0x80); }
    static RGB pink()       { return RGB(0xFF, 0xC0, 0xCB); }
    static RGB brown()      { return RGB(0xA5, 0x2A, 0x2A); }
    static RGB navy()       { return RGB(0x00, 0x00, 0x80); }
    static RGB teal()       { return RGB(0x00, 0x80, 0x80); }
    static RGB olive()      { return RGB(0x80, 0x80, 0x00); }
    static RGB maroon()     { return RGB(0x80, 0x00, 0x00); }
    static RGB violet()     { return RGB(0xEE, 0x82, 0xEE); }
    static RGB indigo()     { return RGB(0x4B, 0x00, 0x82); }
    static RGB gold()       { return RGB(0xFF, 0xD7, 0x00); }
    static RGB silver()     { return RGB(0xC0, 0xC0, 0xC0); }
    static RGB coral()      { return RGB(0xFF, 0x7F, 0x50); }
    static RGB salmon()     { return RGB(0xFA, 0x80, 0x72); }
    static RGB lime()       { return RGB(0x00, 0xFF, 0x00); }
    static RGB turquoise()  { return RGB(0x40, 0xE0, 0xD0); }
    static RGB lavender()   { return RGB(0xE6, 0xE6, 0xFA); }
    static RGB chocolate()  { return RGB(0xD2, 0x69, 0x1E); }

};  // class RGB

}   // namespace ppmstream
