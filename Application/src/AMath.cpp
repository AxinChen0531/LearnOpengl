#include "AMath.h"

Vec2::Vec2() : m_x(0), m_y(0)
{
}

Vec2::Vec2(float x, float y) : m_x(x), m_y(y)
{
}

Vec2::Vec2(const Vec2& other) : m_x(other.m_x), m_y(other.m_y)
{
}

Vec2::Vec2(const Vec3& other) : m_x(other.GetX()), m_y(other.GetY())
{
}

Vec2::Vec2(const Vec4& other) : m_x(other.GetX()), m_y(other.GetY())
{
}

Vec3::Vec3() : m_x(0), m_y(0), m_z(0)
{
}

Vec3::Vec3(float x, float y, float z) : m_x(x), m_y(x), m_z(z)
{
}

Vec3::Vec3(const Vec2& other) : m_x(other.GetX()), m_y(other.GetY()), m_z(0)
{
}

Vec3::Vec3(const Vec3& other) : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z)
{
}

Vec3::Vec3(const Vec4& other) : m_x(other.GetX()), m_y(other.GetY()), m_z(other.GetZ())
{
}

Vec4::Vec4() : m_x(0), m_y(0), m_z(0), m_w(0)
{
}

Vec4::Vec4(float x, float y, float z, float w) : m_x(x), m_y(x), m_z(z), m_w(w)
{
}

Vec4::Vec4(const Vec2& other) : m_x(other.GetX()), m_y(other.GetY()), m_z(0), m_w(0)
{
}

Vec4::Vec4(const Vec3& other) : m_x(other.GetX()), m_y(other.GetY()), m_z(other.GetZ()), m_w(0)
{
}

Vec4::Vec4(const Vec4& other) : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_w(other.m_w)
{
}