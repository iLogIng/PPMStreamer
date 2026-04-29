# math (向量与矩阵数学库)

> ***include/pnmstream/math/Vec.hpp***
> ***include/pnmstream/math/Mat.hpp***
>
> 泛型向量（vec2/vec3/vec4）与矩阵（mat2/mat3/mat4）数学库，基于 `float` 类型，纯头文件实现。
>
> 依赖:
> ***\<cmath>***
> ***\<utility>***
> ***\<memory>***
> ***\<array>***
> ***\<stdexcept>***
> ***\<initializer_list>***
>

## 结构

所有定义位于 ***namespace pnmstream*** 命名空间中。

---

## Vector

> ***include/pnmstream/math/Vector.hpp***

```cpp
template<typename T, size_t N>
struct Vector;
```

### 类型别名

| 类型 | 定义 |
|------|------|
| `vec2` | `Vector<float, 2>` |
| `vec3` | `Vector<float, 3>` |
| `vec4` | `Vector<float, 4>` |

### 成员函数

| 函数 | 返回值 | 说明 |
|------|--------|------|
| `Vector()` | — | 默认构造函数，所有分量初始化为 0 |
| `Vector(T val)` | — | 标量构造函数，所有分量设为 val |
| `Vector(T x, T y)` | — | 二维构造（仅 vec2） |
| `Vector(T x, T y, T z)` | — | 三维构造（仅 vec3） |
| `Vector(T x, T y, T z, T w)` | — | 四维构造（仅 vec4） |
| `x()` | `T` | 第 1 分量 |
| `y()` | `T` | 第 2 分量 |
| `z()` | `T` | 第 3 分量 |
| `w()` | `T` | 第 4 分量 |
| `length()` | `float` | 向量模长 |
| `operator [](size_t i)` | `T&` | 下标访问 |

### 运算符

| 运算符 | 说明 |
|--------|------|
| `+` / `-` | 逐分量加减 |
| `*` / `/` | 逐分量乘除 |
| `* T` / `/ T` | 标量乘除 |
| `T + v` / `T * v` | 标量左运算（反向运算符） |
| `+=` / `-=` / `*=` / `/=` | 复合赋值 |
| `==` / `!=` | 逐分量相等比较 |

### 自由函数

| 函数 | 返回值 | 说明 |
|------|--------|------|
| `dot(v1, v2)` | `T` | 点积 |
| `cross(v1, v2)` | `T` / `vec3` | 二维返回标量，三维返回 vec3 |
| `normalize(v)` | `Vector` | 归一化（单位向量） |

---

## Matrix

> ***include/pnmstream/math/Matrix.hpp***

```cpp
template<typename T, size_t Cols, size_t Rows>
struct Matrix;
```

### 类型别名

| 类型 | 定义 |
|------|------|
| `mat2` | `Matrix<float, 2, 2>` |
| `mat3` | `Matrix<float, 3, 3>` |
| `mat4` | `Matrix<float, 4, 4>` |

### 静态方法

| 方法 | 返回值 | 说明 |
|------|--------|------|
| `identity()` | `Matrix` | 单位矩阵 |

### 成员函数

| 函数 | 说明 |
|------|------|
| `operator ()(col, row)` | 按列、行访问元素 |
| `at(col, row)` | 带边界检查的访问 |
| `transpose()` | 转置矩阵 |

### 运算符

| 运算符 | 说明 |
|--------|------|
| `+` / `-` | 矩阵加减 |
| `*` | 矩阵乘法 |
| `* T` / `/ T` | 标量乘除 |
| `==` / `!=` | 逐元素相等比较 |

### constexpr 约束

- **Vector**: 所有操作均为 `constexpr` + `noexcept`，可在编译期计算。
- **Matrix**: `operator()` 因边界检查含 `throw`，不能标记 `constexpr`；其余操作 `noexcept`。
