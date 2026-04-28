# TODO

## 核心功能
- [x] PPM 文件读取（PNMStream::read()）
- [x] PPMStream → PNMStream 模板重构
- [x] CMake 构建系统
- [x] pnmstream.hpp 统一入口头文件
- [x] PGMBuffer (P5 灰度)
- [x] PBMBuffer (P4 二值 — 展开存储，PNMStream I/O 特化打包)

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
- [x] P5（PGM 灰度）
- [x] P4（PBM 二值）
- [ ] P3（ASCII PPM）
- [ ] PAM 格式

## 质量
- [x] 代码分离（.hpp + .cpp）
- [x] PPMDrawer 解耦（引用 PPMBuffer）
- [x] PPMBuffer 瘦身（移除绘图操作）
- [x] PNMDrawer 泛型化（模板）
- [x] Binary 像素类型（uint8_t 成员）
- [ ] 单元测试
- [ ] noexcept / constexpr 标注
- [ ] ffmpeg 调用解耦为独立脚本
