#include <gtest/gtest.h>
#include "../include/pnmstream/pixel/RGB.hpp"
#include "../include/pnmstream/pixel/RGBA.hpp"
#include "../include/pnmstream/pixel/Grayscale.hpp"
#include "../include/pnmstream/pixel/Binary.hpp"
#include "../include/pnmstream/pixel/Point.hpp"
#include "../include/pnmstream/pixel/Pixel.hpp"

// ============================================================
// Pixel: RGB
// ============================================================

TEST(RGBTest, DefaultConstructor)
{
    using namespace pnmstream;
    RGB c;
    EXPECT_EQ(c.r, 0x00);
    EXPECT_EQ(c.g, 0x00);
    EXPECT_EQ(c.b, 0x00);
}

TEST(RGBTest, ValueConstructor)
{
    using namespace pnmstream;
    RGB c(0x12, 0x34, 0x56);
    EXPECT_EQ(c.r, 0x12);
    EXPECT_EQ(c.g, 0x34);
    EXPECT_EQ(c.b, 0x56);
}

TEST(RGBTest, ColorConstructor)
{
    using namespace pnmstream;
    RGB c(0x123456u);
    EXPECT_EQ(c.r, 0x12);
    EXPECT_EQ(c.g, 0x34);
    EXPECT_EQ(c.b, 0x56);
}

TEST(RGBTest, CopyConstructor)
{
    using namespace pnmstream;
    RGB c0(0x12, 0x34, 0x56);
    RGB c1(c0);
    EXPECT_EQ(c0, c1);
}

TEST(RGBTest, MoveConstructor)
{
    using namespace pnmstream;
    RGB c0(0x12, 0x34, 0x56);
    RGB c1(std::move(c0));
    EXPECT_EQ(c1.r, 0x12);
    EXPECT_EQ(c1.g, 0x34);
    EXPECT_EQ(c1.b, 0x56);
}

TEST(RGBTest, StaticColors)
{
    using namespace pnmstream;
    EXPECT_EQ(RGB::red(),     RGB(0xFF, 0x00, 0x00));
    EXPECT_EQ(RGB::green(),   RGB(0x00, 0xFF, 0x00));
    EXPECT_EQ(RGB::blue(),    RGB(0x00, 0x00, 0xFF));
    EXPECT_EQ(RGB::white(),   RGB(0xFF, 0xFF, 0xFF));
    EXPECT_EQ(RGB::black(),   RGB(0x00, 0x00, 0x00));
    EXPECT_EQ(RGB::yellow(),  RGB(0xFF, 0xFF, 0x00));
    EXPECT_EQ(RGB::magenta(), RGB(0xFF, 0x00, 0xFF));
    EXPECT_EQ(RGB::cyan(),    RGB(0x00, 0xFF, 0xFF));
}

TEST(RGBTest, ToInt)
{
    using namespace pnmstream;
    RGB c(0x12, 0x34, 0x56);
    EXPECT_EQ(c.to_int(), 0x123456u);
}

TEST(RGBTest, Complementary)
{
    using namespace pnmstream;
    EXPECT_EQ(RGB::white().complementary(), RGB::black());
    EXPECT_EQ(RGB::red().complementary(),   RGB(0x00, 0xFF, 0xFF));
}

TEST(RGBTest, GrayScale)
{
    using namespace pnmstream;
    auto g = RGB::white().gray_scale();
    EXPECT_EQ(g.r, g.g);
    EXPECT_EQ(g.g, g.b);
}

TEST(RGBTest, Reset)
{
    using namespace pnmstream;
    RGB c;
    c.reset(static_cast<uint8_t>(0xAB), static_cast<uint8_t>(0xCD), static_cast<uint8_t>(0xEF));
    EXPECT_EQ(c.r, 0xAB);
    EXPECT_EQ(c.g, 0xCD);
    EXPECT_EQ(c.b, 0xEF);
}

TEST(RGBTest, Equality)
{
    using namespace pnmstream;
    RGB a(0x12, 0x34, 0x56);
    RGB b(0x12, 0x34, 0x56);
    RGB c(0x12, 0x34, 0xFF);
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

// ============================================================
// Pixel: RGBA
// ============================================================

TEST(RGBATest, DefaultConstructor)
{
    using namespace pnmstream;
    RGBA c;
    EXPECT_EQ(c.r, 0x00);
    EXPECT_EQ(c.g, 0x00);
    EXPECT_EQ(c.b, 0x00);
    EXPECT_EQ(c.a, 0x00);
}

TEST(RGBATest, ValueConstructor)
{
    using namespace pnmstream;
    RGBA c(0x12, 0x34, 0x56, 0x78);
    EXPECT_EQ(c.r, 0x12);
    EXPECT_EQ(c.g, 0x34);
    EXPECT_EQ(c.b, 0x56);
    EXPECT_EQ(c.a, 0x78);
}

TEST(RGBATest, ColorConstructor)
{
    using namespace pnmstream;
    RGBA c(0x12345678u);
    EXPECT_EQ(c.r, 0x12);
    EXPECT_EQ(c.g, 0x34);
    EXPECT_EQ(c.b, 0x56);
    EXPECT_EQ(c.a, 0x78);
}

TEST(RGBATest, ToRGB)
{
    using namespace pnmstream;
    RGBA c(0x12, 0x34, 0x56, 0xFF);
    auto rgb = c.to_rgb();
    EXPECT_EQ(rgb.r, 0x12);
    EXPECT_EQ(rgb.g, 0x34);
    EXPECT_EQ(rgb.b, 0x56);
}

TEST(RGBATest, FromRGB)
{
    using namespace pnmstream;
    RGB rgb(0xAB, 0xCD, 0xEF);
    auto rgba = RGBA::from_rgb(rgb, 0x80);
    EXPECT_EQ(rgba.r, 0xAB);
    EXPECT_EQ(rgba.g, 0xCD);
    EXPECT_EQ(rgba.b, 0xEF);
    EXPECT_EQ(rgba.a, 0x80);
}

// ============================================================
// Pixel: Grayscale
// ============================================================

TEST(GrayscaleTest, DefaultConstructor)
{
    using namespace pnmstream;
    Grayscale g;
    EXPECT_EQ(g.g, 0x00);
}

TEST(GrayscaleTest, ValueConstructor)
{
    using namespace pnmstream;
    Grayscale g(0xAB);
    EXPECT_EQ(g.g, 0xAB);
}

TEST(GrayscaleTest, FromRGB)
{
    using namespace pnmstream;
    Grayscale g(RGB(0xFF, 0xFF, 0xFF));
    EXPECT_EQ(g.g, 0xFF);
}

TEST(GrayscaleTest, FromRGBA)
{
    using namespace pnmstream;
    Grayscale g(RGBA(0xFF, 0xFF, 0xFF, 0xFF));
    EXPECT_EQ(g.g, 0xFF);
}

TEST(GrayscaleTest, StaticColors)
{
    using namespace pnmstream;
    EXPECT_EQ(Grayscale::black().g, 0x00);
    EXPECT_EQ(Grayscale::white().g, 0xFF);
}

// ============================================================
// Pixel: Binary
// ============================================================

TEST(BinaryTest, DefaultConstructor)
{
    using namespace pnmstream;
    Binary b;
    EXPECT_TRUE(b.is_white());
}

TEST(BinaryTest, ValueConstructor)
{
    using namespace pnmstream;
    Binary b0(0);
    EXPECT_TRUE(b0.is_white());
    Binary b1(1);
    EXPECT_TRUE(b1.is_black());
    Binary b2(255);
    EXPECT_TRUE(b2.is_black());
}

TEST(BinaryTest, FromRGB)
{
    using namespace pnmstream;
    // PBM: 0=white (no ink), 1=black (ink)
    EXPECT_TRUE(Binary(RGB::black()).is_white());
    EXPECT_TRUE(Binary(RGB::white()).is_black());
}

TEST(BinaryTest, FromRGBA)
{
    using namespace pnmstream;
    // RGBA::black() has alpha=0xFF, so to_int() is non-zero -> black
    EXPECT_TRUE(Binary(RGBA::black()).is_black());
    EXPECT_TRUE(Binary(RGBA::white()).is_black());
}

TEST(BinaryTest, FromGrayscale)
{
    using namespace pnmstream;
    // Grayscale: black(0) == black() -> true -> c=1(black); white(0xFF) == black() -> false -> c=0(white)
    EXPECT_TRUE(Binary(Grayscale::black()).is_black());
    EXPECT_TRUE(Binary(Grayscale::white()).is_white());
}

TEST(BinaryTest, StaticColors)
{
    using namespace pnmstream;
    EXPECT_TRUE(Binary::white().is_white());
    EXPECT_TRUE(Binary::black().is_black());
}

// ============================================================
// Pixel: Point
// ============================================================

TEST(PointTest, DefaultConstructor)
{
    using namespace pnmstream;
    PointI p;
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ValueConstructor)
{
    using namespace pnmstream;
    PointI p(3, 5);
    EXPECT_EQ(p.x, 3);
    EXPECT_EQ(p.y, 5);
}

TEST(PointTest, PairConstructor)
{
    using namespace pnmstream;
    PointI p(std::make_pair(7, 11));
    EXPECT_EQ(p.x, 7);
    EXPECT_EQ(p.y, 11);
}

TEST(PointTest, CopyConstructor)
{
    using namespace pnmstream;
    PointI p0(3, 5);
    PointI p1(p0);
    EXPECT_EQ(p0, p1);
}

TEST(PointTest, ConversionConstructor)
{
    using namespace pnmstream;
    PointF pf(3.5f, 5.7f);
    PointI pi(pf);
    EXPECT_EQ(pi.x, 3);
    EXPECT_EQ(pi.y, 5);
}

TEST(PointTest, Equality)
{
    using namespace pnmstream;
    PointI a(1, 2);
    PointI b(1, 2);
    PointI c(1, 3);
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

// ============================================================
// Pixel: Pixel
// ============================================================

TEST(PixelClassTest, Constructor)
{
    using namespace pnmstream;
    PointI pt(10, 20);
    RGBA col(0xFF, 0x00, 0x00, 0xFF);
    Pixel<int> p(pt, col);
    EXPECT_EQ(p.point(), pt);
    EXPECT_EQ(p.color().r, 0xFF);
    EXPECT_EQ(p.color().g, 0x00);
}

// ============================================================
// Compile-time constexpr checks
// ============================================================

TEST(ConstexprPixelTest, RGBConstexpr)
{
    constexpr pnmstream::RGB c(0x12, 0x34, 0x56);
    constexpr auto comp = c.complementary();
    constexpr auto gray = c.gray_scale();
    constexpr auto hex  = c.to_int();
    static_assert(c.r == 0x12, "constexpr RGB r failed");
    static_assert(comp.r == 0xFF - 0x12, "constexpr complementary failed");
    static_assert(hex == 0x123456u, "constexpr to_int failed");
}

TEST(ConstexprPixelTest, GrayscaleConstexpr)
{
    constexpr pnmstream::Grayscale g(0xAB);
    static_assert(g.g == 0xAB, "constexpr Grayscale failed");
}

TEST(ConstexprPixelTest, BinaryConstexpr)
{
    constexpr pnmstream::Binary bw(1);
    static_assert(bw.is_black(), "constexpr Binary is_black failed");
    static_assert(pnmstream::Binary(0).is_white(), "constexpr Binary is_white failed");
}

TEST(ConstexprPixelTest, PointConstexpr)
{
    constexpr pnmstream::Point<int> p(3, 5);
    static_assert(p.x == 3 && p.y == 5, "constexpr Point failed");
}
