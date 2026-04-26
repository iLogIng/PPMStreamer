#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <stdint.h>
#include <utility>
#include <stdexcept>
#include <string>
#include <vector>

#include "PPMBuffer.hpp"
#include "PPMDrawer.hpp"
#include "../pixel/Point.hpp"
#include "../pixel/RGB.hpp"

namespace ppmstream
{

enum class OpenMode
{
    // rewrite ppm file
    Rewrite = std::ios::binary | std::ios::out | std::ios::trunc,
    // alter ppm file
    Alter = std::ios::binary | std::ios::out | std::ios::ate
};  // enum class OpenMode

class PPMStream
{
    friend class ppmstream::PPMDrawer;
private:

    std::ofstream ofs_;             // ppm file output stream
    ppmstream::PPMBuffer pixels_;              // pixel buffer

    int colors_;                    // colors of ppm picture
    std::streampos header_size_;    // ppm header size

    ppmstream::PPMDrawer drawer_;              // the graphic drawer

private:

    // set ppm head info filed
    void set_ppm_dimension(const size_t& width, const size_t& height, int colors);

    // ppm IO stream flush
    PPMStream& flush();

    // write to init the ppm head info
    void init_ppm_file_head(const size_t& w, const size_t& h, const int &c);

    // open ppm file of ofs_
    void raw_open(const std::string& filename, ppmstream::OpenMode mode = ppmstream::OpenMode::Rewrite);
    
    // open ppm file of ofs_ with exception check
    void exception_open(const std::string& filename, ppmstream::OpenMode mode = ppmstream::OpenMode::Rewrite);

public:
    // constructor
    explicit PPMStream();

    PPMStream(std::string filename, size_t width, size_t height, int colors = 255, RGB bk_color = ppmstream::RGB::black(),OpenMode mode = OpenMode::Rewrite);

    PPMStream(std::string filename, size_t scale, size_t w, size_t h, int colors = 255, RGB bk_color = ppmstream::RGB::black(), OpenMode mode = OpenMode::Rewrite);

    // copy constructor
    PPMStream(const PPMStream&) = delete;
    PPMStream& operator =(const PPMStream&) = delete;

    // move constructor
    PPMStream(PPMStream&& other) = delete;
    PPMStream& operator =(PPMStream&& other) = delete;

    // destructor
    ~PPMStream();

    // get the drawer
    PPMDrawer& get_drawer();

public:

    // normal open ppm file
    PPMStream& open(std::string filename, size_t width, size_t height, int colors = 255, RGB bk_color = ppmstream::RGB::black(), ppmstream::OpenMode mode = ppmstream::OpenMode::Rewrite);

    // normal scale open ppm file
    PPMStream& open(std::string filename, size_t scale, size_t w, size_t h, int colors = 255, RGB bk_color = ppmstream::RGB::black(), ppmstream::OpenMode mode = ppmstream::OpenMode::Rewrite);

    // close the ppm file stream
    void close();

    // is ppm file open
    bool is_open() const;

    // get pixel position
    std::streampos get_pixel_position(size_t x, size_t y) const;

    // if file at end of file
    bool eof() const;

private:

    // calculate pixel offset
    std::streamoff calculate_pixel_offset(size_t x, size_t y) const;

    // calculate pixel index
    std::streamoff calculate_pixel_index(size_t index) const;

public:

    // write pixel by (x, y)
    PPMStream& write_pixel(size_t x, size_t y, RGB& rgb);

    // write pixel by (x, y)
    PPMStream& write_pixel(size_t x, size_t y, RGB&& rgb);

public:

    // verify ppm file msg
    void verify_ppm_file(std::string filename, size_t expected_width, size_t expected_height);

    // valid position
    bool is_valid_position(size_t w, size_t h);

    // total pixels
    size_t total_pixels();

};  // class PPMSstream

// ===============================================================

void verify_ppm_file(std::string filename, size_t expected_width, size_t expected_height);

}   // namespace ppmstream


