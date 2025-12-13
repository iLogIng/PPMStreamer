#pragma once

#include <cmath>
#include <utility>
#include <memory>
#include <array>
#include <stdexcept>
#include <initializer_list>

namespace ppm
{

/**
 * + - * / dot cross(vec)
 * common & matrix
 * vector & matrix
 * matrix & matrix
 */

template <typename Type, size_t N>
class Matrix
{
    using data_type = Type;
private:
    // matrix
    std::array<data_type, N * N> data_;

public:
    // constructor
    Matrix()
        : data_{} {}

    explicit Matrix(const data_type& value)
    {
        data_.fill(value);
    }

    Matrix(std::initializer_list<float> init_list)
    {
        if(init_list.size() > N * N)
        {
            throw std::runtime_error("initializer list out of range of N * N");
        }

        std::copy(init_list.begin(), init_list.end(), this->data_.begin());
        std::fill(data_.begin() + init_list.size(), data_.end(), 0.0f);
    }

    // copy constructor
    Matrix(const Matrix& other)
    {
        std::copy(other.data_.begin(), other.data_.end(), this->data_.begin());
    }

    Matrix& operator =(const Matrix& other)
    {
        if(&other != this)
        {
            std::copy(data_.begin(), data_.end(), other.data_.begin());
        }
        return *this;
    }

    // move constructor
    Matrix(Matrix&& other)
        : data_(std::move(other.data_)) {}

    Matrix& operator =(Matrix&& other)
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
    float& operator ()(size_t row, size_t col)
    {
        if(row >= N || col >= N)
        {
            throw std::runtime_error("out of range");
        }
        return data_[row * N + col];
    }

    const float& operator ()(size_t row, size_t col) const
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
    operator +(const Matrix& other) const;
    // operator +
    Matrix<data_type, N>
    operator +(const data_type& a) const;
    // operator -
    Matrix<data_type, N>
    operator -(const Matrix& other) const;
    // operator -
    Matrix<data_type, N>
    operator -(const data_type& a) const;
    // operator *
    Matrix<data_type, N>
    operator *(const Matrix& other) const;
    // operator *
    Matrix<data_type, N>
    operator *(const data_type& a) const;
    // operator /
    Matrix<data_type, N>
    operator /(const Matrix& other) const;
    // operator /
    Matrix<data_type, N>
    operator /(const data_type& a) const;

    template<typename Ty, size_t M>
    friend Matrix<Ty, M> operator +(const Ty& a, const Matrix<Ty, M>& mat);
    template<typename Ty, size_t M>
    friend Matrix<Ty, M> operator -(const Ty& a, const Matrix<Ty, M>& mat);
    template<typename Ty, size_t M>
    friend Matrix<Ty, M> operator *(const Ty& a, const Matrix<Ty, M>& mat);
    template<typename Ty, size_t M>
    friend Matrix<Ty, M> operator /(const Ty& a, const Matrix<Ty, M>& mat);
    
    // operator +=
    Matrix<data_type, N>&
    operator +=(const Matrix& other);
    // operator +=
    Matrix<data_type, N>&
    operator +=(const data_type& a);
    // operator -=
    Matrix<data_type, N>&
    operator -=(const Matrix& other);
    // operator -=
    Matrix<data_type, N>&
    operator -=(const data_type& a);
    // operator *=
    Matrix<data_type, N>&
    operator *=(const Matrix& other);
    // operator *=
    Matrix<data_type, N>&
    operator *=(const data_type& a);
    // operator /=
    Matrix<data_type, N>&
    operator /=(const Matrix& other);
    // operator /=
    Matrix<data_type, N>&
    operator /=(const data_type& a);

    template<typename Ty, size_t M>
    friend Matrix<Ty, M>& operator +=(const Ty& a, Matrix<Ty, M>& mat);
    template<typename Ty, size_t M>
    friend Matrix<Ty, M>& operator -=(const Ty& a, Matrix<Ty, M>& mat);
    template<typename Ty, size_t M>
    friend Matrix<Ty, M>& operator *=(const Ty& a, Matrix<Ty, M>& mat);
    template<typename Ty, size_t M>
    friend Matrix<Ty, M>& operator /=(const Ty& a, Matrix<Ty, M>& mat);

public:

    // identity
    static Matrix identity()
    {
        Matrix mat(data_type{0});
        for(size_t i = 0; i < N; ++i)
        {
            mat(i, i) = data_type{1};
        }
        return mat;
    }

    // transpos
    Matrix transpos()
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
Matrix<data_type, N>::operator +(const Matrix<data_type, N>& other) const 
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
Matrix<data_type, N>::operator +(const data_type& a) const 
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
Matrix<data_type, N>::operator -(const Matrix<data_type, N>& other) const 
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
Matrix<data_type, N>::operator -(const data_type& a) const 
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
Matrix<data_type, N>::operator *(const Matrix<data_type, N>& other) const 
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
template<typename data_type, size_t N>Matrix<data_type, N>
Matrix<data_type, N>::operator *(const data_type& a) const 
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

template<typename data_type, size_t N>
Matrix<data_type, N>
Matrix<data_type, N>::operator /(const Matrix<data_type, N>& other) const 
{
    Matrix<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            result(i, j) = (*this)(i, j) / other(i, j);
        }
    }
    return result;
}
template<typename data_type, size_t N>
Matrix<data_type, N>
Matrix<data_type, N>::operator /(const data_type& a) const 
{
    Matrix<data_type, N> result;
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            result(i, j) = (*this)(i, j) / a;
        }
    }
    return result;
}

// friend
template<typename Ty, size_t M>
Matrix<Ty, M> operator +(const Ty& a, const Matrix<Ty, M>& mat)
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
Matrix<Ty, M> operator -(const Ty& a, const Matrix<Ty, M>& mat)
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
Matrix<Ty, M> operator *(const Ty& a, const Matrix<Ty, M>& mat)
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
template<typename Ty, size_t M>
Matrix<Ty, M> operator /(const Ty& a, const Matrix<Ty, M>& mat)
{
    Matrix<Ty, M> result;
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < M; ++j)
        {
            result(i, j) = a / mat(i, j);
        }
    }
    return result;
}

template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator +=(const Matrix<data_type, N>& other)
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
Matrix<data_type, N>::operator +=(const data_type& a)
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
Matrix<data_type, N>::operator -=(const Matrix<data_type, N>& other)
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
Matrix<data_type, N>::operator -=(const data_type& a)
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
Matrix<data_type, N>::operator *=(const Matrix<data_type, N>& other)
{
    Matrix<data_type, N> tempmat;
    tempmat = (*this) * other;
    (*this) = std::move(tempmat);
    return *this;
}
template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator *=(const data_type& a)
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

template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator /=(const Matrix<data_type, N>& other)
{
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            (*this)(i, j) /= other(i, j);
        }
    }
    return *this;
}
template<typename data_type, size_t N>
Matrix<data_type, N>&
Matrix<data_type, N>::operator /=(const data_type& a)
{
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            (*this)(i, j) /= a;
        }
    }
    return *this;
}

// friend
template<typename Ty, size_t M>
Matrix<Ty, M>& operator +=(const Ty& a, Matrix<Ty, M>& mat)
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
Matrix<Ty, M>& operator -=(const Ty& a, Matrix<Ty, M>& mat)
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
Matrix<Ty, M>& operator *=(const Ty& a, Matrix<Ty, M>& mat)
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
template<typename Ty, size_t M>
Matrix<Ty, M>& operator /=(const Ty& a, Matrix<Ty, M>& mat)
{
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < M; ++j)
        {
            mat(i, j) = a / mat(i, j);
        }
    }
    return mat;
}

// ===================================================

using mat2f = Matrix<float, 2>;
using mat2 = mat2f;

using mat3f = Matrix<float, 3>;
using mat3 = mat3f;

using mat4f = Matrix<float, 4>;
using mat4 = mat4f;

}   // namespace ppm
