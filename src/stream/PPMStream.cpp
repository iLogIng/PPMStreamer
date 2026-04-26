#include "../../include/ppmstream/stream/PPMStream.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <stdint.h>
#include <utility>
#include <stdexcept>
#include <string>
#include <vector>


// set ppm head info filed
void
ppmstream::PPMStream::
set_ppm_dimension(const size_t& width, const size_t& height, int colors)
{
    colors_ = colors;
    pixels_.reset(width, height, ppmstream::RGB::black());
}

// ppm IO stream flush
ppmstream::PPMStream&
ppmstream::PPMStream::
flush()
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
inline void
ppmstream::PPMStream::
init_ppm_file_head(const size_t& w, const size_t& h, const int &c)
{
    ofs_ << "P6\n";
    ofs_ << w << ' ' << h << '\n';
    ofs_ << c << '\n';
    ofs_.flush();
    
    header_size_ = ofs_.tellp();
}

// open ppm file of ofs_
inline void
ppmstream::PPMStream::
raw_open(const std::string& filename, ppmstream::OpenMode mode)
{
    ofs_.open(filename, static_cast<std::ios::openmode>(mode));
}

// open ppm file of ofs_ with exception check
inline void
ppmstream::PPMStream::
exception_open(const std::string& filename, ppmstream::OpenMode mode)
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

// constructor
ppmstream::PPMStream::
PPMStream()
{}

ppmstream::PPMStream::
PPMStream(std::string filename, size_t width, size_t height, int colors, RGB bk_color, OpenMode mode)
    : pixels_(width, height, bk_color), colors_(colors)
{
    this->raw_open(filename, mode);
    init_ppm_file_head(width, height, colors);
}

ppmstream::PPMStream::
PPMStream(std::string filename, size_t scale, size_t w, size_t h, int colors, RGB bk_color, OpenMode mode)
    : PPMStream(filename, w * scale, h * scale, colors, bk_color, mode)
{ }

// destructor
ppmstream::PPMStream::
~PPMStream()
{
    close();
}

// normal open ppm file
ppmstream::PPMStream&
ppmstream::PPMStream::
open(std::string filename, size_t width, size_t height, int colors, RGB bk_color, ppmstream::OpenMode mode)
{
    set_ppm_dimension(width, height, colors);
    this->exception_open(filename, mode);
    init_ppm_file_head(width, height, colors);

    pixels_.reset(width, height, bk_color);
    return *this;
}

// normal scale open ppm file
ppmstream::PPMStream&
ppmstream::PPMStream::
open(std::string filename, size_t scale, size_t w, size_t h, int colors, RGB bk_color, ppmstream::OpenMode mode)
{
    return open(filename, w * scale, h * scale, colors, bk_color, mode);
}

// close the ppm file stream
inline void
ppmstream::PPMStream::
close()
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
bool
ppmstream::PPMStream::
is_open() const
{
    return ofs_.is_open();
}

// if file at end of file
bool
ppmstream::PPMStream::
eof() const
{
    return ofs_.eof();
}

// expose the internal pixel buffer
ppmstream::PPMBuffer&
ppmstream::PPMStream::
buffer()
{
    return pixels_;
}


void
ppmstream::PPMStream::
verify_ppm_file(std::string filename, size_t expected_width, size_t expected_height)
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



