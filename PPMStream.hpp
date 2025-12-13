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
#include "Point.hpp"
#include "RGB.hpp"

namespace ppm
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
public:
class PPMDrawer
{
    friend class PPMStream;
    friend class PPMBuffer;
private:

    // binding the PPMStream
    PPMStream& stream_;

    // constructor
    PPMDrawer(PPMStream& stream)
        : stream_(stream)
    {}

public:
    // constructor
    PPMDrawer() = delete;

    // copy constructor
    PPMDrawer(const PPMDrawer&) = delete;
    PPMDrawer& operator =(const PPMDrawer&) = delete;

    // move constructor
    PPMDrawer(PPMDrawer&&) = delete;
    PPMDrawer& operator =(PPMDrawer&&) = delete;

    // destructor
    ~PPMDrawer() = default;

public:
    // redraw the buffer
    inline void redraw(RGB rgb)
    {
        for(size_t i = 0; i < stream_.pixels_.width() * stream_.pixels_.height(); ++i)
        {
            stream_.pixels_[i] = rgb;
        }
    }

public:
    // draw pixel by (x, y)
    inline void draw_point(PointI point, RGB rgb)
    {
        if(point.x < stream_.pixels_.width() && point.y < stream_.pixels_.height())
        {
            stream_.pixels_(point.x, point.y) = rgb;
        }
    }

    // draw a line
    inline void draw_line(PointI p0, PointI p1, RGB color)
    {
        int dx = abs(p1.x - p0.x);
        int dy = abs(p1.y - p0.y);
        int sx = (p0.x < p1.x) ? 1 : -1;
        int sy = (p0.y < p1.y) ? 1 : -1;
        int err = dx - dy;

        while(true)
        {
            draw_point({p0.x, p0.y}, color);
            if(p0.x == p1.x && p0.y == p1.y)
            {
                break;
            }
            int e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy;
                p0.x += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                p0.y += sy;
            }
        }
    }

    // draw rectangle
    inline void draw_rectangle(PointI p0, PointI p2, RGB color)
    {

    }

};

private:

    std::ofstream ofs_;             // ppm file output stream
    PPMBuffer pixels_;              // pixel buffer

    int colors_;                    // colors of ppm picture
    std::streampos header_size_;    // ppm header size

    PPMDrawer drawer_;              // the graphic drawer

private:

    // set ppm head info filed
    inline void set_ppm_dimension(const size_t& width, const size_t& height, int colors)
    {
        colors_ = colors;
        pixels_.reset(width, height, ppm::RGB::black());
    }

    // ppm IO stream flush
    PPMStream& flush()
    {
        if(!pixels_.empty() && ofs_.is_open())
        {
            ofs_.seekp(header_size_);
            ofs_.write(reinterpret_cast<const char*>(pixels_.data()), pixels_.bytes());
            ofs_.flush();
        }
        return *this;
    }

    // write to init the ppm head info
    inline void init_ppm_file_head(const size_t& w, const size_t& h, const int &c)
    {
        ofs_ << "P6\n";
        ofs_ << w << ' ' << h << '\n';
        ofs_ << c << '\n';
        ofs_.flush();
        
        header_size_ = ofs_.tellp();
    }
    
    // open ppm file of ofs_
    inline void raw_open(const std::string& filename, ppm::OpenMode mode = ppm::OpenMode::Rewrite)
    {
        ofs_.open(filename, static_cast<std::ios::openmode>(mode));
    }

    // open ppm file of ofs_ with exception check
    inline void exception_open(const std::string& filename, ppm::OpenMode mode = ppm::OpenMode::Rewrite)
    {
        if(ofs_.is_open())
        {
            ofs_.close();
        }
        this->raw_open(filename, mode);
        if(!ofs_.is_open())
        {
            throw std::runtime_error("CANNOT OPEN THE PPM FILE: " + filename);
        }
    }

public:
    // constructor
    explicit PPMStream()
        : drawer_(*this)
    {}

    PPMStream(std::string filename, size_t width, size_t height, int colors = 255, RGB bk_color = ppm::RGB::black(),OpenMode mode = OpenMode::Rewrite)
        : pixels_(width, height, bk_color), colors_(colors), drawer_(*this)
    {
        this->raw_open(filename, mode);
        init_ppm_file_head(width, height, colors);
    }

    PPMStream(std::string filename, size_t scale, size_t w, size_t h, int colors = 255, RGB bk_color = ppm::RGB::black(), OpenMode mode = OpenMode::Rewrite)
        : PPMStream(filename, w * scale, h * scale, colors, bk_color, mode)
    { }

    // copy constructor
    PPMStream(const PPMStream&) = delete;
    PPMStream& operator =(const PPMStream&) = delete;

    // move constructor
    PPMStream(PPMStream&& other) = delete;
    PPMStream& operator =(PPMStream&& other) = delete;

    // destructor
    ~PPMStream()
    {
        close();
    }

    // get the drawer
    PPMDrawer& get_drawer()
    {
        return drawer_;
    }

public:

    // normal open ppm file
    inline PPMStream& open(std::string filename, size_t width, size_t height, int colors = 255, RGB bk_color = ppm::RGB::black(), ppm::OpenMode mode = ppm::OpenMode::Rewrite)
    {
        set_ppm_dimension(width, height, colors);
        this->exception_open(filename, mode);
        init_ppm_file_head(width, height, colors);

        pixels_.reset(width, height, bk_color);
        return *this;
    }

    // normal scale open ppm file
    inline PPMStream& open(std::string filename, size_t scale, size_t w, size_t h, int colors = 255, RGB bk_color = ppm::RGB::black(), ppm::OpenMode mode = ppm::OpenMode::Rewrite)
    {
        return open(filename, w * scale, h * scale, colors, bk_color, mode);
    }

    // close the ppm file stream
    inline void close()
    {
        if(ofs_.is_open())
        {
            if(!pixels_.empty())
            {
                ofs_.seekp(header_size_);
                ofs_.write(reinterpret_cast<const char*>(pixels_.data()), pixels_.bytes());
            }
            ofs_.close();
        }
    }

    // is ppm file open
    inline bool is_open() const
    {
        return ofs_.is_open();
    }

    // get pixel position
    inline std::streampos get_pixel_position(size_t x, size_t y) const
    {
        if(x >= pixels_.width() || y >= pixels_.height())
        {
            throw std::runtime_error("pixel out of range");
        }
        return calculate_pixel_offset(x, y);
    }

    // if file at end of file
    inline bool eof() const
    {
        return ofs_.eof();
    }

private:

    // calculate pixel offset
    inline std::streamoff calculate_pixel_offset(size_t x, size_t y) const
    {
        return static_cast<std::streamoff>((x + y * pixels_.width()) * sizeof(RGB));
    }

    // calculate pixel index
    inline std::streamoff calculate_pixel_index(size_t index) const
    {
        return static_cast<std::streamoff>(index * sizeof(RGB));
    }

public:

    // write pixel by (x, y)
    inline PPMStream& write_pixel(size_t x, size_t y, RGB& rgb)
    {
        pixels_(x, y) = rgb;
        return *this;
    }

    // write pixel by (x, y)
    inline PPMStream& write_pixel(size_t x, size_t y, RGB&& rgb)
    {
        pixels_(x, y) = rgb;
        return *this;
    }

public:

    // verify ppm file msg
    static void verify_ppm_file(std::string filename, size_t expected_width, size_t expected_height);

    // valid position
    inline bool is_valid_position(size_t w, size_t h)
    {
        return w < pixels_.width() && h < pixels_.height();
    }

    // total pixels
    inline size_t total_pixels()
    {
        return pixels_.size();
    }

};  // class PPMSstream

// ===============================================================

void PPMStream::verify_ppm_file(std::string filename, size_t expected_width, size_t expected_height)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if(!file)
    {
        std::cerr << "CANNOT OPEN THE PPM FILE" << std::endl;
        return;
    }

    std::streamsize file_size = file.tellg();
    file.seekg(0);

    std::string header;
    std::getline(file, header);     // P6
    std::getline(file, header);     // width height
    std::getline(file, header);     // colors

    std::streampos header_end = file.tellg();
    std::streamsize pixel_data_size = file_size - header_end;
    size_t expected_pixel_data_size = expected_width * expected_height * sizeof(RGB);

    std::cout << "FILE NAME:\t" <<  filename << std::endl;
    std::cout << "FILE SIZE:\t" << file_size << " byte\n";
    std::cout << "HEADER END:\t" << header_end << " byte\n";
    std::cout << "PIX DATA SIZE:\t" << pixel_data_size << " byte\n";
    std::cout << "ABOUT\t" << pixel_data_size / 3 << " pixes\n";
    std::cout << std::endl;
    std::cout << "EXPECTED WIDTH:\t" << expected_width << " pixes\n";
    std::cout << "EXPECTED HEIGHT:\t" << expected_height << " pixes\n";
    std::cout << "EXPECTED PIX DATA SIZE:\t" << expected_pixel_data_size << " byte\n";
    std::cout << "ABOUT\t" << expected_pixel_data_size / 3 << " pixes\n";
    std::cout << std::endl;

    if(pixel_data_size == expected_pixel_data_size)
    {
        std::cout << "CORRECT FILE SIZE" << std::endl;
    }
    else
    {
        std::cout << "WRONG FILE SIZE" << std::endl;
        std::cout << "LACK:\t" << expected_pixel_data_size - pixel_data_size << " byte\n";
        std::cout << "LACK PIX:\t" << (expected_pixel_data_size - pixel_data_size) / 3 << " pixes\n";
    }

    std::cout << std::endl;
}

}   // namespace ppm


