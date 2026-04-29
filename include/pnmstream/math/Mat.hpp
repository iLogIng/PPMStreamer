#pragma once

#include <cmath>
#include <utility>
#include <memory>
#include <array>
#include <stdexcept>
#include <initializer_list>

namespace pnmstream
{

template <typename Type, size_t N>
class Matrix
{
    using data_type = Type;
private:
    // matrix
    std::array<data_type, N * N> data_;

public:
    // constructor
    constexpr Matrix() noexcept
        : data_{} {}

    constexpr explicit Matrix(const data_type& value) noexcept
    {
        for(size_t i = 0; i < N * N; ++i)
        {
            data_[i] = value;
        }
    }

    Matrix(std::initializer_list<data_type> init_list)
    {
        if(init_list.size() > N * N)
        {
            throw std::runtime_error("initializer list out of range of N * N");
        }

        auto it = init_list.begin();
        for(size_t i = 0; i < init_list.size(); ++i, ++it)
        {
            data_[i] = *it;
        }
        for(size_t i = init_list.size(); i < N * N; ++i)
        {
            data_[i] = data_type{0};
        }
    }

    // copy constructor
    constexpr Matrix(const Matrix& other) noexcept
    {
        for(size_t i = 0; i < N * N; ++i)
        {
            data_[i] = other.data_[i];
        }
    }

    constexpr Matrix& operator =(const Matrix& other) noexcept
    {
        if(&other != this)
        {
            for(size_t i = 0; i < N * N; ++i)
            {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    // move constructor
    constexpr Matrix(Matrix&& other) noexcept
        : data_(std::move(other.data_)) {}

    constexpr Matrix& operator =(Matrix&& other) noexcept
    {
        if(&other != this)
        {
            data_ = std::move(other.data_);
        }
        return *this;
    }

    ~Matrix() = default;

public:
    // matrix
    data_type& operator ()(size_t row, size_t col)
    {
        if(row >= N || col >= N)
        {
            throw std::runtime_error("out of range");
        }
        return data_[row * N + col];
    }

    const data_type& operator ()(size_t row, size_t col) const
    {
        if(row >= N || col >= N)
        {
            throw std::runtime_error("out of range");
        }
        return data_[row * N + col];
    }

public:
    // operator op()

    // operator +
    Matrix<data_type, N>
    operator +(const Matrix& other) const noexcept;
    // operator +
    Matrix<data_type, N>
    operator +(const data_type& a) const noexcept;
    // operator -
    Matrix<data_type, N>
    operator -(const Matrix& other) const noexcept;
    // operator -
    Matrix<data_type, N>
    operator -(const data_type& a) const noexcept;
    // operator *
    Matrix<data_type, N>
    operator *(const Matrix& other) const noexcept;
    // operator *
    Matrix<data_type, N>
    operator *(const data_type& a) const noexcept;

    constexpr bool operator ==(const Matrix& other) const noexcept
    {
        for(size_t i = 0; i < N * N; ++i)
        {
            if(data_[i] != other.data_[i]) return false;
        }
        return true;
    }

    constexpr bool operator !=(const Matrix& other) const noexcept
    {
        return !(*this == other);
    }

    template<typename Ty, size_t M>
    friend Matrix<Ty, M> operator +(const Ty& a, const Matrix<Ty, M>& mat) noexcept;
    template<typename Ty, size_t M>
    friend Matrix<Ty, M> operator -(const Ty& a, const Matrix<Ty, M>& mat) noexcept;
    template<typename Ty, size_t M>
    friend Matrix<Ty, M> operator *(const Ty& a, const Matrix<Ty, M>& mat) noexcept;

    // operator +=
    Matrix<data_type, N>&
    operator +=(const Matrix& other) noexcept;
    // operator +=
    Matrix<data_type, N>&
    operator +=(const data_type& a) noexcept;
    // operator -=
    Matrix<data_type, N>&
    operator -=(const Matrix& other) noexcept;
    // operator -=
    Matrix<data_type, N>&
    operator -=(const data_type& a) noexcept;
    // operator *=
    Matrix<data_type, N>&
    operator *=(const Matrix& other) noexcept;
    // operator *=
    Matrix<data_type, N>&
    operator *=(const data_type& a) noexcept;

    template<typename Ty, size_t M>
    friend Matrix<Ty, M>& operator +=(const Ty& a, Matrix<Ty, M>& mat) noexcept;
    template<typename Ty, size_t M>
    friend Matrix<Ty, M>& operator -=(const Ty& a, Matrix<Ty, M>& mat) noexcept;
    template<typename Ty, size_t M>
    friend Matrix<Ty, M>& operator *=(const Ty& a, Matrix<Ty, M>& mat) noexcept;

public:

    // identity
    static Matrix identity() noexcept
    {
        Matrix mat(data_type{0});
        for(size_t i = 0; i < N; ++i)
        {
            mat(i, i) = data_type{1};
        }
        return mat;
    }

    // transpose
    Matrix transpose() const noexcept
    {
        Matrix mat;
        for(size_t i = 0; i < N; ++i)
        {
            for(size_t j = 0; j < N; ++j)
            {
                mat(j, i) = (*this)(i, j);
            }
        }
        return mat;
    }

};  // class Matrix

// ===========================================================================

template<typename data_type, size_t N>
Matrix<data_type, N>
Matrix<data_type, N>::operator +(const Matrix<data_type, N>& other) const noexcept
{
    Matrix<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}
template<typename data_type, size_t N>
Matrix<data_type, N>
Matrix<data_type, N>::operator +(const data_type& a) const noexcept
{
    Matrix<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            result(i, j) = (*this)(i, j) + a;
        }
    }
    return result;
}

template<typename data_type, size_t N>
Matrix<data_type, N>
Matrix<data_type, N>::operator -(const Matrix<data_type, N>& other) const noexcept
{
    Matrix<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}
template<typename data_type, size_t N>
Matrix<data_type, N>
Matrix<data_type, N>::operator -(const data_type& a) const noexcept
{
    Matrix<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            result(i, j) = (*this)(i, j) - a;
        }
    }
    return result;
}

template<typename data_type, size_t N>
Matrix<data_type, N>
Matrix<data_type, N>::operator *(const Matrix<data_type, N>& other) const noexcept
{
    Matrix<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            for(size_t k = 0; k < N; ++k)
            {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}
template<typename data_type, size_t N>
Matrix<data_type, N>
Matrix<data_type, N>::operator *(const data_type& a) const noexcept
{
    Matrix<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            result(i, j) = (*this)(i, j) * a;
        }
    }
    return result;
}

// friend
template<typename Ty, size_t M>
Matrix<Ty, M> operator +(const Ty& a, const Matrix<Ty, M>& mat) noexcept
{
    Matrix<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < M; ++j)
        {
            result(i, j) = a + mat(i, j);
        }
    }
    return result;
}
template<typename Ty, size_t M>
Matrix<Ty, M> operator -(const Ty& a, const Matrix<Ty, M>& mat) noexcept
{
    Matrix<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < M; ++j)
        {
            result(i, j) = a - mat(i, j);
        }
    }
    return result;
}
template<typename Ty, size_t M>
Matrix<Ty, M> operator *(const Ty& a, const Matrix<Ty, M>& mat) noexcept
{
    Matrix<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < M; ++j)
        {
            result(i, j) = a * mat(i, j);
        }
    }
    return result;
}

template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator +=(const Matrix<data_type, N>& other) noexcept
{
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            (*this)(i, j) += other(i, j);
        }
    }
    return *this;
}
template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator +=(const data_type& a) noexcept
{
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            (*this)(i, j) += a;
        }
    }
    return *this;
}

template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator -=(const Matrix<data_type, N>& other) noexcept
{
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            (*this)(i, j) -= other(i, j);
        }
    }
    return *this;
}
template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator -=(const data_type& a) noexcept
{
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            (*this)(i, j) -= a;
        }
    }
    return *this;
}

template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator *=(const Matrix<data_type, N>& other) noexcept
{
    Matrix<data_type, N> tempmat;
    tempmat = (*this) * other;
    (*this) = std::move(tempmat);
    return *this;
}
template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator *=(const data_type& a) noexcept
{
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            (*this)(i, j) *= a;
        }
    }
    return *this;
}

// friend
template<typename Ty, size_t M>
Matrix<Ty, M>& operator +=(const Ty& a, Matrix<Ty, M>& mat) noexcept
{
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < M; ++j)
        {
            mat(i, j) = a + mat(i, j);
        }
    }
    return mat;
}
template<typename Ty, size_t M>
Matrix<Ty, M>& operator -=(const Ty& a, Matrix<Ty, M>& mat) noexcept
{
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < M; ++j)
        {
            mat(i, j) = a - mat(i, j);
        }
    }
    return mat;
}
template<typename Ty, size_t M>
Matrix<Ty, M>& operator *=(const Ty& a, Matrix<Ty, M>& mat) noexcept
{
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < M; ++j)
        {
            mat(i, j) = a * mat(i, j);
        }
    }
    return mat;
}

using mat2f = Matrix<float, 2>;
using mat2 = mat2f;

using mat3f = Matrix<float, 3>;
using mat3 = mat3f;

using mat4f = Matrix<float, 4>;
using mat4 = mat4f;

}   // namespace pnmstream
