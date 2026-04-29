# drawer (绘图器)

> ***include/pnmstream/stream/PNMDrawer.hpp***
>
> 通用绘图器模板，通过 `PNMBuffer<color_type>&` 引用操作缓冲区，提供基本图元绘制功能。
>
> 依赖:
> ***[buffer module](./buffer.md)*** — 操作 PNMBuffer
> ***[Point](./pixel.md#point)*** — 坐标参数
>

## 结构

所有定义位于 ***namespace pnmstream*** 命名空间中。

```cpp
template<typename color_type_>
class PNMDrawer {
    using color_type = color_type_;
    PNMBuffer<color_type>& buffer_;  // 绑定的缓冲区
};
```

### 构造函数

| 构造函数 | 说明 |
|----------|------|
| `PNMDrawer(buffer)` | 绑定缓冲区（禁止默认/拷贝/移动构造） |

---

### 绘图方法

| 函数 | 说明 |
|------|------|
| `redraw(color)` | 用指定颜色重绘整个缓冲区 |
| `draw_point(point, color)` | 在 `PointI` 处绘制像素（自动裁剪越界） |
| `draw_line(p0, p1, color)` | Bresenham 直线算法 |
| `draw_row(point, n, color)` | 从 point 开始绘制 n 像素水平线段 |
| `draw_col(point, n, color)` | 从 point 开始绘制 n 像素垂直线段 |
| `fill_rectangle(point, w, h, color)` | 填充矩形 |

所有绘图方法均为 `noexcept`，越界绘制自动裁剪。
