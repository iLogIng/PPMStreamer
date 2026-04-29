# buffer (缓冲区)

> ***include/pnmstream/stream/buffer/PNMBuffer.hpp***
> ***include/pnmstream/stream/buffer/PPMBuffer.hpp***
> ***include/pnmstream/stream/buffer/PGMBuffer.hpp***
> ***include/pnmstream/stream/buffer/PBMBuffer.hpp***
>
> 像素缓冲区抽象层。不同 PNM 格式的核心差异在像素存储格式，Buffer 层封装这一差异，上层（Drawer、Stream）通过抽象基类统一访问。
>
> 依赖:
> ***\<vector>***
> ***\<cstddef>***
> ***[pixel module](./pixel.md)***
>

## 结构

所有定义位于 ***namespace pnmstream*** 命名空间中。

```
PNMBuffer<color_type> (abstract)
    │
    ├── PPMBuffer  : PNMBuffer<RGB>       — P6 格式
    ├── PGMBuffer  : PNMBuffer<Grayscale>  — P5 格式
    └── PBMBuffer  : PNMBuffer<Binary>     — P4 格式
```

---

## PNMBuffer

> ***include/pnmstream/stream/buffer/PNMBuffer.hpp***

```cpp
template<typename color_type_>
class PNMBuffer {
    using color_type = color_type_;
    using buffer_type = std::vector<color_type>;
};
```

抽象基类模板，定义像素容器的通用接口。

### 纯虚接口

| 函数 | 返回值 | 说明 |
|------|--------|------|
| `width()` | `size_t` `noexcept` | 图像宽度 |
| `height()` | `size_t` `noexcept` | 图像高度 |
| `size()` | `size_t` `noexcept` | 像素总数 (w × h) |
| `bytes()` | `size_t` `noexcept` | 字节数 |
| `data()` | `color_type*` `noexcept` | 原始数据指针 |
| `buffer()` | `vector&` `noexcept` | 底层容器引用 |
| `empty()` | `bool` `noexcept` | 是否为空 |
| `operator()(x, y)` | `color_type&` `noexcept` | 坐标访问 |
| `at(x, y)` | `color_type&` | 带边界检查的坐标访问 |
| `operator[](n)` | `color_type&` `noexcept` | 下标访问 |
| `reset(w, h, color)` | `void` | 重置缓冲区并填充颜色 |
| `clear()` | `void` `noexcept` | 清空 |

---

## PPMBuffer

> ***include/pnmstream/stream/buffer/PPMBuffer.hpp***

```cpp
class PPMBuffer : public PNMBuffer<RGB>;
```

PPM P6 格式（RGB 888）缓冲区。

### 构造函数

| 构造方式 | 说明 |
|----------|------|
| `PPMBuffer()` | 默认构造（空） |
| `PPMBuffer(w, h, color)` | 指定尺寸，默认黑 |
| `PPMBuffer(PPMBuffer&&)` | 移动构造（禁用拷贝） |

### 默认背景色

`color_type::black()` (0x000000)

---

## PGMBuffer

> ***include/pnmstream/stream/buffer/PGMBuffer.hpp***

```cpp
class PGMBuffer : public PNMBuffer<Grayscale>;
```

PGM P5 格式（灰度）缓冲区。

### 构造函数

| 构造方式 | 说明 |
|----------|------|
| `PGMBuffer()` | 默认构造（空） |
| `PGMBuffer(w, h, color)` | 指定尺寸，默认黑 |
| `PGMBuffer(PGMBuffer&&)` | 移动构造（禁用拷贝） |

### 默认背景色

`color_type::black()` (0x00)

---

## PBMBuffer

> ***include/pnmstream/stream/buffer/PBMBuffer.hpp***

```cpp
class PBMBuffer : public PNMBuffer<Binary>;
```

PBM P4 格式（二值）缓冲区。

### 构造函数

| 构造方式 | 说明 |
|----------|------|
| `PBMBuffer()` | 默认构造（空） |
| `PBMBuffer(w, h, color)` | 指定尺寸，默认白 |
| `PBMBuffer(PBMBuffer&&)` | 移动构造（禁用拷贝） |

### 默认背景色

`color_type::white()`

### 注意事项

- PBM 采用"0 白 1 黑"约定
- 文件存储按位打包（每像素 1 bit），`PNMStream` 读写时自动打包/解包
