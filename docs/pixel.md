# pixel (像素模型)

> ***include/pnmstream/pixel/RGB.hpp***
> ***include/pnmstream/pixel/RGBA.hpp***
> ***include/pnmstream/pixel/Grayscale.hpp***
> ***include/pnmstream/pixel/Binary.hpp***
> ***include/pnmstream/pixel/Point.hpp***
> ***include/pnmstream/pixel/Pixel.hpp***
>
> 色彩模型与坐标点定义，构成 Drawer 和 Buffer 的像素类型基础。
>
> 依赖:
> ***\<cstdint>***
> ***\<cmath>***
> ***\<utility>***
>

## 结构

所有定义位于 ***namespace pnmstream*** 命名空间中。

---

## RGB

> ***include/pnmstream/pixel/RGB.hpp***

```cpp
struct RGB {
    uint8_t r, g, b;
};
```

RGB 888 色彩模型，24 位真彩色。

### 构造函数

| 构造方式 | 说明 |
|----------|------|
| `RGB()` | 默认构造，黑 (0x000000) |
| `RGB(r, g, b)` | 三通道构造 |
| `RGB(color)` | 从 uint32_t 构造：`0x00RRGGBB` |
| `RGB(RGB&&)` / `RGB(const RGB&)` | 移动/拷贝构造 |

### 成员函数

| 函数 | 返回值 | 说明 |
|------|--------|------|
| `to_int()` | `uint32_t` | 打包为 `0x00RRGGBB` |
| `complementary()` | `RGB` | 互补色 (`0xFF - r/g/b`) |
| `gray_scale()` | `RGB` | 灰度化 (亮度权重: 0.299R + 0.587G + 0.114B) |
| `reset(r, g, b)` | `void` | 重置通道值 |
| `reset(rf, gf, bf)` | `void` | 浮点数重置 `[0, 1]` |
| `mix(other, t)` | `void` | 线性插值混合 |

### 静态颜色

`red()` `green()` `blue()` `yellow()` `magenta()` `cyan()`
`white()` `black()` `gray()` `orange()` `purple()` `pink()`
`brown()` `navy()` `teal()` `olive()` `maroon()` `violet()`
`indigo()` `gold()` `silver()` `coral()` `salmon()` `lime()`
`turquoise()` `lavender()` `chocolate()`

---

## RGBA

> ***include/pnmstream/pixel/RGBA.hpp***

```cpp
struct RGBA {
    uint8_t r, g, b, a;
};
```

RGBA 色彩模型，32 位（RGB + Alpha 通道）。

### 构造函数

| 构造方式 | 说明 |
|----------|------|
| `RGBA()` | 默认构造，全 0 |
| `RGBA(r, g, b, a)` | 四通道构造 |
| `RGBA(color)` | 从 uint32_t 构造：`0xRRGGBBAA` |

### 成员函数

| 函数 | 返回值 | 说明 |
|------|--------|------|
| `to_int()` | `uint32_t` | 打包为 `0xRRGGBBAA` |
| `complementary()` | `RGBA` | 互补色（保留 Alpha） |
| `gray_scale()` | `RGBA` | 灰度化（保留 Alpha） |
| `to_rgb()` | `RGB` | 转换为 RGB（丢弃 Alpha） |
| `from_rgb(rgb, alpha)` | `RGBA` | 从 RGB 构造，默认 alpha=0xFF |

---

## Grayscale

> ***include/pnmstream/pixel/Grayscale.hpp***

```cpp
struct Grayscale {
    uint8_t g;
};
```

单通道灰度模型。

### 构造函数

| 构造方式 | 说明 |
|----------|------|
| `Grayscale()` | 默认构造，0x00 |
| `Grayscale(val)` | 灰度值构造 |
| `Grayscale(RGB)` | 从 RGB 自动灰度化 |
| `Grayscale(RGBA)` | 从 RGBA 自动灰度化 |

### 静态颜色

`black()` `white()`

---

## Binary

> ***include/pnmstream/pixel/Binary.hpp***

```cpp
struct Binary {
    uint8_t c;   // 0 = White, 1 = Black
};
```

二值模型，遵循 PBM 约定：0 为白色，1 为黑色。

### 构造函数

| 构造方式 | 说明 |
|----------|------|
| `Binary()` | 默认构造，白色 |
| `Binary(val)` | 从 uint8_t 构造（非零→黑） |
| `Binary(RGB)` | 从 RGB 转换（RGB 非零→黑） |
| `Binary(RGBA)` | 从 RGBA 转换 |
| `Binary(Grayscale)` | 从 Grayscale 转换（黑→黑，白→白） |

### 成员函数

| 函数 | 返回值 | 说明 |
|------|--------|------|
| `is_white()` | `bool` | 是否为白色 |
| `is_black()` | `bool` | 是否为黑色 |

---

## Point

> ***include/pnmstream/pixel/Point.hpp***

```cpp
template<typename Ty>
struct Point {
    Ty x, y;
};
```

二维坐标点模板（整数或浮点）。

### 类型别名

| 类型 | 定义 |
|------|------|
| `PointI` | `Point<int>` |
| `PointF` | `Point<float>` |
| `PointD` | `Point<double>` |

### 构造函数

| 构造方式 | 说明 |
|----------|------|
| `Point()` | 默认构造 (0, 0) |
| `Point(x, y)` | 坐标构造 |
| `Point(pair)` | 从 `std::pair` 构造 |
| `Point(Point<U>&)` | 跨类型转换构造（如 `PointF` → `PointI`） |

---

## Pixel (Class)

> ***include/pnmstream/pixel/Pixel.hpp***

```cpp
template<typename T>
class Pixel {
    Point<T> point_;
    RGBA color_;
};
```

颜色 + 位置组合。用于表示一个带有坐标的像素点。

### 成员函数

| 函数 | 返回值 | 说明 |
|------|--------|------|
| `color()` | `RGBA&` | 颜色引用 |
| `point()` | `Point<T>&` | 坐标引用 |
