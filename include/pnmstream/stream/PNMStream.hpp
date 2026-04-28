#pragma once

#include "OpenMode.hpp"
#include "buffer/PNMBuffer.hpp"
#include "buffer/PPMBuffer.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <type_traits>
#include <stdexcept>

namespace pnmstream
{

// PNM format traits 扩展新格式时特化该模板
template<typename BufferT>
struct pnm_format_traits;

template<>
struct pnm_format_traits<PPMBuffer>
{
    static constexpr const char* magic = "P6";
    static constexpr bool has_color_depth = true;
};

// PPM 文件元信息结构
struct ppm_meta_info
{
    std::string magic;
    size_t width = 0;
    size_t height = 0;
    int color_depth = 0;
    size_t file_size = 0;
    size_t pixels_size = 0;
};

ppm_meta_info ppm_file_info(const std::string& filename);
void verify_ppm_file(const std::string& filename, size_t expected_width, size_t expected_height);

// 通用 PNMStream 模板
template<typename BufferT = PPMBuffer>
class PNMStream
{
    static_assert(std::is_base_of_v<PNMBuffer<typename BufferT::color_type>, BufferT>,
                  "BufferT must derive from PNMBuffer<color_type>");

public:
    using color_type = typename BufferT::color_type;

private:
    std::fstream file_;
    BufferT buffer_;
    int color_depth_ = 255;
    std::streampos header_size_ = 0;

private:
    void open_file(const std::string& filename, OpenMode mode);
    void init_header(size_t w, size_t h, int c);
    void skip_header_ws();

public:
    PNMStream() = default;

    PNMStream(const std::string& filename,
              size_t width, size_t height,
              int color_depth = 255,
              color_type bk_color = color_type{},
              OpenMode mode = OpenMode::Write);

    PNMStream(const std::string& filename,
              size_t scale, size_t w, size_t h,
              int color_depth = 255,
              color_type bk_color = color_type{},
              OpenMode mode = OpenMode::Write);

    PNMStream(const PNMStream&) = delete;
    PNMStream& operator=(const PNMStream&) = delete;

    ~PNMStream();

    // 写入模式，创建/打开文件，写入头信息
    PNMStream& open(const std::string& filename,
                    size_t width, size_t height,
                    int color_depth = 255,
                    color_type bk_color = color_type{},
                    OpenMode mode = OpenMode::Write);

    PNMStream& open(const std::string& filename,
                    size_t scale, size_t w, size_t h,
                    int color_depth = 255,
                    color_type bk_color = color_type{},
                    OpenMode mode = OpenMode::Write);

    // 读取模式，打开文件，解析头信息，加载像素数据
    PNMStream& read(const std::string& filename);

    // 保存，将缓冲写入文件
    void save();

    // 关闭文件流，自动保存
    void close();

    PNMBuffer<color_type>& buffer();
    const PNMBuffer<color_type>& buffer() const;

    bool is_open() const;
    bool eof() const;
};

// = = = = = = = =

template<typename BufferT>
PNMStream<BufferT>::
PNMStream(const std::string& filename,
          size_t width, size_t height,
          int color_depth, color_type bk_color,
          OpenMode mode)
    : color_depth_(color_depth)
{
    open_file(filename, mode);
    init_header(width, height, color_depth);
    buffer_.reset(width, height, bk_color);
}

template<typename BufferT>
PNMStream<BufferT>::
PNMStream(const std::string& filename,
          size_t scale, size_t w, size_t h,
          int color_depth, color_type bk_color,
          OpenMode mode)
    : PNMStream(filename, w * scale, h * scale, color_depth, bk_color, mode)
{}

template<typename BufferT>
PNMStream<BufferT>::
~PNMStream()
{
    close();
}

template<typename BufferT>
void
PNMStream<BufferT>::
open_file(const std::string& filename, OpenMode mode)
{
    if(file_.is_open())
    {
        file_.close();
    }
    file_.open(filename, static_cast<std::ios::openmode>(mode));
    if(!file_.is_open())
    {
        throw std::runtime_error("CANNOT OPEN FILE: " + filename);
    }
}

template<typename BufferT>
void
PNMStream<BufferT>::
init_header(size_t w, size_t h, int c)
{
    using traits = pnm_format_traits<BufferT>;

    file_ << traits::magic << '\n';
    file_ << w << ' ' << h << '\n';
    if constexpr(traits::has_color_depth)
    {
        file_ << c << '\n';
    }
    file_.flush();

    header_size_ = file_.tellp();
}

template<typename BufferT>
void
PNMStream<BufferT>::
skip_header_ws()
{
    while(file_.good())
    {
        int c = file_.peek();
        if(c == '#')
        {
            file_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if(std::isspace(c))
        {
            file_.get();
        }
        else
        {
            break;
        }
    }
}

template<typename BufferT>
PNMStream<BufferT>&
PNMStream<BufferT>::
open(const std::string& filename,
     size_t width, size_t height,
     int color_depth, color_type bk_color,
     OpenMode mode)
{
    color_depth_ = color_depth;
    open_file(filename, mode);
    init_header(width, height, color_depth);
    buffer_.reset(width, height, bk_color);
    return *this;
}

template<typename BufferT>
PNMStream<BufferT>&
PNMStream<BufferT>::
open(const std::string& filename,
     size_t scale, size_t w, size_t h,
     int color_depth, color_type bk_color,
     OpenMode mode)
{
    return open(filename, w * scale, h * scale, color_depth, bk_color, mode);
}

template<typename BufferT>
PNMStream<BufferT>&
PNMStream<BufferT>::
read(const std::string& filename)
{
    using traits = pnm_format_traits<BufferT>;

    // 以 Alter 模式打开（in|out|binary）
    open_file(filename, OpenMode::Alter);

    // 读取魔数
    std::string magic;
    std::getline(file_, magic);
    if(!magic.empty() && magic.back() == '\r')
    {
        magic.pop_back();
    }
    if(magic != traits::magic)
    {
        throw std::runtime_error("UNEXPECTED MAGIC NUMBER: " + magic
                                 + " (expected " + traits::magic + ")");
    }

    // 读取宽、高
    skip_header_ws();
    size_t w = 0, h = 0;
    file_ >> w;
    skip_header_ws();
    file_ >> h;

    // 读取色深
    skip_header_ws();
    if constexpr(traits::has_color_depth)
    {
        file_ >> color_depth_;
    }

    // 定位到像素数据起始位置
    file_ >> std::ws;
    header_size_ = file_.tellg();

    // 重置缓冲并读取像素数据
    buffer_.reset(w, h);
    file_.read(reinterpret_cast<char*>(buffer_.data()), buffer_.bytes());

    if(!file_)
    {
        throw std::runtime_error("FAILED TO READ PIXEL DATA FROM: " + filename);
    }

    return *this;
}

template<typename BufferT>
void
PNMStream<BufferT>::
save()
{
    if(file_.is_open() && !buffer_.empty())
    {
        file_.seekp(header_size_);
        file_.write(reinterpret_cast<const char*>(buffer_.data()), buffer_.bytes());
        file_.flush();
    }
}

template<typename BufferT>
void
PNMStream<BufferT>::
close()
{
    if(file_.is_open())
    {
        save();
        file_.close();
    }
}

template<typename BufferT>
PNMBuffer<typename BufferT::color_type>&
PNMStream<BufferT>::
buffer()
{
    return buffer_;
}

template<typename BufferT>
const PNMBuffer<typename BufferT::color_type>&
PNMStream<BufferT>::
buffer() const
{
    return buffer_;
}

template<typename BufferT>
bool
PNMStream<BufferT>::
is_open() const
{
    return file_.is_open();
}

template<typename BufferT>
bool
PNMStream<BufferT>::
eof() const
{
    return file_.eof();
}

} // namespace pnmstream
