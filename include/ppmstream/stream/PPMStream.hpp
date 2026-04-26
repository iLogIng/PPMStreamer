#pragma once

#include <iomanip>
#include <fstream>
#include <sstream>

#include <utility>
#include <string>
#include <vector>

#include "PPMBuffer.hpp"
#include "../pixel/Point.hpp"
#include "../pixel/RGB.hpp"

namespace ppmstream
{

enum class OpenMode
{
    // 读文件
    Read = std::ios::binary | std::ios::in,
    // 更改文件
    Alter = std::ios::binary | std::ios::out | std::ios::ate,
    // 写文件
    Write = std::ios::binary | std::ios::out | std::ios::trunc
};  // enum class OpenMode

class PPMStream
{
private:

    std::fstream ppmfs_;                // ppm输入输出流
    ppmstream::PPMBuffer pixels_;       // 像素缓冲

    int color_depth_;                   // 色深
    std::streampos header_size_;        // ppm文件头长度

private:

    // 以差错处理的方式打开文件
    void open_file(const std::string& filename, ppmstream::OpenMode mode = ppmstream::OpenMode::Write);

    // 写 PPM 文件头 (魔数，维度，色深)
    void init_ppm_header(size_t w, size_t h, int c);

public:

    PPMBuffer& buffer();

#pragma region Construction
public:
    explicit PPMStream();

    PPMStream(std::string filename,
        size_t width, size_t heighl,
        int color_depth = 255,
        RGB bk_color = ppmstream::RGB::black(),
        OpenMode mode = OpenMode::Write);

    PPMStream(std::string filename,
        size_t scale, size_t w, size_t h,
        int color_depth = 255,
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
#pragma endregion

#pragma region Stream State
public:

    // normal open ppm file
    PPMStream& open(std::string filename,
        size_t width, size_t height, int color_depth = 255,
        RGB bk_color = ppmstream::RGB::black(),
        ppmstream::OpenMode mode = ppmstream::OpenMode::Write);

    // normal scale open ppm file
    PPMStream& open(std::string filename,
        size_t scale, size_t w, size_t h,
        int color_depth = 255,
        RGB bk_color = ppmstream::RGB::black(),
        ppmstream::OpenMode mode = ppmstream::OpenMode::Write);

    // close the ppm file stream
    void close();

    // is ppm file open
    bool is_open() const;

    // if file at end of file
    bool eof() const;

#pragma endregion

};  // class PPMStream

// verify ppm file msg
void verify_ppm_file(std::string filename, size_t expected_width, size_t expected_height);

}   // namespace ppmstream


