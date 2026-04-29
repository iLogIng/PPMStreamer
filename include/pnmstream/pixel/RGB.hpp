#pragma once

#include <stdint.h>
#include <cmath>

namespace pnmstream
{

// RGB 色彩
struct RGB
{
    using rgb_type = uint8_t;
    using color_type = uint32_t;

    rgb_type r, g, b;    // red green blue channels

    constexpr static rgb_type channel_lim(const rgb_type& c) noexcept
    {
        return c < 0xFF ? c : 0xFF;
    }

    constexpr RGB() noexcept
        : r(0x00), g(0x00), b(0x00)
    { }

    constexpr RGB(rgb_type red, rgb_type green, rgb_type blue) noexcept
        : r(red), g(green), b(blue)
    { }

    constexpr RGB(color_type color) noexcept
        : r((color >> 16) & 0xFF),
        g((color >> 8) & 0xFF),
        b(color & 0xFF)
    { }

    constexpr RGB(const RGB& other) noexcept
        : r(other.r), g(other.g), b(other.b)
    { }

    constexpr RGB& operator =(const RGB& other) noexcept
    {
        r = other.r;
        g = other.g;
        b = other.b;
        return *this;
    }

    constexpr RGB(RGB&& other) noexcept
        : r(other.r), g(other.g), b(other.b)
    { }

    constexpr RGB& operator =(RGB&& other) noexcept
    {
        if(&other != this)
        {
            r = other.r;
            g = other.g;
            b = other.b;
        }
        return *this;
    }

    ~RGB() = default;

    constexpr bool operator ==(const RGB& other) const noexcept
    {
        return r == other.r && g == other.g && b == other.b;
    }

    constexpr bool operator !=(const RGB& other) const noexcept
    {
        return !(*this == other);
    }

// ==================================================================

    constexpr static rgb_type float_to_int(float c) noexcept
    {
        return channel_lim(static_cast<rgb_type>(c * 255.0f));
    }

    constexpr static float int_to_float(rgb_type c) noexcept
    {
        return static_cast<float>(c / 255.0f);
    }

    constexpr void reset(rgb_type red, rgb_type green, rgb_type blue) noexcept
    {
        r = red;
        g = green;
        b = blue;
    }

    constexpr void reset(float rf, float gf, float bf) noexcept
    {
        r = float_to_int(rf);
        g = float_to_int(gf);
        b = float_to_int(bf);
    }

    void mix(const RGB& rth, float t) noexcept
    {
        t = std::max(0.0f, std::min(1.0f, t));
        float k = 1 - t;
        r = static_cast<rgb_type>(r * k + rth.r * t);
        g = static_cast<rgb_type>(g * k + rth.g * t);
        b = static_cast<rgb_type>(b * k + rth.b * t);
    }

    static RGB mix(const RGB& a, const RGB& b, float t) noexcept
    {
        t = std::max(0.0f, std::min(1.0f, t));
        float k = 1 - t;
        return RGB({
            static_cast<rgb_type>(a.r * k + b.r * t),
            static_cast<rgb_type>(a.g * k + b.g * t),
            static_cast<rgb_type>(a.b * k + b.b * t)
        });
    }

    constexpr color_type to_int() const noexcept
    {
        return (static_cast<color_type>(r) << 16)
                | (static_cast<color_type>(g) << 8)
                | static_cast<color_type>(b);
    }

    constexpr RGB complementary() const noexcept
    {
        return RGB(0xFF - r, 0xFF - g, 0xFF - b);
    }

    constexpr RGB gray_scale() const noexcept
    {
        rgb_type gray = static_cast<rgb_type>(0.299f * r + 0.587f * g + 0.114f * b);
        return RGB(gray, gray, gray);
    }

// colors ============================================================

    constexpr static RGB red()            noexcept { return RGB(0xFF, 0x00, 0x00); }
    constexpr static RGB green()          noexcept { return RGB(0x00, 0xFF, 0x00); }
    constexpr static RGB blue()           noexcept { return RGB(0x00, 0x00, 0xFF); }
    constexpr static RGB yellow()         noexcept { return RGB(0xFF, 0xFF, 0x00); }
    constexpr static RGB magenta()        noexcept { return RGB(0xFF, 0x00, 0xFF); }
    constexpr static RGB cyan()           noexcept { return RGB(0x00, 0xFF, 0xFF); }

    constexpr static RGB white()          noexcept { return RGB(0xFF, 0xFF, 0xFF); }
    constexpr static RGB black()          noexcept { return RGB(0x00, 0x00, 0x00); }
    constexpr static RGB gray()           noexcept { return RGB(0x80, 0x80, 0x80); }

    constexpr static RGB orange()     noexcept { return RGB(0xFF, 0xA5, 0x00); }
    constexpr static RGB purple()     noexcept { return RGB(0x80, 0x00, 0x80); }
    constexpr static RGB pink()       noexcept { return RGB(0xFF, 0xC0, 0xCB); }
    constexpr static RGB brown()      noexcept { return RGB(0xA5, 0x2A, 0x2A); }
    constexpr static RGB navy()       noexcept { return RGB(0x00, 0x00, 0x80); }
    constexpr static RGB teal()       noexcept { return RGB(0x00, 0x80, 0x80); }
    constexpr static RGB olive()      noexcept { return RGB(0x80, 0x80, 0x00); }
    constexpr static RGB maroon()     noexcept { return RGB(0x80, 0x00, 0x00); }
    constexpr static RGB violet()     noexcept { return RGB(0xEE, 0x82, 0xEE); }
    constexpr static RGB indigo()     noexcept { return RGB(0x4B, 0x00, 0x82); }
    constexpr static RGB gold()       noexcept { return RGB(0xFF, 0xD7, 0x00); }
    constexpr static RGB silver()     noexcept { return RGB(0xC0, 0xC0, 0xC0); }
    constexpr static RGB coral()      noexcept { return RGB(0xFF, 0x7F, 0x50); }
    constexpr static RGB salmon()     noexcept { return RGB(0xFA, 0x80, 0x72); }
    constexpr static RGB lime()       noexcept { return RGB(0x00, 0xFF, 0x00); }
    constexpr static RGB turquoise()  noexcept { return RGB(0x40, 0xE0, 0xD0); }
    constexpr static RGB lavender()   noexcept { return RGB(0xE6, 0xE6, 0xFA); }
    constexpr static RGB chocolate()  noexcept { return RGB(0xD2, 0x69, 0x1E); }

};  // class RGB

}   // namespace pnmstream
