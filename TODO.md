# TODO

## 核心功能
- [ ] PPM 文件读取（ifs_ + read_pixel + save）
- [ ] PNMStream 抽象基类（PPM → PAM → PNM 扩展）
- [ ] CMake 构建系统
- [ ] ppmstream.hpp 统一入口头文件

## 绘图能力
- [x] draw_point / draw_line（Bresenham）
- [x] draw_rectangle
- [x] fill_rect / fill_row / fill_col
- [ ] 三角形光栅化
- [ ] 画圆（Bresenham）
- [ ] 抗锯齿（SSAA / MSAA）
- [ ] 卷积滤波

## 图像变换
- [ ] 缩放 / 旋转 / 裁剪 / 翻转

## 格式扩展
- [ ] RGBA / Pixel 类型（PAM 准备）
- [ ] P5（灰度）/ P3（ASCII）/ P4（黑白）

## 质量
- [x] 代码分离（.hpp + .cpp）
- [x] PPMDrawer 解耦（引用 PPMBuffer）
- [x] PPMBuffer 瘦身（移除绘图操作）
- [x] draw_rectangle 补齐实现
- [ ] 单元测试
- [ ] noexcept / constexpr 标注
- [ ] 命名空间 closing 注释修正
- [ ] ffmpeg 调用解耦为独立脚本
