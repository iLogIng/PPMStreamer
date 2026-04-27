# PPMStream

> **Version** v0.2.0 (in progress)
> **Standard** C++17 · **Dependencies** None (C++ standard library only)

A zero-dependency C++ library for PPM image file I/O, pixel buffer management, and raster drawing.

## Features

| Status | Module | Description |
|--------|--------|-------------|
| ✅ | **math** | Vector (`vec2`/`vec3`/`vec4`) and Matrix (`mat2`/`mat3`/`mat4`) templates with arithmetic, dot/cross/outer |
| ✅ | **RGB** | 24-bit RGB pixel with color presets, mixing, grayscale, complementary |
| ✅ | **Point** | 2D coordinate template (`PointI`/`PointF`/`PointD`) |
| ✅ | **PPMBuffer** | Pixel buffer container with bounds-checked access |
| ✅ | **PPMDrawer** | Drawing primitives: point, line (Bresenham), row/column segment, rectangle fill |
| ✅ | **PPMStream** | PPM P6 binary file writer with `ppm_meta_info` / `ppm_file_info()` metadata query |
| 🚧 | **RGBA / Pixel** | RGBA pixel and composited Pixel (color + position) — placeholders |
| ❌ | **PNMStream** | Abstract base for PPM → PAM → PNM extension |
| ❌ | **CMake build** | Currently using hand-written Makefile |
| ❌ | **Tests** | Test suite not yet implemented |
| ❌ | **Pixel data loading** | Reading PPM pixel data not yet implemented |
| ❌ | **Extended formats** | P5 (grayscale), P3 (ASCII), P4 (black/white) |

## Project Structure

```
include/ppmstream/
├── ppmstream.hpp           # Unified entry header
├── math/
│   ├── Vec.hpp             # N-dimensional vector template
│   └── Mat.hpp             # N×N matrix template
├── pixel/
│   ├── RGB.hpp             # RGB pixel + color presets
│   ├── RGBA.hpp            # RGBA pixel (placeholder)
│   ├── Pixel.hpp           # Color + position composite (placeholder)
│   └── Point.hpp           # 2D coordinate template
└── stream/
    ├── PNMStream.hpp       # Abstract base (placeholder)
    ├── PPMStream.hpp       # PPM format read/write stream
    ├── PPMBuffer.hpp       # Pixel memory buffer
    └── PPMDrawer.hpp       # Drawing primitives
```

## Quick Start

```cpp
#include <ppmstream.hpp>
using namespace ppmstream;

PPMStream ppms("output.ppm", 800, 600, 255);
PPMDrawer drawer(ppms.buffer());

// Draw a red diagonal line
drawer.draw_line({0, 0}, {799, 599}, RGB::red());

// Fill a blue rectangle
drawer.fill_rectangle({100, 100}, 200, 150, RGB::blue());

ppms.close();  // flush pixels to file
```

## Type Aliases

```cpp
// math
using vec2f = Vector<float, 2>;  using vec2 = vec2f;
using vec3f = Vector<float, 3>;  using vec3 = vec3f;
using vec4f = Vector<float, 4>;  using vec4 = vec4f;
using mat2f = Matrix<float, 2>;  using mat2 = mat2f;
using mat3f = Matrix<float, 3>;  using mat3 = mat3f;
using mat4f = Matrix<float, 4>;  using mat4 = mat4f;

// pixel
using PointI = Point<int>;
using PointF = Point<float>;
using PointD = Point<double>;
```

## Remaining Work

- [ ] PNMStream abstract base class
- [ ] CMake build system (replacing Makefile)
- [ ] Unit tests
- [ ] PPM pixel data loading (reading)
- [ ] RGBA / Pixel type implementation
- [ ] Extended formats (P5/P3/P4)
- [ ] Image transforms (scale/rotate/crop/flip)
- [ ] Anti-aliased rasterization
