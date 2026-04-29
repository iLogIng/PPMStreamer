#pragma once

#include <cmath>
#include <array>
#include <stdexcept>
#include <initializer_list>

#include "Mat.hpp"

namespace pnmstream
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
    constexpr Vector() noexcept
        : data_{} {}

    constexpr explicit Vector(data_type value) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] = value;
        }
    }

    template<typename... Args, typename  = std::enable_if_t<sizeof...(Args) == N>>
    constexpr Vector(Args&&... args) noexcept
        : data_{static_cast<data_type>(std::forward<Args>(args))...} {}

    template<typename OtherType, size_t OtherN>
    constexpr Vector(const Vector<OtherType, OtherN>& other, data_type fillvalue = data_type{}) noexcept
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
    constexpr Vector(const Vector& other) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] = other[i];
        }
    }

    constexpr Vector& operator =(const Vector& other) noexcept
    {
        if(&other != this)
        {
            for(size_t i = 0; i < N; ++i)
            {
                data_[i] = other[i];
            }
        }
        return *this;
    }

    // move constructor
    constexpr Vector(Vector&& other) noexcept
        : data_(std::move(other.data_)) {}

    constexpr Vector& operator =(Vector&& other) noexcept
    {
        if(&other != this)
        {
            data_ = std::move(other.data_);
        }
        return *this;
    }

    ~Vector() = default;

public:

    constexpr data_type& operator [](size_t idx) noexcept
    {
        return data_[idx];
    }

    constexpr const data_type& operator [](size_t idx) const noexcept
    {
        return data_[idx];
    }

public:
    // x
    template<size_t M = N>
    constexpr std::enable_if_t<M >= 1, data_type&> x() noexcept
    {
        return data_[0];
    }
    template<size_t M = N>
    constexpr std::enable_if_t<M >= 1, const data_type&> x() const noexcept
    {
        return data_[0];
    }

    // y
    template<size_t M = N>
    constexpr std::enable_if_t<M >= 2, data_type&> y() noexcept
    {
        return data_[1];
    }
    template<size_t M = N>
    constexpr std::enable_if_t<M >= 2, const data_type&> y() const noexcept
    {
        return data_[1];
    }

    // z
    template<size_t M = N>
    constexpr std::enable_if_t<M >= 3, data_type&> z() noexcept
    {
        return data_[2];
    }
    template<size_t M = N>
    constexpr std::enable_if_t<M >= 3, const data_type&> z() const noexcept
    {
        return data_[2];
    }

    // w
    template<size_t M = N>
    constexpr std::enable_if_t<M >= 4, data_type&> w() noexcept
    {
        return data_[3];
    }
    template<size_t M = N>
    constexpr std::enable_if_t<M >= 4, const data_type&> w() const noexcept
    {
        return data_[3];
    }

    template<size_t M = N>
    constexpr std::enable_if_t<M >= 2, Vector<data_type, 2>> yx() const noexcept
    {
        return vec2(this->y(), this->x());
    }

    template<size_t M = N>
    constexpr std::enable_if_t<M >= 2, Vector<data_type, 4>> xyyx() const noexcept
    {
        return vec4(this->x(), this->y(), this->y(), this->x());
    }

public:

    // +
    constexpr Vector operator +(const Vector& other) const noexcept
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] + other[i];
        }
        return result;
    }
    constexpr Vector operator +(const data_type& value) const noexcept
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] + value;
        }
        return result;
    }
    // -
    constexpr Vector operator -(const Vector& other) const noexcept
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] - other[i];
        }
        return result;
    }
    constexpr Vector operator -(const data_type& value) const noexcept
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] - value;
        }
        return result;
    }
    // *
    constexpr Vector operator *(const Vector& other) const noexcept
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] * other[i];
        }
        return result;
    }
    constexpr Vector operator *(const data_type& value) const noexcept
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] * value;
        }
        return result;
    }
    // /
    constexpr Vector operator /(const data_type& value) const noexcept
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] / value;
        }
        return result;
    }
    constexpr Vector operator /(const Vector& other) const noexcept
    {
        Vector result;
        for(size_t i = 0; i < N; ++i)
        {
            result[i] = data_[i] / other[i];
        }
        return result;
    }

    constexpr bool operator ==(const Vector& other) const noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            if(data_[i] != other[i]) return false;
        }
        return true;
    }

    constexpr bool operator !=(const Vector& other) const noexcept
    {
        return !(*this == other);
    }

    template<typename Ty, size_t M>
    friend constexpr Vector<Ty, M> operator +(const Ty value, const Vector<Ty, M>& vec) noexcept;
    template<typename Ty, size_t M>
    friend constexpr Vector<Ty, M> operator -(const Ty value, const Vector<Ty, M>& vec) noexcept;
    template<typename Ty, size_t M>
    friend constexpr Vector<Ty, M> operator *(const Ty value, const Vector<Ty, M>& vec) noexcept;
    template<typename Ty, size_t M>
    friend constexpr Vector<Ty, M> operator /(const Ty value, const Vector<Ty, M>& vec) noexcept;


    // +=
    constexpr Vector& operator +=(const Vector& other) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] += other[i];
        }
        return *this;
    }
    constexpr Vector& operator +=(const data_type& value) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] += value;
        }
        return *this;
    }
    // -=
    constexpr Vector& operator -=(const Vector& other) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] -= other[i];
        }
        return *this;
    }
    constexpr Vector& operator -=(const data_type& value) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] -= value;
        }
        return *this;
    }
    // *=
    constexpr Vector& operator *=(const Vector& other) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] *= other[i];
        }
        return *this;
    }
    constexpr Vector& operator *=(const data_type& value) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] *= value;
        }
        return *this;
    }
    // /=
    constexpr Vector& operator /=(const Vector& other) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] /= other[i];
        }
        return *this;
    }
    constexpr Vector& operator /=(const data_type& value) noexcept
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[i] /= value;
        }
        return *this;
    }

    template<typename Ty, size_t M>
    friend constexpr Vector<Ty, M>& operator +=(const Ty value, Vector<Ty, M>& vec) noexcept;
    template<typename Ty, size_t M>
    friend constexpr Vector<Ty, M>& operator -=(const Ty value, Vector<Ty, M>& vec) noexcept;
    template<typename Ty, size_t M>
    friend constexpr Vector<Ty, M>& operator *=(const Ty value, Vector<Ty, M>& vec) noexcept;
    template<typename Ty, size_t M>
    friend constexpr Vector<Ty, M>& operator /=(const Ty value, Vector<Ty, M>& vec) noexcept;

public:

    // vector length
    auto length() const noexcept -> decltype(std::sqrt(static_cast<data_type>(data_type{})))
    {
        data_type sum = {};
        for(size_t i = 0; i < N; ++i)
        {
            sum += data_[i] * data_[i];
        }
        return std::sqrt(sum);
    }

    // normalize
    Vector<data_type, N> normalize() const noexcept
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
constexpr Vector<Ty, M> operator +(const Ty value, const Vector<Ty, M>& vec) noexcept
{
    Vector<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        result[i] = value + vec[i];
    }
    return result;
}
template<typename Ty, size_t M>
constexpr Vector<Ty, M> operator -(const Ty value, const Vector<Ty, M>& vec) noexcept
{
    Vector<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        result[i] = value - vec[i];
    }
    return result;
}
template<typename Ty, size_t M>
constexpr Vector<Ty, M> operator *(const Ty value, const Vector<Ty, M>& vec) noexcept
{
    Vector<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        result[i] = value * vec[i];
    }
    return result;
}
template<typename Ty, size_t M>
constexpr Vector<Ty, M> operator /(const Ty value, const Vector<Ty, M>& vec) noexcept
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
constexpr Vector<Ty, M>& operator +=(const Ty value, Vector<Ty, M>& vec) noexcept
{
    for(size_t i = 0; i < M; ++i)
    {
        vec[i] = value + vec[i];
    }
    return vec;
}
template<typename Ty, size_t M>
constexpr Vector<Ty, M>& operator -=(const Ty value, Vector<Ty, M>& vec) noexcept
{
    for(size_t i = 0; i < M; ++i)
    {
        vec[i] = value - vec[i];
    }
    return vec;
}
template<typename Ty, size_t M>
constexpr Vector<Ty, M>& operator *=(const Ty value, Vector<Ty, M>& vec) noexcept
{
    for(size_t i = 0; i < M; ++i)
    {
        vec[i] = value * vec[i];
    }
    return vec;
}
template<typename Ty, size_t M>
constexpr Vector<Ty, M>& operator /=(const Ty value, Vector<Ty, M>& vec) noexcept
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
constexpr data_type
dot(const Vector<data_type, N>& a, const Vector<data_type, N>& b) noexcept
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
constexpr pnmstream::Matrix<data_type, N>
outer(const Vector<data_type, N>& a, const Vector<data_type, N>& b) noexcept
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
constexpr data_type cross(const Vector<data_type, 2>& a, const Vector<data_type, 2>& b) noexcept
{
    return a.x() * b.y() - a.y() * b.x();
}

// 3D cross
template<typename data_type>
constexpr Vector<data_type, 3> cross(const Vector<data_type, 3>& a, const Vector<data_type, 3>& b) noexcept
{
    return Vector<data_type, 3>(
        a.y() * b.z() - a.z() * b.y(),
        a.z() * b.x() - a.x() * b.z(),
        a.x() * b.y() - a.y() * b.x()
    );
}

// static assert prohibit other dimension vector cross
template<typename data_type, size_t N>
Vector<data_type, N> cross(const Vector<data_type, N>& a, const Vector<data_type, N>& b) noexcept
{
    static_assert(N == 2 || N == 3,
        "Cross product is only defined for 2D and 3D vectors");
    return Vector<data_type, N>();
}

// length squared
template<typename data_type, size_t N>
constexpr data_type
length_squared(const Vector<data_type,N>& vec) noexcept
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
length(const Vector<data_type, N>& vec) noexcept -> decltype(std::sqrt(data_type{}))
{
    return std::sqrt(length_squared(vec));
}

// normalize
template<typename data_type, size_t N>
Vector<data_type, N>
normalize(const Vector<data_type, N>& vec) noexcept
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
abs(const Vector<data_type, N>& vec) noexcept
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
sin(const Vector<data_type, N>& vec) noexcept
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
cos(const Vector<data_type, N>& vec) noexcept
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
tanh(const Vector<data_type, N>& vec) noexcept
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
exp(const Vector<data_type, N>& vec) noexcept
{
    Vector<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        result[i] = std::exp(vec[i]);
    }
    return result;
}


}   // namespace pnmstream
