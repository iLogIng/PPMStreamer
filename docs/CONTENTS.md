# 目录 CONTENTS

> pnmstream v0.2.0 | C++17 | 零外部依赖

## Foundation

| 模块 | 模块 | 头文件 |
|------|------|--------|
| [Vector](./math.md) | 向量数学库 | `math/Vec.hpp` |
| [Matrix](./math.md#mat) | 矩阵数学库 | `math/Mat.hpp` |
| [RGB](./pixel.md#rgb) | RGB 色彩模型 | `pixel/RGB.hpp` |
| [RGBA](./pixel.md#rgba) | RGBA 色彩模型 | `pixel/RGBA.hpp` |
| [Grayscale](./pixel.md#grayscale) | 灰度色彩模型 | `pixel/Grayscale.hpp` |
| [Binary](./pixel.md#binary) | 二值色彩模型 | `pixel/Binary.hpp` |
| [Point](./pixel.md#point) | 二维坐标点 | `pixel/Point.hpp` |
| [Pixel](./pixel.md#pixel-class) | 像素（颜色+位置）组合 | `pixel/Pixel.hpp` |

## Buffer & Drawer

| 模块 | 说明 | 头文件 |
|------|------|--------|
| [PNMBuffer](./buffer.md#pnmbuffer) | 缓冲区抽象基类模板 | `stream/buffer/PNMBuffer.hpp` |
| [PPMBuffer](./buffer.md#ppmbuffer) | PPM (P6 RGB) 缓冲区 | `stream/buffer/PPMBuffer.hpp` |
| [PGMBuffer](./buffer.md#pgmbuffer) | PGM (P5 灰度) 缓冲区 | `stream/buffer/PGMBuffer.hpp` |
| [PBMBuffer](./buffer.md#pbmbuffer) | PBM (P4 二值) 缓冲区 | `stream/buffer/PBMBuffer.hpp` |
| [PNMDrawer](./drawer.md) | 通用绘图器 | `stream/PNMDrawer.hpp` |

## Stream

| 模块 | 说明 | 头文件 |
|------|------|--------|
| [PNMStream](./stream.md) | 通用 PNM 流模板 | `stream/PNMStream.hpp` |

