#include "../../include/pnmstream/stream/PPMStream.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

#include <stdint.h>
#include <utility>
#include <stdexcept>
#include <string>
#include <vector>


// write to init the ppm head info
void
pnmstream::PPMStream::
init_ppm_header(size_t w, size_t h, int c)
{
    ppmfs_ << "P6\n";
    ppmfs_ << w << ' ' << h << '\n';
    ppmfs_ << c << '\n';
    ppmfs_.flush();

    header_size_ = ppmfs_.tellp();
}

// open ppm file with exception check
void
pnmstream::PPMStream::
open_file(const std::string& filename, pnmstream::OpenMode mode)
{
    if(ppmfs_.is_open())
    {
        ppmfs_.close();
    }
    ppmfs_.open(filename, static_cast<std::ios::openmode>(mode));
    if(!ppmfs_.is_open())
    {
        throw std::runtime_error("CANNOT OPEN THE PPM FILE: " + filename);
    }
}

// constructor
pnmstream::PPMStream::
PPMStream()
{}

pnmstream::PPMStream::
PPMStream(std::string filename,
    size_t width, size_t height,
    int color_depth, RGB bk_color,
    OpenMode mode)
    : pixels_(width, height, bk_color), color_depth_(color_depth)
{
    open_file(filename, mode);
    init_ppm_header(width, height, color_depth);
}

pnmstream::PPMStream::
PPMStream(std::string filename,
    size_t scale, size_t w, size_t h,
    int color_depth, RGB bk_color,
    OpenMode mode)
    : PPMStream(filename, w * scale, h * scale, color_depth, bk_color, mode)
{ }

pnmstream::PPMStream::
~PPMStream()
{
    close();
}

pnmstream::PPMBuffer&
pnmstream::PPMStream::
buffer()
{
    return this->pixels_;
}

// normal open ppm file
pnmstream::PPMStream&
pnmstream::PPMStream::
open(std::string filename,
    size_t width, size_t height,
    int color_depth, RGB bk_color,
    pnmstream::OpenMode mode)
{
    color_depth_ = color_depth;
    open_file(filename, mode);
    init_ppm_header(width, height, color_depth);

    pixels_.reset(width, height, bk_color);
    return *this;
}

// normal scale open ppm file
pnmstream::PPMStream&
pnmstream::PPMStream::
open(std::string filename,
    size_t scale, size_t w, size_t h,
    int color_depth, RGB bk_color,
    pnmstream::OpenMode mode)
{
    return open(filename, w * scale, h * scale, color_depth, bk_color, mode);
}

// close the ppm file stream
void
pnmstream::PPMStream::
close()
{
    if(ppmfs_.is_open())
    {
        if(!pixels_.empty())
        {
            ppmfs_.seekp(header_size_);
            ppmfs_.write(reinterpret_cast<const char*>(pixels_.data()), pixels_.bytes());
        }
        ppmfs_.close();
    }
}

// is ppm file open
bool
pnmstream::PPMStream::
is_open() const
{
    return ppmfs_.is_open();
}

// if file at end of file
bool
pnmstream::PPMStream::
eof() const
{
    return ppmfs_.eof();
}

pnmstream::ppm_meta_info
pnmstream::
ppm_file_info(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if(!file)
    {
        throw std::runtime_error("CANNOT OPEN THE PPM FILE: " + filename);
    }

    ppm_meta_info meta = {};
    meta.file_size = static_cast<size_t>(file.tellg());
    file.seekg(0);

    auto skip_comments = [&file]()
    {
        while(file.peek() == '#')
        {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    };

    std::getline(file, meta.magic);
    skip_comments();
    file >> meta.width >> meta.height;
    skip_comments();
    file >> meta.color_depth;
    file.ignore();

    std::streampos header_end = file.tellg();
    meta.pixels_size = meta.file_size - static_cast<size_t>(header_end);

    return meta;
}

void
pnmstream::
verify_ppm_file(std::string filename, size_t expected_width, size_t expected_height)
{
    auto meta = ppm_file_info(filename);

    std::cout << "FILE NAME:\t" <<  filename << std::endl;
    std::cout << "FILE SIZE:\t" << meta.file_size << " byte\n";
    std::cout << "PIX DATA SIZE:\t" << meta.pixels_size << " byte\n";
    std::cout << "ABOUT\t" << meta.pixels_size / 3 << " pixes\n";
    std::cout << std::endl;
    std::cout << "EXPECTED WIDTH:\t" << expected_width << " pixes\n";
    std::cout << "EXPECTED HEIGHT:\t" << expected_height << " pixes\n";

    size_t expected_pixel_data_size = expected_width * expected_height * sizeof(RGB);
    std::cout << "EXPECTED PIX DATA SIZE:\t" << expected_pixel_data_size << " byte\n";
    std::cout << "ABOUT\t" << expected_pixel_data_size / 3 << " pixes\n";
    std::cout << std::endl;

    if(meta.pixels_size == expected_pixel_data_size)
    {
        std::cout << "CORRECT FILE SIZE" << std::endl;
    }
    else
    {
        std::cout << "WRONG FILE SIZE" << std::endl;
        if(expected_pixel_data_size > meta.pixels_size)
        {
            std::cout << "LACK:\t" << expected_pixel_data_size - meta.pixels_size << " byte\n";
            std::cout << "LACK PIX:\t" << (expected_pixel_data_size - meta.pixels_size) / 3 << " pixes\n";
        }
    }

    std::cout << std::endl;
}



