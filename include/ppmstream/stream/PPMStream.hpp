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
#include "../pixel/Point.hpp"
#include "../pixel/RGB.hpp"

namespace ppmstream
{

enum class OpenMode
{
    // Read ppm file
    Read = std::ios::binary | std::ios::in,
    // Alter ppm file
    Alter = std::ios::binary | std::ios::out | std::ios::ate,
    // Write ppm file
    Write = std::ios::binary | std::ios::out | std::ios::trunc
};  // enum class OpenMode

class PPMStream
{
private:

    std::ofstream ofs_;                 // ppm文件输出流
    ppmstream::PPMBuffer pixels_;       // 像素缓冲

    int colors_;                        // 颜色
    std::streampos header_size_;        // ppm文件头长度

private:

    // set ppm head info filed
    void set_ppm_dimension(const size_t& width, const size_t& height, int colors);

    // ppm IO stream flush
    PPMStream& flush();

    // write to init the ppm head info
    void init_ppm_file_head(const size_t& w, const size_t& h, const int &c);

    // open ppm file of ofs_
    void raw_open(const std::string& filename, ppmstream::OpenMode mode = ppmstream::OpenMode::Write);
    
    // open ppm file of ofs_ with exception check
    void exception_open(const std::string& filename, ppmstream::OpenMode mode = ppmstream::OpenMode::Write);

#pragma region Construction
public:
    // constructor
    explicit PPMStream();

    PPMStream(std::string filename,
        size_t width, size_t heighl,
        int colors = 255,
        RGB bk_color = ppmstream::RGB::black(),
        OpenMode mode = OpenMode::Write);

    PPMStream(std::string filename,
        size_t scale, size_t w, size_t h,
        int colors = 255,
        RGB bk_color = ppmstream::RGB::black(),
        OpenMode mode = OpenMode::Write);

    // copy constructor
    PPMStream(const PPMStream&) = delete;
    PPMStream& operator =(const PPMStream&) = delete;

    // move constructor
    PPMStream(PPMStream&& other) = delete;
    PPMStream& operator =(PPMStream&& other) = delete;

    // destructor
    ~PPMStream();

    // access the internal pixel buffer
    PPMBuffer& buffer();
#pragma endregion

public:

    // normal open ppm file
    PPMStream& open(std::string filename,
        size_t width, size_t height, int colors = 255,
        RGB bk_color = ppmstream::RGB::black(),
        ppmstream::OpenMode mode = ppmstream::OpenMode::Write);

    // normal scale open ppm file
    PPMStream& open(std::string filename,
        size_t scale, size_t w, size_t h,
        int colors = 255,
        RGB bk_color = ppmstream::RGB::black(),
        ppmstream::OpenMode mode = ppmstream::OpenMode::Write);

    // close the ppm file stream
    void close();

    // is ppm file open
    bool is_open() const;

    // if file at end of file
    bool eof() const;

public:

    // verify ppm file msg
    void verify_ppm_file(std::string filename, size_t expected_width, size_t expected_height);

};  // class PPMStream

}   // namespace ppmstream


