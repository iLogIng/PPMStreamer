#pragma once

#include <stdint.h>
#include <cmath>

#include "RGB.hpp"

namespace pnmstream
{

// RGBA 色彩
struct RGBA
{
    using rgba_type = uint8_t;
    using color_type = uint32_t;

    rgba_type r, g, b, a;    // red green blue alpha channels

    constexpr static rgba_type channel_lim(const rgba_type& c) noexcept
    {
        return c < 0xFF ? c : 0xFF;
    }

    constexpr RGBA() noexcept
        : r(0x00), g(0x00), b(0x00), a(0x00)
    { }

    constexpr RGBA(rgba_type red, rgba_type green, rgba_type blue, rgba_type alpha) noexcept
        : r(red), g(green), b(blue), a(alpha)
    { }

    constexpr RGBA(color_type color) noexcept
        : r((color >> 24) & 0xFF)
        , g((color >> 16) & 0xFF)
        , b((color >> 8) & 0xFF)
        , a(color & 0xFF)
    { }

    constexpr RGBA(const RGBA& other) noexcept
        : r(other.r), g(other.g), b(other.b), a(other.a)
    { }

    constexpr RGBA& operator =(const RGBA& other) noexcept
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        return *this;
    }

    constexpr RGBA(RGBA&& other) noexcept
        : r(other.r), g(other.g), b(other.b), a(other.a)
    { }

    constexpr RGBA& operator =(RGBA&& other) noexcept
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

    ~RGBA() = default;

// ==================================================================

    constexpr static rgba_type float_to_int(float c) noexcept
    {
        return channel_lim(static_cast<rgba_type>(c * 255.0f));
    }

    constexpr static float int_to_float(rgba_type c) noexcept
    {
        return static_cast<float>(c / 255.0f);
    }

    constexpr void reset(rgba_type red, rgba_type green, rgba_type blue, rgba_type alpha) noexcept
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    constexpr void reset(float rf, float gf, float bf, float af) noexcept
    {
        r = float_to_int(rf);
        g = float_to_int(gf);
        b = float_to_int(bf);
        a = float_to_int(af);
    }

    void mix(const RGBA& rth, float t) noexcept
    {
        t = std::max(0.0f, std::min(1.0f, t));
        float k = 1 - t;
        r = static_cast<rgba_type>(r * k + rth.r * t);
        g = static_cast<rgba_type>(g * k + rth.g * t);
        b = static_cast<rgba_type>(b * k + rth.b * t);
        a = static_cast<rgba_type>(a * k + rth.a * t);
    }

    static RGBA mix(const RGBA& a, const RGBA& b, float t) noexcept
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

    constexpr color_type to_int() const noexcept
    {
        return (static_cast<color_type>(r) << 24)
                | (static_cast<color_type>(g) << 16)
                | (static_cast<color_type>(b) << 8)
                | static_cast<color_type>(a);
    }

    constexpr RGBA complementary() const noexcept
    {
        return RGBA(0xFF - r, 0xFF - g, 0xFF - b, a);
    }

    constexpr RGBA gray_scale() const noexcept
    {
        rgba_type gray = static_cast<rgba_type>(0.299f * r + 0.587f * g + 0.114f * b);
        return RGBA(gray, gray, gray, a);
    }

// colors ============================================================

    constexpr static RGBA red()            noexcept { return RGBA(0xFF, 0x00, 0x00, 0xFF); }
    constexpr static RGBA green()          noexcept { return RGBA(0x00, 0xFF, 0x00, 0xFF); }
    constexpr static RGBA blue()           noexcept { return RGBA(0x00, 0x00, 0xFF, 0xFF); }
    constexpr static RGBA yellow()         noexcept { return RGBA(0xFF, 0xFF, 0x00, 0xFF); }
    constexpr static RGBA magenta()        noexcept { return RGBA(0xFF, 0x00, 0xFF, 0xFF); }
    constexpr static RGBA cyan()           noexcept { return RGBA(0x00, 0xFF, 0xFF, 0xFF); }

    constexpr static RGBA white()          noexcept { return RGBA(0xFF, 0xFF, 0xFF, 0xFF); }
    constexpr static RGBA black()          noexcept { return RGBA(0x00, 0x00, 0x00, 0xFF); }
    constexpr static RGBA gray()           noexcept { return RGBA(0x80, 0x80, 0x80, 0xFF); }

    constexpr static RGBA orange()     noexcept { return RGBA(0xFF, 0xA5, 0x00, 0xFF); }
    constexpr static RGBA purple()     noexcept { return RGBA(0x80, 0x00, 0x80, 0xFF); }
    constexpr static RGBA pink()       noexcept { return RGBA(0xFF, 0xC0, 0xCB, 0xFF); }
    constexpr static RGBA brown()      noexcept { return RGBA(0xA5, 0x2A, 0x2A, 0xFF); }
    constexpr static RGBA navy()       noexcept { return RGBA(0x00, 0x00, 0x80, 0xFF); }
    constexpr static RGBA teal()       noexcept { return RGBA(0x00, 0x80, 0x80, 0xFF); }
    constexpr static RGBA olive()      noexcept { return RGBA(0x80, 0x80, 0x00, 0xFF); }
    constexpr static RGBA maroon()     noexcept { return RGBA(0x80, 0x00, 0x00, 0xFF); }
    constexpr static RGBA violet()     noexcept { return RGBA(0xEE, 0x82, 0xEE, 0xFF); }
    constexpr static RGBA indigo()     noexcept { return RGBA(0x4B, 0x00, 0x82, 0xFF); }
    constexpr static RGBA gold()       noexcept { return RGBA(0xFF, 0xD7, 0x00, 0xFF); }
    constexpr static RGBA silver()     noexcept { return RGBA(0xC0, 0xC0, 0xC0, 0xFF); }
    constexpr static RGBA coral()      noexcept { return RGBA(0xFF, 0x7F, 0x50, 0xFF); }
    constexpr static RGBA salmon()     noexcept { return RGBA(0xFA, 0x80, 0x72, 0xFF); }
    constexpr static RGBA lime()       noexcept { return RGBA(0x00, 0xFF, 0x00, 0xFF); }
    constexpr static RGBA turquoise()  noexcept { return RGBA(0x40, 0xE0, 0xD0, 0xFF); }
    constexpr static RGBA lavender()   noexcept { return RGBA(0xE6, 0xE6, 0xFA, 0xFF); }
    constexpr static RGBA chocolate()  noexcept { return RGBA(0xD2, 0x69, 0x1E, 0xFF); }

// conversion =========================================================

    constexpr RGB to_rgb() const noexcept
    {
        return RGB(r, g, b);
    }

    constexpr static RGBA from_rgb(const RGB& rgb, rgba_type alpha = 0xFF) noexcept
    {
        return RGBA(rgb.r, rgb.g, rgb.b, alpha);
    }

};  // class RGBA

} // namespace pnmstream
