# stream (文件流)

> ***include/pnmstream/stream/PNMStream.hpp***
> ***include/pnmstream/stream/OpenMode.hpp***
>
> PNM（PPM/PGM/PBM）文件读写流模板，通过模板参数 `BufferT` 派生子类。提供 open / read / save / close 完整生命周期管理。
>
> 依赖:
> ***[buffer module](./buffer.md)*** — BufferT 类型参数
> ***\<fstream>***
> ***\<string>***
> ***\<stdexcept>***
>

## 结构

所有定义位于 ***namespace pnmstream*** 命名空间中。

```cpp
template<typename BufferT = PPMBuffer>
class PNMStream {
    using color_type = typename BufferT::color_type;
};
```

`BufferT` 必须是 `PNMBuffer<color_type>` 的子类（`static_assert` 校验）。

---

## PNM 格式特征

通过模板特化 `pnm_format_traits<BufferT>` 描述各格式的差异：

| 特化 | 魔数 | 有色深 |
|------|------|--------|
| `pnm_format_traits<PPMBuffer>` | `"P6"` | 是 |
| `pnm_format_traits<PGMBuffer>` | `"P5"` | 是 |
| `pnm_format_traits<PBMBuffer>` | `"P4"` | 否 |

---

## 构造函数

| 构造方式 | 说明 |
|----------|------|
| `PNMStream()` | 默认构造（空） |
| `PNMStream(filename, width, height, color_depth, bk_color, mode)` | 打开并初始化 |
| `PNMStream(filename, scale, w, h, color_depth, bk_color, mode)` | 等比缩放初始化 |

---

## 成员函数

### 打开/关闭

| 函数 | 返回值 | 说明 |
|------|--------|------|
| `open(filename, w, h, depth, color, mode)` | `PNMStream&` | 写入模式，创建文件 + 写入头信息 |
| `open(filename, scale, w, h, depth, color, mode)` | `PNMStream&` | 等比缩放版本 |
| `read(filename)` | `PNMStream&` | 读取模式，解析头信息 + 加载像素数据 |
| `save()` | `void` | 将缓冲区写入文件（`close` 自动调用） |
| `close()` | `void` | 关闭文件流（自动 `save`） |

### 查询

| 函数 | 返回值 | 说明 |
|------|--------|------|
| `buffer()` | `PNMBuffer<color_type>&` | 缓冲区引用 |
| `is_open()` | `bool` `noexcept` | 文件是否已打开 |
| `eof()` | `bool` `noexcept` | 是否到达文件尾 |

---

## 元信息查询

```cpp
ppm_meta_info ppm_file_info(const std::string& filename);
void verify_ppm_file(const std::string& filename,
                     size_t expected_width,
                     size_t expected_height);
```

### ppm_meta_info

| 字段 | 类型 | 说明 |
|------|------|------|
| `magic` | `std::string` | 魔数字符串 |
| `width` | `size_t` | 图像宽度 |
| `height` | `size_t` | 图像高度 |
| `color_depth` | `int` | 色深 |
| `file_size` | `size_t` | 文件大小 |
| `pixels_size` | `size_t` | 像素数据大小 |

---

## OpenMode

> ***include/pnmstream/stream/OpenMode.hpp***

```cpp
enum class OpenMode {
    Read,   // in | binary
    Write,  // out | binary
    Alter   // in | out | binary
};
```

| 枚举值 | 打开模式 | 用途 |
|--------|----------|------|
| `Read` | `in \| binary` | 只读 |
| `Write` | `out \| binary` | 写入（创建/覆盖） |
| `Alter` | `in \| out \| binary` | 读写（用于 `read` 方法） |

---

## 读写流程

### 写入

```
open() → 写入头信息（魔数 + 宽高 + 色深） → reset 缓冲区 → save()
→ 写入像素数据 → close()
```

### 读取

```
read() → 解析魔数 → 解析宽高 → 解析色深 → 定位像素起始 → reset 缓冲区
→ 读取像素数据（PBM 格式自动按位解包） → close()
```

### 格式特化

- **PPM / PGM**: 二进制格式读写，`buffer_.data()` 直接 `read`/`write`
- **PBM**: 按位打包/解包，每像素 1 bit，每 8 像素打包为 1 字节
