#pragma once

#include <cmath>
#include <array>
#include <stdexcept>
#include <initializer_list>

#include "Mat.hpp"

namespace ppmstream
{

template<typename Type, size_t n>
class Vector;

using vec2f = Vector<float, 2>;
using vec2 = vec2f;

using vec3f = Vector<float, 3>;
using vec3 = vec3f;

using vec4f = Vector<float, 4>;
using vec4 = vec4f;

template<typename Type, size_t N>
class Vector
{
    using data_type = Type;

private:
    // vector data
    std::array<data_type, N> data_;

public:
    // constructor
    Vector()
        : data_{} {}

    explicit Vector(data_type value)
    {
        data_.fill(value);
    }

    template<typename... Args, typename  = std::enable_if_t<sizeof...(Args) == N>>
    Vector(Args&&... args)
        : data_{static_cast<data_type>(std::forward<Args>(args))...} {}

    template<typename OtherType, size_t OtherN>
    Vector(const Vector<OtherType, OtherN>& other, data_type fillvalue = data_type{})
    {
        constexpr size_t min_size = (N < OtherN) ? N : OtherN;

        size_t i = 0;
        for(i = 0; i < min_size; ++i)
        {
            data_[i] = static_cast<data_type>(other[i]);
        }
        for(; i < N; ++i)
        {
            data_[i] = fillvalue;
        }
    }

    // copy constructor
    Vector(const Vector& other)
    {
        std::copy(other.data_.begin(), other.data_.end(), data_.begin());
    }

    Vector& operator =(const Vector& other)
    {
        if(&other != this)
        {
            std::copy(other.data_.begin(), other.data_.end(), data_.begin());
        }
        return *this;
    }

    // move constructor
    Vector(Vector&& other)
        : data_(std::move(other.data_)) {}

    Vector& operator =(Vector&& other)
    {
        if(&other != this)
        {
            data_ = std::move(other.data_);
        }
        return *this;
    }

    ~Vector() = default;

public:

    data_type& operator [](size_t idx)
    {
        return data_[idx];
    }

    const data_type& operator [](size_t idx) const
    {
        return data_[idx];
    }

public:
    // x
    template<size_t M = N>
    std::enable_if_t<M >= 1, data_type&> x()
    {
        return data_[0];
    }
    template<size_t M = N>
    std::enable_if_t<M >= 1, const data_type&> x() const
    {
        return data_[0];
    }

    // y
    template<size_t M = N>
    std::enable_if_t<M >= 2, data_type&> y()
    {
        return data_[1];
    }
    template<size_t M = N>
    std::enable_if_t<M >= 2, const data_type&> y() const
    {
        return data_[1];
    }

    // z
    template<size_t M = N>
    std::enable_if_t<M >= 3, data_type&> z()
    {
        return data_[2];
    }
    template<size_t M = N>
    std::enable_if_t<M >= 3, const data_type&> z() const
    {
        return data_[2];
    }

    // w
    template<size_t M = N>
    std::enable_if_t<M >= 4, data_type&> w()
    {
        return data_[3];
    }
    template<size_t M = N>
    std::enable_if_t<M >= 4, const data_type&> w() const
    {
        return data_[3];
    }

    template<size_t M = N>
    std::enable_if_t<M >= 2, Vector<data_type, 2>> yx() const
    {
        return vec2(this->y(), this->x());
    }

    template<size_t M = N>
    std::enable_if_t<M >= 2, Vector<data_type, 4>> xyyx() const
    {
        return vec4(this->x(), this->y(), this->y(), this->x());
    }

public:

    // +
    Vector operator +(const Vector& other) const
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] + other[i];
        }
        return result;
    }
    Vector operator +(const data_type& value) const
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] + value;
        }
        return result;
    }
    // -
    Vector operator -(const Vector& other) const
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] - other[i];
        }
        return result;
    }
    Vector operator -(const data_type& value) const
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] - value;
        }
        return result;
    }
    // *
    Vector operator *(const Vector& other) const
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] * other[i];
        }
        return result;
    }
    Vector operator *(const data_type& value) const
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] * value;
        }
        return result;
    }
    // /
    Vector operator /(const data_type& value) const
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] / value;
        }
        return result;
    }
    Vector operator /(const Vector& other) const
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] / other[i];
        }
        return result;
    }

    template<typename Ty, size_t M>
    friend Vector<Ty, M> operator +(const Ty value, const Vector<Ty, M>& vec);
    template<typename Ty, size_t M>
    friend Vector<Ty, M> operator -(const Ty value, const Vector<Ty, M>& vec);
    template<typename Ty, size_t M>
    friend Vector<Ty, M> operator *(const Ty value, const Vector<Ty, M>& vec);
    template<typename Ty, size_t M>
    friend Vector<Ty, M> operator /(const Ty value, const Vector<Ty, M>& vec);


    // +=
    Vector& operator +=(const Vector& other)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] += other[i];
        }
        return *this;
    }
    Vector& operator +=(const data_type& value)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] += value;
        }
        return *this;
    }
    // -=
    Vector& operator -=(const Vector& other)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] -= other[i];
        }
        return *this;
    }
    Vector& operator -=(const data_type& value)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] -= value;
        }
        return *this;
    }
    // *=
    Vector& operator *=(const Vector& other)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] *= other[i];
        }
        return *this;
    }
    Vector& operator *=(const data_type& value)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] *= value;
        }
        return *this;
    }
    // /=
    Vector& operator /=(const Vector& other)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] /= other[i];
        }
        return *this;
    }
    Vector& operator /=(const data_type& value)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] /= value;
        }
        return *this;
    }

    template<typename Ty, size_t M>
    friend Vector<Ty, M>& operator +=(const Ty value, Vector<Ty, M>& vec);
    template<typename Ty, size_t M>
    friend Vector<Ty, M>& operator -=(const Ty value, Vector<Ty, M>& vec);
    template<typename Ty, size_t M>
    friend Vector<Ty, M>& operator *=(const Ty value, Vector<Ty, M>& vec);
    template<typename Ty, size_t M>
    friend Vector<Ty, M>& operator /=(const Ty value, Vector<Ty, M>& vec);

public:

    // vector length
    auto length() const -> decltype(std::sqrt(static_cast<data_type>(data_type{})))
    {
        data_type sum = {};
        for(size_t i = 0; i < N; ++i)
        {
            sum += data_[i] * data_[i];
        }
        return std::sqrt(sum);
    }

    // normalize
    Vector<data_type, N> normalize() const
    {
        Vector<data_type, N> result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] / length();
        }
        return result;
    }

};  // class Vector

// ============================================================================

// friend
template<typename Ty, size_t M>
Vector<Ty, M> operator +(const Ty value, const Vector<Ty, M>& vec)
{
    Vector<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        result[i] = value + vec[i];
    }
    return result;
}
template<typename Ty, size_t M>
Vector<Ty, M> operator -(const Ty value, const Vector<Ty, M>& vec)
{
    Vector<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        result[i] = value - vec[i];
    }
    return result;
}
template<typename Ty, size_t M>
Vector<Ty, M> operator *(const Ty value, const Vector<Ty, M>& vec)
{
    Vector<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        result[i] = value * vec[i];
    }
    return result;
}
template<typename Ty, size_t M>
Vector<Ty, M> operator /(const Ty value, const Vector<Ty, M>& vec)
{
    Vector<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        result[i] = value / vec[i];
    }
    return result;
}

// friend
template<typename Ty, size_t M>
Vector<Ty, M>& operator +=(const Ty value, Vector<Ty, M>& vec)
{
    for(size_t i = 0; i < M; ++i)
    {
        vec[i] = value + vec[i];
    }
    return vec;
}
template<typename Ty, size_t M>
Vector<Ty, M>& operator -=(const Ty value, Vector<Ty, M>& vec)
{
    for(size_t i = 0; i < M; ++i)
    {
        vec[i] = value - vec[i];
    }
    return vec;
}
template<typename Ty, size_t M>
Vector<Ty, M>& operator *=(const Ty value, Vector<Ty, M>& vec)
{
    for(size_t i = 0; i < M; ++i)
    {
        vec[i] = value * vec[i];
    }
    return vec;
}
template<typename Ty, size_t M>
Vector<Ty, M>& operator /=(const Ty value, Vector<Ty, M>& vec)
{
    for(size_t i = 0; i < M; ++i)
    {
        vec[i] = value / vec[i];
    }
    return vec;
}

// =====================================================================
// func option

// dot production
template<typename data_type, size_t N>
data_type
dot(const Vector<data_type, N>& a, const Vector<data_type, N>& b)
{
    data_type result = {};
    for(size_t i = 0; i < N; ++i)
    {
        result += a[i] * b[i];
    }
    return result;
}

// outer
template<typename data_type, size_t N>
ppmstream::Matrix<data_type, N>
outer(const Vector<data_type, N>& a, const Vector<data_type, N>& b)
{
    Matrix<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            result(i, j) = a[i] * b[j];
        }
    }
    return result;
}

// 2D cross
template<typename data_type>
data_type cross(const Vector<data_type, 2>& a, const Vector<data_type, 2>& b)
{
    return a.x() * b.y() - a.y() * b.x();
}

// 3D cross
template<typename data_type>
Vector<data_type, 3> cross(const Vector<data_type, 3>& a, const Vector<data_type, 3>& b)
{
    return Vector<data_type, 3>(
        a.y() * b.z() - a.z() * b.y(),
        a.z() * b.x() - a.x() * b.z(),
        a.x() * b.y() - a.y() * b.x()
    );
}

// static assert prohibit other dimension vector cross
template<typename data_type, size_t N>
Vector<data_type, N> cross(const Vector<data_type, N>& a, const Vector<data_type, N>& b)
{
    static_assert(N == 2 || N == 3,
        "Cross product is only defined for 2D and 3D vectors");
    return Vector<data_type, N>();
}

// length squared
template<typename data_type, size_t N>
data_type
length_squared(const Vector<data_type,N>& vec)
{
    data_type sum = {0};
    for(size_t i = 0; i < N; ++i)
    {
        sum += vec[i] * vec[i];
    }
    return sum;
}

// length
template<typename data_type, size_t N>
auto
length(const Vector<data_type, N>& vec) -> decltype(std::sqrt(data_type{}))
{
    return std::sqrt(length_squared(vec));
}

// normalize
template<typename data_type, size_t N>
Vector<data_type, N>
normalize(const Vector<data_type, N>& vec)
{
    auto veclength = length(vec);
    if(veclength > data_type{0})
    {
        return vec / veclength;
    }
    return vec;
}

// abs
template<typename data_type, size_t N>
Vector<data_type, N>
abs(const Vector<data_type, N>& vec)
{
    Vector<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        result[i] = std::abs(vec[i]);
    }
    return result;
}

// sin
template<typename data_type, size_t N>
Vector<data_type, N>
sin(const Vector<data_type, N>& vec)
{
    Vector<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        result[i] = std::sin(vec[i]);
    }
    return result;
}

// cos
template<typename data_type, size_t N>
Vector<data_type, N>
cos(const Vector<data_type, N>& vec)
{
    Vector<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        result[i] = std::cos(vec[i]);
    }
    return result;
}

// tanh
template<typename data_type, size_t N>
Vector<data_type, N>
tanh(const Vector<data_type, N>& vec)
{
    Vector<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        result[i] = std::tanh(vec[i]);
    }
    return result;
}

// exp
template<typename data_type, size_t N>
Vector<data_type, N>
exp(const Vector<data_type, N>& vec)
{
    Vector<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        result[i] = std::exp(vec[i]);
    }
    return result;
}


}   // namespace ppm
