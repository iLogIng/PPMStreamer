#include <gtest/gtest.h>
#include "../include/pnmstream/stream/buffer/PPMBuffer.hpp"
#include "../include/pnmstream/stream/buffer/PGMBuffer.hpp"
#include "../include/pnmstream/stream/buffer/PBMBuffer.hpp"
#include "../include/pnmstream/stream/PNMDrawer.hpp"
#include "../include/pnmstream/stream/PNMStream.hpp"

#include <cstdio>
#include <fstream>

// ============================================================
// Buffer: PPMBuffer
// ============================================================

TEST(PPMBufferTest, DefaultConstructor)
{
    using namespace pnmstream;
    PPMBuffer buf;
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.width(), 0u);
    EXPECT_EQ(buf.height(), 0u);
    EXPECT_EQ(buf.size(), 0u);
}

TEST(PPMBufferTest, SizeConstructor)
{
    using namespace pnmstream;
    PPMBuffer buf(4, 4);
    EXPECT_FALSE(buf.empty());
    EXPECT_EQ(buf.width(), 4u);
    EXPECT_EQ(buf.height(), 4u);
    EXPECT_EQ(buf.size(), 16u);
}

TEST(PPMBufferTest, PixelAccess)
{
    using namespace pnmstream;
    PPMBuffer buf(2, 2);
    buf(0, 0) = RGB::red();
    buf(1, 1) = RGB::blue();
    EXPECT_EQ(buf(0, 0), RGB::red());
    EXPECT_EQ(buf(1, 1), RGB::blue());
}

TEST(PPMBufferTest, BoundsCheck)
{
    using namespace pnmstream;
    PPMBuffer buf(4, 4);
    EXPECT_THROW(buf.at(4, 0), std::out_of_range);
    EXPECT_THROW(buf.at(0, 4), std::out_of_range);
    EXPECT_NO_THROW(buf.at(3, 3));
}

TEST(PPMBufferTest, SubscriptOperator)
{
    using namespace pnmstream;
    PPMBuffer buf(2, 2);
    buf[0] = RGB::red();
    buf[3] = RGB::blue();
    EXPECT_EQ(buf[0], RGB::red());
    EXPECT_EQ(buf[3], RGB::blue());
}

TEST(PPMBufferTest, DataPointer)
{
    using namespace pnmstream;
    PPMBuffer buf(4, 4);
    EXPECT_NE(buf.data(), nullptr);
    EXPECT_EQ(buf.bytes(), 16u * sizeof(RGB));
}

TEST(PPMBufferTest, MoveConstructor)
{
    using namespace pnmstream;
    PPMBuffer buf0(4, 4);
    buf0(0, 0) = RGB::red();
    PPMBuffer buf1(std::move(buf0));
    EXPECT_EQ(buf1(0, 0), RGB::red());
    EXPECT_EQ(buf1.width(), 4u);
    EXPECT_EQ(buf1.height(), 4u);
}

TEST(PPMBufferTest, Reset)
{
    using namespace pnmstream;
    PPMBuffer buf(4, 4);
    buf(0, 0) = RGB::red();
    buf.reset(2, 2, RGB::green());
    EXPECT_EQ(buf.width(), 2u);
    EXPECT_EQ(buf.height(), 2u);
    // all pixels should be green after reset
    EXPECT_EQ(buf(0, 0), RGB::green());
    EXPECT_EQ(buf(1, 1), RGB::green());
}

TEST(PPMBufferTest, Clear)
{
    using namespace pnmstream;
    PPMBuffer buf(4, 4);
    EXPECT_FALSE(buf.empty());
    buf.clear();
    EXPECT_TRUE(buf.empty());
}

TEST(PPMBufferTest, BufferAccess)
{
    using namespace pnmstream;
    PPMBuffer buf(2, 2);
    auto& vec = buf.buffer();
    EXPECT_EQ(vec.size(), 4u);
    vec[0] = RGB::red();
    EXPECT_EQ(buf[0], RGB::red());
}

// ============================================================
// Buffer: PGMBuffer
// ============================================================

TEST(PGMBufferTest, Constructor)
{
    using namespace pnmstream;
    PGMBuffer buf(4, 4);
    EXPECT_EQ(buf.width(), 4u);
    EXPECT_EQ(buf.height(), 4u);
    EXPECT_EQ(buf.size(), 16u);
    EXPECT_EQ(buf.bytes(), 16u * sizeof(Grayscale));
    EXPECT_FALSE(buf.empty());
}

TEST(PGMBufferTest, PixelAccess)
{
    using namespace pnmstream;
    PGMBuffer buf(2, 2);
    buf(0, 0) = Grayscale(0xAB);
    EXPECT_EQ(buf(0, 0).g, 0xAB);
    EXPECT_THROW(buf.at(2, 0), std::out_of_range);
}

TEST(PGMBufferTest, Reset)
{
    using namespace pnmstream;
    PGMBuffer buf(4, 4);
    buf.reset(2, 2, Grayscale(0x80));
    EXPECT_EQ(buf.width(), 2u);
    EXPECT_EQ(buf(0, 0).g, 0x80);
}

// ============================================================
// Buffer: PBMBuffer
// ============================================================

TEST(PBMBufferTest, Constructor)
{
    using namespace pnmstream;
    PBMBuffer buf(4, 4);
    EXPECT_EQ(buf.width(), 4u);
    EXPECT_EQ(buf.height(), 4u);
    EXPECT_EQ(buf.size(), 16u);
    EXPECT_FALSE(buf.empty());
}

TEST(PBMBufferTest, PixelAccess)
{
    using namespace pnmstream;
    PBMBuffer buf(2, 2);
    buf(0, 0) = Binary::black();
    EXPECT_TRUE(buf(0, 0).is_black());
    EXPECT_TRUE(buf(1, 0).is_white());  // default is white
    EXPECT_THROW(buf.at(2, 0), std::out_of_range);
}

TEST(PBMBufferTest, Reset)
{
    using namespace pnmstream;
    PBMBuffer buf(4, 4);
    buf.reset(2, 2, Binary::black());
    EXPECT_EQ(buf.width(), 2u);
    EXPECT_TRUE(buf(0, 0).is_black());
}

// ============================================================
// PNMDrawer
// ============================================================

TEST(PNMDrawerTest, Constructor)
{
    using namespace pnmstream;
    PPMBuffer buf(4, 4);
    PNMDrawer<RGB> drawer(buf);
    (void)drawer;  // construction succeeds
}

TEST(PNMDrawerTest, Redraw)
{
    using namespace pnmstream;
    PPMBuffer buf(4, 4);
    PNMDrawer<RGB> drawer(buf);
    drawer.redraw(RGB::green());
    for(size_t i = 0; i < buf.size(); ++i)
    {
        EXPECT_EQ(buf[i], RGB::green());
    }
}

TEST(PNMDrawerTest, DrawPoint)
{
    using namespace pnmstream;
    PPMBuffer buf(4, 4);
    PNMDrawer<RGB> drawer(buf);
    drawer.draw_point({1, 2}, RGB::red());
    EXPECT_EQ(buf(1, 2), RGB::red());
}

TEST(PNMDrawerTest, DrawPointOutOfBounds)
{
    using namespace pnmstream;
    PPMBuffer buf(4, 4);
    PNMDrawer<RGB> drawer(buf);
    // should not crash
    drawer.draw_point({-1, 0}, RGB::red());
    drawer.draw_point({4, 4}, RGB::red());
}

TEST(PNMDrawerTest, DrawLine)
{
    using namespace pnmstream;
    PPMBuffer buf(5, 5);
    PNMDrawer<RGB> drawer(buf);
    drawer.draw_line({0, 0}, {4, 4}, RGB::red());
    EXPECT_EQ(buf(0, 0), RGB::red());
    EXPECT_EQ(buf(2, 2), RGB::red());
    EXPECT_EQ(buf(4, 4), RGB::red());
}

TEST(PNMDrawerTest, FillRectangle)
{
    using namespace pnmstream;
    PPMBuffer buf(5, 5);
    PNMDrawer<RGB> drawer(buf);
    drawer.fill_rectangle({1, 1}, 3, 3, RGB::red());
    EXPECT_EQ(buf(1, 1), RGB::red());
    EXPECT_EQ(buf(3, 3), RGB::red());
    EXPECT_NE(buf(0, 0), RGB::red());  // outside fill
    EXPECT_NE(buf(4, 4), RGB::red());  // outside fill
}

TEST(PNMDrawerTest, DrawRow)
{
    using namespace pnmstream;
    PPMBuffer buf(5, 5);
    PNMDrawer<RGB> drawer(buf);
    drawer.draw_row({1, 2}, 3, RGB::blue());
    EXPECT_EQ(buf(1, 2), RGB::blue());
    EXPECT_EQ(buf(2, 2), RGB::blue());
    EXPECT_EQ(buf(3, 2), RGB::blue());
    EXPECT_NE(buf(4, 2), RGB::blue());  // beyond length
}

TEST(PNMDrawerTest, DrawCol)
{
    using namespace pnmstream;
    PPMBuffer buf(5, 5);
    PNMDrawer<RGB> drawer(buf);
    drawer.draw_col({2, 1}, 3, RGB::green());
    EXPECT_EQ(buf(2, 1), RGB::green());
    EXPECT_EQ(buf(2, 2), RGB::green());
    EXPECT_EQ(buf(2, 3), RGB::green());
}

// ============================================================
// PNMStream (write-then-read round trip with temp file)
// ============================================================

class PNMStreamTest : public ::testing::Test
{
protected:
    const std::string temp_ppm_ = "/tmp/test_ppmstream_output.ppm";
    const std::string temp_pgm_ = "/tmp/test_ppmstream_output.pgm";
    const std::string temp_pbm_ = "/tmp/test_ppmstream_output.pbm";

    void TearDown() override
    {
        std::remove(temp_ppm_.c_str());
        std::remove(temp_pgm_.c_str());
        std::remove(temp_pbm_.c_str());
    }
};

TEST_F(PNMStreamTest, PPMWriteRead)
{
    using namespace pnmstream;
    {
        PNMStream<PPMBuffer> stream(temp_ppm_, 4, 4, 255, RGB::red());
        EXPECT_TRUE(stream.is_open());
    }  // close triggers save

    // read back
    PNMStream<PPMBuffer> reader;
    reader.read(temp_ppm_);
    EXPECT_EQ(reader.buffer().width(), 4u);
    EXPECT_EQ(reader.buffer().height(), 4u);
    EXPECT_EQ(reader.buffer()(0, 0), RGB::red());
}

TEST_F(PNMStreamTest, PGMWriter)
{
    using namespace pnmstream;
    {
        PNMStream<PGMBuffer> stream(temp_pgm_, 4, 4, 255, Grayscale(0x80));
        EXPECT_TRUE(stream.is_open());
    }

    PNMStream<PGMBuffer> reader;
    reader.read(temp_pgm_);
    EXPECT_EQ(reader.buffer().width(), 4u);
    EXPECT_EQ(reader.buffer().height(), 4u);
    EXPECT_EQ(reader.buffer()(0, 0).g, 0x80);
}

TEST_F(PNMStreamTest, PBMWriter)
{
    using namespace pnmstream;
    {
        PNMStream<PBMBuffer> stream(temp_pbm_, 4, 4, 1, Binary::black());
        EXPECT_TRUE(stream.is_open());
    }

    PNMStream<PBMBuffer> reader;
    reader.read(temp_pbm_);
    EXPECT_EQ(reader.buffer().width(), 4u);
    EXPECT_EQ(reader.buffer().height(), 4u);
    EXPECT_TRUE(reader.buffer()(0, 0).is_black());
}
