# PPMStream

> **版本** v0.2.0（开发中）
> **标准** C++17 · **依赖** 无（仅使用 C++ 标准库）

一个零依赖的 C++ 库，用于 PPM 图像文件读写、像素缓冲区管理以及光栅绘图。

## 特性

| 状态 | 模块 | 描述 |
|--------|--------|-------------|
| ✅ | **math** | 向量（`vec2`/`vec3`/`vec4`）和矩阵（`mat2`/`mat3`/`mat4`）模板，支持算术运算、点积/叉积/外积 |
| ✅ | **RGB** | 24 位 RGB 像素，提供颜色预设、混合、灰度、互补色 |
| ✅ | **Point** | 二维坐标模板（`PointI`/`PointF`/`PointD`） |
| ✅ | **PPMBuffer** | 像素缓冲区容器，带边界检查的访问 |
| ✅ | **PPMDrawer** | 绘图基本操作：点、线段（Bresenham）、行/列片段、矩形填充 |
| ✅ | **PPMStream** | PPM P6 二进制文件写入器，提供 `ppm_meta_info` / `ppm_file_info()` 元数据查询 |
| ✅ | **RGBA / Pixel** | 带 Alpha 通道的 RGBA 像素，以及复合的 Pixel（颜色 + 位置） |
| ❌ | **PNMStream** | 抽象基类，用于 PPM → PAM → PNM 扩展 |
| ❌ | **CMake 构建** | 目前使用手写 Makefile |
| ❌ | **测试** | 测试套件尚未实现 |
| ❌ | **像素数据加载** | 读取 PPM 像素数据尚未实现 |
| ❌ | **扩展格式** | P5（灰度）、P3（ASCII）、P4（黑白） |

## 项目结构

```text
include/ppmstream/
├── ppmstream.hpp           # 统一入口头文件
├── math/
│   ├── Vec.hpp             # N 维向量模板
│   └── Mat.hpp             # N×N 矩阵模板
├── pixel/
│   ├── RGB.hpp             # RGB 像素 + 颜色预设
│   ├── RGBA.hpp            # RGBA 像素（占位）
│   ├── Pixel.hpp           # 颜色 + 位置复合（占位）
│   └── Point.hpp           # 二维坐标模板
└── stream/
    ├── PNMStream.hpp       # 抽象基类（占位）
    ├── PPMStream.hpp       # PPM 格式读写流
    ├── PPMBuffer.hpp       # 像素内存缓冲区
    └── PPMDrawer.hpp       # 绘图基本操作
```

## 快速开始

```cpp
#include <ppmstream.hpp>
using namespace ppmstream;

PPMStream ppms("output.ppm", 800, 600, 255);
PPMDrawer drawer(ppms.buffer());

// 绘制一条红色对角线
drawer.draw_line({0, 0}, {799, 599}, RGB::red());

// 填充一个蓝色矩形
drawer.fill_rectangle({100, 100}, 200, 150, RGB::blue());

// 将像素刷新到文件
ppms.close();
```

## 类型别名

```cpp
// vec
using vec2f = Vector<float, 2>;  using vec2 = vec2f;
using vec3f = Vector<float, 3>;  using vec3 = vec3f;
using vec4f = Vector<float, 4>;  using vec4 = vec4f;
// mat
using mat2f = Matrix<float, 2>;  using mat2 = mat2f;
using mat3f = Matrix<float, 3>;  using mat3 = mat3f;
using mat4f = Matrix<float, 4>;  using mat4 = mat4f;

// point
using PointI = Point<int>;
using PointF = Point<float>;
using PointD = Point<double>;
```

## 待完成工作

- [ ] PNMStream 抽象基类
- [ ] CMake 构建系统（替换 Makefile）
- [ ] 单元测试
- [ ] PPM 像素数据加载（读取）
- [ ] 扩展格式（P5/P3/P4）
- [ ] 图像变换（缩放/旋转/裁剪/翻转）
- [ ] 抗锯齿光栅化