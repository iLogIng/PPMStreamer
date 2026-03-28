# PPMStream

> **VERSION 0.1.0**
> **2025.12.05**
>

## 项目简介 Description

**PPMStream** 是一个基于 ***C++11*** 特性，包装 ***iofstream*** 文件读写流，提供 **.ppm** 格式二进制文件读写的库

- 设计背景：.ppm 图像格式很有趣，想包装针对于该格式文件的读写库，以更加简单的进行文件读写编辑。设计初期有考虑过使用该库进行图像处理算法的实践。

-----

## 功能特性 Features

- **数学库**
  - ***Vec.hpp*** 向量类头文件
  - ***Mat.hpp*** 矩阵类头文件
  
- **辅助库**
  - ***RGB.hpp*** RGB像素结构库
  - ***Point.hpp*** 点结构库
  
- **文件读写包装类**
  - ***PPMBuffer.hpp*** 提供 **.ppm** 格式图像文件内存缓冲区的类，目前直接将一张图像映射到一个总像素大小的内存块中
  - ***PPMStream.hpp*** 提供 **.ppm** 格式图像文件的读写流类封装，包装了 ***iofstream*** 文件读写流
    - **PPMStream** 类，提供缓冲区的持久保存
    - **PPMDrawer** 类，是 **PPMStream** 类的一个内部类，目前用于进行真正的缓冲区像素(**PPMBuffer**)读写功能，通过引用将该内部类导出，对唯一文件缓冲区进行读写。

## 快速开始 Getting Start

- **>= C++11**

## 文件结构

```text
.
├── CMakeLists.txt
├── include
│   ├── math
│   │   ├── Mat.hpp
│   │   └── Vec.hpp
│   ├── stream
│   │   ├── PPMBuffer.hpp
│   │   └── PPMStream.hpp
│   └── utils
│       ├── Point.hpp
│       └── RGB.hpp
├── LICENSE
├── main.cpp
├── makefile
├── README.md
├── src
├── tests
└── TODO.md
```

## END