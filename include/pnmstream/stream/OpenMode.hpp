#pragma once

#include <fstream>

namespace pnmstream
{

enum class OpenMode
{
    // 更改文件
    Alter = std::ios::binary | std::ios::out | std::ios::ate,
    // 写文件
    Write = std::ios::binary | std::ios::out | std::ios::trunc
};  // enum class OpenMode

} // namespace pnmstream