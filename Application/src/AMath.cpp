#include "AMath.h"

const float Mathf::PI = acosf(-1.0f);
const float Mathf::Deg2Rad = Mathf::PI / 180.0f;
const float Mathf::Rad2Deg = 180.0f / Mathf::PI;

float Mathf::FPow(float n, int p)
{
	if (p < 0)
		throw "FPow's p should bigger than or equal to 0";
	float t = 1.0f;
	while (p != 0) {
		if (p & 1)
			t *= n;
		p >>= 1;
		n *= n;
	}
	return t;
}

float Mathf::FPow(int n, int p)
{
	if (p < 0)
		throw "FPow's p should bigger than or equal to 0";
	int t = 1;
	while (p != 0) {
		if (p & 1)
			t *= n;
		p >>= 1;
		n *= n;
	}
	return t;
}

float Mathf::Clamp(float num, float min, float max)
{
	if (num < min)
		return min;
	else if (num > max)
		return max;
	else
		return num;
}

float Mathf::Lerp(float from, float to, float k, bool limit)
{
	if (limit)
		k = Saturate(k);
	return from * k + to * (1 - k);
}

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

Vec2 Vec2::Normalized() const
{
	float len = Len();
	if (len > 1E-05f)
		return (*this) * (1 / len);
	else
		return Vec2::Zero();
}

Vec2 Vec2::Lerp(const Vec2& other, float k, bool limit) const
{
	if (limit)
		k = Mathf::Saturate(k);
	return (*this) * k + other * (1 - k);
}

Vec3::Vec3() : m_x(0), m_y(0), m_z(0)
{
}

Vec3::Vec3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
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

Vec3 Vec3::Normalized() const
{
	float len = Len();
	if (len > 1E-05f)
		return (*this) * (1 / len);
	else
		return Vec3::Zero();
}

Vec3 Vec3::Lerp(const Vec3& other, float k, bool limit) const
{
	if (limit)
		k = Mathf::Saturate(k);
	return (*this) * k + other * (1 - k);
}

Vec4::Vec4() : m_x(0), m_y(0), m_z(0), m_w(0)
{
}

Vec4::Vec4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w)
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

Matrix2x2::Matrix2x2()
{
	memset(m_p, 0, sizeof(m_p));
}

Matrix2x2::Matrix2x2(const Matrix2x2& other)
{
	memcpy(m_p, &other, sizeof(m_p));
}

Matrix2x2::Matrix2x2(const Matrix3x3& other)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m_p[i][j] = other[i][j];
}

Matrix2x2::Matrix2x2(const Matrix4x4& other)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m_p[i][j] = other[i][j];
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const
{
	Matrix2x2 res = Matrix2x2();
	float* r = (float*)&res;
	float* a = (float*)(this);
	float* b = (float*)&other;
	for (int i = 0; i < 4; i++) {
		*r = *a + *b;
		r++;
		a++;
		b++;
	}
	return res;
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other) const
{
	Matrix2x2 res = Matrix2x2();
	float* r = (float*)&res;
	float* a = (float*)(this);
	float* b = (float*)&other;
	for (int i = 0; i < 4; i++) {
		*r = *a - *b;
		r++;
		a++;
		b++;
	}
	return res;
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2& other) const
{
	Matrix2x2 res = Matrix2x2();
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				res[i][j] += m_p[i][k] * other[k][j];
	return res;
}

Vec2 Matrix2x2::operator*(const Vec2 vec) const
{
	Vec2 res = Vec2();
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			res[i] += m_p[i][j] * vec[j];
	return res;
}

Matrix3x3::Matrix3x3()
{
	memset(m_p, 0, sizeof(m_p));
}

Matrix3x3::Matrix3x3(const Matrix2x2& other)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m_p[i][j] = other[i][j];
	for (int i = 0; i < 2; i++) {
		m_p[2][i] = 0;
		m_p[i][2] = 0;
	}
	m_p[2][2] = 1;
}

Matrix3x3::Matrix3x3(const Matrix3x3& other)
{
	memcpy(m_p, &other, sizeof(m_p));
}

Matrix3x3::Matrix3x3(const Matrix4x4& other)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m_p[i][j] = other[i][j];
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const
{
	Matrix3x3 res = Matrix3x3();
	float* r = (float*)&res;
	float* a = (float*)(this);
	float* b = (float*)&other;
	for (int i = 0; i < 9; i++) {
		*r = *a + *b;
		r++;
		a++;
		b++;
	}
	return res;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const
{
	Matrix3x3 res = Matrix3x3();
	float* r = (float*)&res;
	float* a = (float*)(this);
	float* b = (float*)&other;
	for (int i = 0; i < 9; i++) {
		*r = *a - *b;
		r++;
		a++;
		b++;
	}
	return res;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const
{
	Matrix3x3 res = Matrix3x3();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				res[i][j] += m_p[i][k] * other[k][j];
	return res;
}

Vec3 Matrix3x3::operator*(const Vec3& vec) const
{
	Vec3 res = Vec3();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			res[i] += m_p[i][j] * vec[j];
	return res;
}

Matrix4x4::Matrix4x4()
{
	memset(m_p, 0, sizeof(m_p));
}

Matrix4x4::Matrix4x4(const Matrix2x2& other)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m_p[i][j] = other[i][j];
	for (int i = 0; i < 2; i++) {
		m_p[2][i] = 0;
		m_p[i][2] = 0;
	}
	for (int i = 0; i < 3; i++) {
		m_p[3][i] = 0;
		m_p[i][3] = 0;
	}
	m_p[2][2] = 1;
	m_p[3][3] = 1;
}

Matrix4x4::Matrix4x4(const Matrix3x3& other)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m_p[i][j] = other[i][j];
	for (int i = 0; i < 3; i++) {
		m_p[3][i] = 0;
		m_p[i][3] = 0;
	}
	m_p[2][2] = 1;
	m_p[3][3] = 1;
}

Matrix4x4::Matrix4x4(const Matrix4x4& other)
{
	memcpy(m_p, &other, sizeof(m_p));
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
{
	Matrix4x4 res = Matrix4x4();
	float* r = (float*)&res;
	float* a = (float*)(this);
	float* b = (float*)&other;
	for (int i = 0; i < 16; i++) {
		*r = *a + *b;
		r++;
		a++;
		b++;
	}
	return res;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const
{
	Matrix4x4 res = Matrix4x4();
	float* r = (float*)&res;
	float* a = (float*)(this);
	float* b = (float*)&other;
	for (int i = 0; i < 16; i++) {
		*r = *a - *b;
		r++;
		a++;
		b++;
	}
	return res;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
{
	Matrix4x4 res = Matrix4x4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				res[i][j] += m_p[i][k] * other[k][j];
	return res;
}

Vec4 Matrix4x4::operator*(const Vec4& vec) const
{
	Vec4 res = Vec4();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			res[i] += m_p[i][j] * vec[j];
	return res;
}
