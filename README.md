# PPMStream Project
> **VERSION 0.1.0**
> **2025.12.05**

## 项目目的

- 该项目是为了学习计算机图形学而设计的一个PPM文件的文件读写流项目。
- 该项目是为了给计算机图形学学习提供一个编写图形学算法的实践平台。

---

## 文件结构

### 数学库

- **Vec.hpp**
    > 向量
    提供了三个类型 **vec2** **vec3** **vec4** 的模板特化
- **Mat.hpp**
    > 矩阵
    提供了三个类型 **mat2** **mat3** **mat4** 的模板特化

### 图形建模

- **Point.hpp**
    > 点位置
    包装了 **std::pair<Type, Type>** 并提供了与 **std::pair<Type, Type>** 类进行类型转换的特性。
- **RGB.hpp**
    > 像素rgb
    使用结构体包含 **red** **green** **blue** 三个**uint8_t**数据成员

### 读写流

- **PPMStream.hpp**
    > ppm文件读写流
    包装为**PPMStream**类
- **PPMBuffer.hpp**
    > ppm文件读写缓存
    包装为**PPMBuffer**类，组合在**PPMStream**类中进行使用

---

## END
