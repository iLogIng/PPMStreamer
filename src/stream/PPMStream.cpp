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


// write to init the ppm head info
void
ppmstream::PPMStream::
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
ppmstream::PPMStream::
open_file(const std::string& filename, ppmstream::OpenMode mode)
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
ppmstream::PPMStream::
PPMStream()
{}

ppmstream::PPMStream::
PPMStream(std::string filename,
    size_t width, size_t height,
    int color_depth, RGB bk_color,
    OpenMode mode)
    : pixels_(width, height, bk_color), color_depth_(color_depth)
{
    open_file(filename, mode);
    init_ppm_header(width, height, color_depth);
}

ppmstream::PPMStream::
PPMStream(std::string filename,
    size_t scale, size_t w, size_t h,
    int color_depth, RGB bk_color,
    OpenMode mode)
    : PPMStream(filename, w * scale, h * scale, color_depth, bk_color, mode)
{ }

ppmstream::PPMStream::
~PPMStream()
{
    close();
}

ppmstream::PPMBuffer&
ppmstream::PPMStream::
buffer()
{
    return this->pixels_;
}

// normal open ppm file
ppmstream::PPMStream&
ppmstream::PPMStream::
open(std::string filename,
    size_t width, size_t height,
    int color_depth, RGB bk_color,
    ppmstream::OpenMode mode)
{
    color_depth_ = color_depth;
    open_file(filename, mode);
    init_ppm_header(width, height, color_depth);

    pixels_.reset(width, height, bk_color);
    return *this;
}

// normal scale open ppm file
ppmstream::PPMStream&
ppmstream::PPMStream::
open(std::string filename,
    size_t scale, size_t w, size_t h,
    int color_depth, RGB bk_color,
    ppmstream::OpenMode mode)
{
    return open(filename, w * scale, h * scale, color_depth, bk_color, mode);
}

// close the ppm file stream
void
ppmstream::PPMStream::
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
ppmstream::PPMStream::
is_open() const
{
    return ppmfs_.is_open();
}

// if file at end of file
bool
ppmstream::PPMStream::
eof() const
{
    return ppmfs_.eof();
}

void
ppmstream::
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
    std::getline(file, header);     // color_depth

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



