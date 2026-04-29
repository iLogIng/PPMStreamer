#include <gtest/gtest.h>
#include "../include/pnmstream/math/Vec.hpp"
#include "../include/pnmstream/math/Mat.hpp"

// ============================================================
// Math: Vector
// ============================================================

TEST(VectorTest, DefaultConstructor)
{
    using namespace pnmstream;
    vec2 v;
    EXPECT_FLOAT_EQ(v.x(), 0.0f);
    EXPECT_FLOAT_EQ(v.y(), 0.0f);
}

TEST(VectorTest, ValueConstructor)
{
    using namespace pnmstream;
    vec2 v(3.0f);
    EXPECT_FLOAT_EQ(v.x(), 3.0f);
    EXPECT_FLOAT_EQ(v.y(), 3.0f);
}

TEST(VectorTest, ElementConstructor)
{
    using namespace pnmstream;
    vec2 v(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
}

TEST(VectorTest, CopyConstructor)
{
    using namespace pnmstream;
    vec2 v0(1.0f, 2.0f);
    vec2 v1(v0);
    EXPECT_EQ(v0, v1);
}

TEST(VectorTest, MoveConstructor)
{
    using namespace pnmstream;
    vec2 v0(1.0f, 2.0f);
    vec2 v1(std::move(v0));
    EXPECT_FLOAT_EQ(v1.x(), 1.0f);
    EXPECT_FLOAT_EQ(v1.y(), 2.0f);
}

TEST(VectorTest, Addition)
{
    using namespace pnmstream;
    vec2 a(1.0f, 2.0f);
    vec2 b(3.0f, 4.0f);
    auto r = a + b;
    EXPECT_FLOAT_EQ(r.x(), 4.0f);
    EXPECT_FLOAT_EQ(r.y(), 6.0f);
}

TEST(VectorTest, Subtraction)
{
    using namespace pnmstream;
    vec2 a(5.0f, 7.0f);
    vec2 b(1.0f, 3.0f);
    auto r = a - b;
    EXPECT_FLOAT_EQ(r.x(), 4.0f);
    EXPECT_FLOAT_EQ(r.y(), 4.0f);
}

TEST(VectorTest, Multiplication)
{
    using namespace pnmstream;
    vec2 a(2.0f, 3.0f);
    vec2 b(4.0f, 5.0f);
    auto r = a * b;
    EXPECT_FLOAT_EQ(r.x(), 8.0f);
    EXPECT_FLOAT_EQ(r.y(), 15.0f);
}

TEST(VectorTest, ScalarMultiplication)
{
    using namespace pnmstream;
    vec2 a(2.0f, 3.0f);
    auto r = a * 2.0f;
    EXPECT_FLOAT_EQ(r.x(), 4.0f);
    EXPECT_FLOAT_EQ(r.y(), 6.0f);
}

TEST(VectorTest, Division)
{
    using namespace pnmstream;
    vec2 a(8.0f, 9.0f);
    vec2 b(2.0f, 3.0f);
    auto r = a / b;
    EXPECT_FLOAT_EQ(r.x(), 4.0f);
    EXPECT_FLOAT_EQ(r.y(), 3.0f);
}

TEST(VectorTest, ScalarDivision)
{
    using namespace pnmstream;
    vec2 a(6.0f, 8.0f);
    auto r = a / 2.0f;
    EXPECT_FLOAT_EQ(r.x(), 3.0f);
    EXPECT_FLOAT_EQ(r.y(), 4.0f);
}

TEST(VectorTest, CompoundAssignment)
{
    using namespace pnmstream;
    vec2 a(1.0f, 2.0f);
    a += vec2(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(a.x(), 4.0f);
    EXPECT_FLOAT_EQ(a.y(), 6.0f);
    a *= 2.0f;
    EXPECT_FLOAT_EQ(a.x(), 8.0f);
    EXPECT_FLOAT_EQ(a.y(), 12.0f);
}

TEST(VectorTest, Equality)
{
    using namespace pnmstream;
    vec2 a(1.0f, 2.0f);
    vec2 b(1.0f, 2.0f);
    vec2 c(1.0f, 3.0f);
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST(VectorTest, Accessors)
{
    using namespace pnmstream;
    vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
    EXPECT_FLOAT_EQ(v.w(), 4.0f);
}

TEST(VectorTest, Length)
{
    using namespace pnmstream;
    vec3 v(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

TEST(VectorTest, DotProduct)
{
    using namespace pnmstream;
    vec3 a(1.0f, 2.0f, 3.0f);
    vec3 b(4.0f, 5.0f, 6.0f);
    EXPECT_FLOAT_EQ(dot(a, b), 32.0f);
}

TEST(VectorTest, CrossProduct2D)
{
    using namespace pnmstream;
    vec2 a(1.0f, 0.0f);
    vec2 b(0.0f, 1.0f);
    EXPECT_FLOAT_EQ(cross(a, b), 1.0f);
}

TEST(VectorTest, CrossProduct3D)
{
    using namespace pnmstream;
    vec3 a(1.0f, 0.0f, 0.0f);
    vec3 b(0.0f, 1.0f, 0.0f);
    auto r = cross(a, b);
    EXPECT_FLOAT_EQ(r.x(), 0.0f);
    EXPECT_FLOAT_EQ(r.y(), 0.0f);
    EXPECT_FLOAT_EQ(r.z(), 1.0f);
}

TEST(VectorTest, Normalize)
{
    using namespace pnmstream;
    vec3 v(3.0f, 4.0f, 0.0f);
    auto n = normalize(v);
    EXPECT_NEAR(n.length(), 1.0f, 1e-6f);
}

TEST(VectorTest, ScalarReversedOperators)
{
    using namespace pnmstream;
    vec2 v(2.0f, 3.0f);
    auto r = 1.0f + v;
    EXPECT_FLOAT_EQ(r.x(), 3.0f);
    EXPECT_FLOAT_EQ(r.y(), 4.0f);
    auto s = 6.0f - v;
    EXPECT_FLOAT_EQ(s.x(), 4.0f);
    EXPECT_FLOAT_EQ(s.y(), 3.0f);
    auto t = 2.0f * v;
    EXPECT_FLOAT_EQ(t.x(), 4.0f);
    EXPECT_FLOAT_EQ(t.y(), 6.0f);
}

// ============================================================
// Math: Matrix
// ============================================================

TEST(MatrixTest, DefaultConstructor)
{
    using namespace pnmstream;
    mat2 m;
    EXPECT_FLOAT_EQ(m(0, 0), 0.0f);
    EXPECT_FLOAT_EQ(m(1, 1), 0.0f);
}

TEST(MatrixTest, Identity)
{
    using namespace pnmstream;
    auto m = mat2::identity();
    EXPECT_FLOAT_EQ(m(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m(0, 1), 0.0f);
    EXPECT_FLOAT_EQ(m(1, 0), 0.0f);
    EXPECT_FLOAT_EQ(m(1, 1), 1.0f);
}

TEST(MatrixTest, Transpose)
{
    using namespace pnmstream;
    mat2 m{1.0f, 2.0f, 3.0f, 4.0f};
    auto t = m.transpose();
    EXPECT_FLOAT_EQ(t(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(t(0, 1), 3.0f);
    EXPECT_FLOAT_EQ(t(1, 0), 2.0f);
    EXPECT_FLOAT_EQ(t(1, 1), 4.0f);
}

TEST(MatrixTest, MatrixAddition)
{
    using namespace pnmstream;
    mat2 a{1.0f, 2.0f, 3.0f, 4.0f};
    mat2 b{5.0f, 6.0f, 7.0f, 8.0f};
    auto r = a + b;
    EXPECT_FLOAT_EQ(r(0, 0), 6.0f);
    EXPECT_FLOAT_EQ(r(1, 1), 12.0f);
}

TEST(MatrixTest, MatrixMultiplication)
{
    using namespace pnmstream;
    mat2 a{1.0f, 2.0f, 3.0f, 4.0f};
    mat2 b{5.0f, 6.0f, 7.0f, 8.0f};
    auto r = a * b;
    // [1*5+2*7, 1*6+2*8; 3*5+4*7, 3*6+4*8]
    EXPECT_FLOAT_EQ(r(0, 0), 19.0f);
    EXPECT_FLOAT_EQ(r(0, 1), 22.0f);
    EXPECT_FLOAT_EQ(r(1, 0), 43.0f);
    EXPECT_FLOAT_EQ(r(1, 1), 50.0f);
}

TEST(MatrixTest, MatrixEquality)
{
    using namespace pnmstream;
    mat2 a{1.0f, 2.0f, 3.0f, 4.0f};
    mat2 b{1.0f, 2.0f, 3.0f, 4.0f};
    mat2 c{1.0f, 2.0f, 3.0f, 5.0f};
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

// ============================================================
// Compile-time constexpr checks
// ============================================================

TEST(ConstexprTest, VecConstexpr)
{
    constexpr pnmstream::vec2 a(1.0f, 2.0f);
    constexpr pnmstream::vec2 b(3.0f, 4.0f);
    constexpr auto sum = a + b;
    static_assert(sum.x() == 4.0f, "constexpr vec addition failed");
}

// Matrix::operator() throws on bounds error, so constexpr is not available.
