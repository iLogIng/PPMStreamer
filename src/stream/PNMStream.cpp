#include "../../include/pnmstream/stream/PNMStream.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <string>

namespace pnmstream
{

ppm_meta_info
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
verify_ppm_file(const std::string& filename, size_t expected_width, size_t expected_height)
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

} // namespace pnmstream
