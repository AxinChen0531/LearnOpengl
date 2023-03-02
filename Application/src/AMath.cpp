/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : 渲染引擎常用数学库
 */

#include <memory>
#include <exception>

#include "AMath.h"

const float Mathf::PI = acosf(-1.0f);
const float Mathf::Deg2Rad = Mathf::PI / 180.0f;
const float Mathf::Rad2Deg = 180.0f / Mathf::PI;

float Mathf::FPow(float n, int p)
{
	if (p < 0)
		throw std::exception("FPow's p should bigger than or equal to 0");
	float t = 1.0f;
	while (p != 0) {
		if (p & 1)
			t *= n;
		p >>= 1;
		n *= n;
	}
	return t;
}

int Mathf::FPow(int n, int p)
{
	if (p < 0)
		throw std::exception("FPow's p should bigger than or equal to 0");
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
	return from + (to - from) * k;
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
	return *this + (other - *this) * k;
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

Vec3 Vec3::Rotate(const Quaternion& rotation) const
{
	float x1 = rotation.m_w * m_x + rotation.m_z * m_y - rotation.m_y * m_z;
	float y1 = rotation.m_w * m_y + rotation.m_x * m_z - rotation.m_z * m_x;
	float z1 = rotation.m_w * m_z + rotation.m_y * m_x - rotation.m_x * m_y;
	float w1 = -rotation.m_x * m_x - rotation.m_y * m_y - rotation.m_z * m_z;
	return Vec3(
		x1 * rotation.m_w - z1 * rotation.m_y + y1 * rotation.m_z - w1 * rotation.m_x,
		z1 * rotation.m_x - w1 * rotation.m_y + y1 * rotation.m_w - x1 * rotation.m_z,
		x1 * rotation.m_y - w1 * rotation.m_z + z1 * rotation.m_w - y1 * rotation.m_x
	);
}

Vec3 Vec3::Lerp(const Vec3& other, float k, bool limit) const
{
	if (limit)
		k = Mathf::Saturate(k);
	return *this + (other - *this) * k;
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
	Matrix2x2 res;
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
	Matrix2x2 res;
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
	Matrix2x2 res;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				res[i][j] += m_p[i][k] * other[k][j];
	return res;
}

Vec2 Matrix2x2::operator*(const Vec2 vec) const
{
	Vec2 res;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			res[i] += m_p[i][j] * vec[j];
	return res;
}

Matrix2x2 Matrix2x2::Trans() const
{
	Matrix2x2 res;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			res[i][j] = m_p[j][i];
	return res;
}

Matrix2x2 Matrix2x2::Inverse() const
{
	Matrix2x2 tmp = *this;
	Matrix2x2 res = Matrix2x2::One();
	int n = 2;
	for (int i = 0; i < n; i++) {
		int max_row = i;
		for (int j = i + 1; j < n; j++)
			if (Mathf::Abs(tmp[j][i]) > Mathf::Abs(tmp[max_row][i]))
				max_row = j;
		if (max_row != i) {
			for (int k = 0; k < n; k++) {
				float t = tmp[i][k];
				tmp[i][k] = tmp[max_row][k];
				tmp[max_row][k] = t;
				t = res[i][k];
				res[i][k] = res[max_row][k];
				res[max_row][k] = t;

			}
		}
		float pivot = tmp[i][i];
		if (pivot == 0.0f) 
			return Matrix4x4::Zero();
		for (int j = i + 1; j < n; j++) {
			float scale = tmp[j][i] / pivot;
			for (int k = 0; k < n; k++) {
				tmp[j][k] -= scale * tmp[i][k];
				res[j][k] -= scale * res[i][k];
			}
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		float pivot = tmp[i][i];
		if (pivot == 0.0f) 
			return Matrix4x4::Zero();
		for (int j = 0; j < n; j++) 
			res[i][j] /= pivot;
		for (int j = i - 1; j >= 0; j--) {
			float scale = tmp[j][i] / pivot;
			for (int k = 0; k < n; k++) 
				res[j][k] -= scale * res[i][k];
		}
	}
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
	Matrix3x3 res;
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
	Matrix3x3 res;
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
	Matrix3x3 res;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				res[i][j] += m_p[i][k] * other[k][j];
	return res;
}

Vec3 Matrix3x3::operator*(const Vec3& vec) const
{
	Vec3 res;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			res[i] += m_p[i][j] * vec[j];
	return res;
}

Matrix3x3 Matrix3x3::Trans() const
{
	Matrix3x3 res;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			res[i][j] = m_p[j][i];
	return res;
}

Matrix3x3 Matrix3x3::Inverse() const
{
	Matrix3x3 tmp = *this;
	Matrix3x3 res = Matrix3x3::One();
	int n = 3;
	for (int i = 0; i < n; i++) {
		int max_row = i;
		for (int j = i + 1; j < n; j++)
			if (Mathf::Abs(tmp[j][i]) > Mathf::Abs(tmp[max_row][i]))
				max_row = j;
		if (max_row != i) {
			for (int k = 0; k < n; k++) {
				float t = tmp[i][k];
				tmp[i][k] = tmp[max_row][k];
				tmp[max_row][k] = t;
				t = res[i][k];
				res[i][k] = res[max_row][k];
				res[max_row][k] = t;

			}
		}
		float pivot = tmp[i][i];
		if (pivot == 0.0f) 
			return Matrix4x4::Zero();
		for (int j = i + 1; j < n; j++) {
			float scale = tmp[j][i] / pivot;
			for (int k = 0; k < n; k++) {
				tmp[j][k] -= scale * tmp[i][k];
				res[j][k] -= scale * res[i][k];
			}
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		float pivot = tmp[i][i];
		if (pivot == 0.0f) 
			return Matrix4x4::Zero();
		for (int j = 0; j < n; j++) 
			res[i][j] /= pivot;
		for (int j = i - 1; j >= 0; j--) {
			float scale = tmp[j][i] / pivot;
			for (int k = 0; k < n; k++) 
				res[j][k] -= scale * res[i][k];
		}
	}
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
	Matrix4x4 res;
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
	Matrix4x4 res;
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
	Matrix4x4 res;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				res[i][j] += m_p[i][k] * other[k][j];
	return res;
}

Vec4 Matrix4x4::operator*(const Vec4& vec) const
{
	Vec4 res;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			res[i] += m_p[i][j] * vec[j];
	return res;
}

Matrix4x4 Matrix4x4::Trans() const
{
	Matrix4x4 res;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			res[i][j] = m_p[j][i];
	return res;
}

Matrix4x4 Matrix4x4::Inverse() const
{
	Matrix4x4 tmp = *this;
	Matrix4x4 res = Matrix4x4::One();
	int n = 4;
	for (int i = 0; i < n; i++) {
		int max_row = i;
		for (int j = i + 1; j < n; j++)
			if (Mathf::Abs(tmp[j][i]) > Mathf::Abs(tmp[max_row][i]))
				max_row = j;
		if (max_row != i) {
			for (int k = 0; k < n; k++) {
				float t = tmp[i][k];
				tmp[i][k] = tmp[max_row][k];
				tmp[max_row][k] = t;
				t = res[i][k];
				res[i][k] = res[max_row][k];
				res[max_row][k] = t;
				
			}
		}
		float pivot = tmp[i][i];
		if (pivot == 0.0f) 
			return Matrix4x4::Zero();
		for (int j = i + 1; j < n; j++) {
			float scale = tmp[j][i] / pivot;
			for (int k = 0; k < n; k++) {
				tmp[j][k] -= scale * tmp[i][k];
				res[j][k] -= scale * res[i][k];
			}
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		float pivot = tmp[i][i];
		if (pivot == 0.0f) 
			return Matrix4x4::Zero();
		for (int j = 0; j < n; j++) 
			res[i][j] /= pivot;
		for (int j = i - 1; j >= 0; j--) {
			float scale = tmp[j][i] / pivot;
			for (int k = 0; k < n; k++) 
				res[j][k] -= scale * res[i][k];
		}
	}
	return res;
}

Quaternion::Quaternion() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(1.0f)
{
}

Quaternion::Quaternion(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w)
{
}

Quaternion::Quaternion(const Quaternion& other) : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z), m_w(other.m_w)
{
}

Quaternion::Quaternion(const Vec3& euler)
{
	float p = euler.GetX() * Mathf::Deg2Rad * 0.5f, h = euler.GetY() * Mathf::Deg2Rad * 0.5f, r = euler.GetZ() * Mathf::Deg2Rad * 0.5f;
	this->m_w = Mathf::Cos(h) * Mathf::Cos(p) * Mathf::Cos(r) + Mathf::Sin(h) * Mathf::Sin(p) * Mathf::Sin(r);
	this->m_x = -Mathf::Cos(h) * Mathf::Sin(p) * Mathf::Cos(r) - Mathf::Sin(h) * Mathf::Cos(p) * Mathf::Sin(r);
	this->m_y = Mathf::Cos(h) * Mathf::Sin(p) * Mathf::Sin(r) - Mathf::Sin(h) * Mathf::Cos(p) * Mathf::Cos(r);
	this->m_z = Mathf::Sin(h) * Mathf::Sin(p) * Mathf::Cos(r) - Mathf::Cos(h) * Mathf::Cos(p) * Mathf::Sin(r);
}

Quaternion::Quaternion(const Matrix3x3& matrix)
{
	float fwsm = matrix[0][0] + matrix[1][1] + matrix[2][2];
	float fxsm = matrix[0][0] - matrix[1][1] - matrix[2][2];
	float fysm = matrix[1][1] - matrix[0][0] - matrix[2][2];
	float fzsm = matrix[2][2] - matrix[0][0] - matrix[1][1];
	int bi = 0;
	float fbsm = fwsm;
	if (fxsm > fbsm) {
		fbsm = fxsm;
		bi = 1;
	}
	if (fysm > fbsm) {
		fbsm = fysm;
		bi = 2;
	}
	if (fzsm > fbsm) {
		fbsm = fzsm;
		bi = 3;
	}
	float bv = Mathf::Sqrt(fbsm + 1) * 0.5f;
	float mult = 0.25f / bv;

	switch (bi) {
	case 0:
		m_w = bv;
		m_x = (matrix[1][2] - matrix[2][1]) * mult;
		m_y = (matrix[2][0] - matrix[0][2]) * mult;
		m_z = (matrix[0][1] - matrix[1][0]) * mult;
		break;
	case 1:
		m_x = bv;
		m_w = (matrix[1][2] - matrix[2][1]) * mult;
		m_y = (matrix[1][0] + matrix[0][1]) * mult;
		m_z = (matrix[0][2] + matrix[2][0]) * mult;
		break;
	case 2:
		m_y = bv;
		m_w = (matrix[2][0] - matrix[0][2]) * mult;
		m_x = (matrix[1][0] + matrix[0][1]) * mult;
		m_z = (matrix[1][2] + matrix[2][1]) * mult;
		break;
	default:
		m_z = bv;
		m_w = (matrix[0][1] - matrix[1][0]) * mult;
		m_x = (matrix[2][0] + matrix[0][2]) * mult;
		m_y = (matrix[1][2] + matrix[2][1]) * mult;
		break;
	}
}

Vec3 Quaternion::ToEuler() const
{
	Vec3 res;
	float sp = -2.0f * (m_y * m_z + m_w * m_x);
	if (Mathf::Abs(sp) > 0.9999f) {
		res.Set(
			Mathf::Rad2Deg * 1.570796f * sp,
			Mathf::Rad2Deg * Mathf::Atan2(0.5f - m_y * m_y - m_z * m_z, -m_x * m_z - m_w * m_y),
			0.0f);
	} else {
		res.Set(
			Mathf::Rad2Deg * Mathf::Asin(sp),
			Mathf::Rad2Deg * Mathf::Atan2(0.5f - m_x * m_x - m_y * m_y, m_x * m_z - m_w * m_y),
			Mathf::Rad2Deg * Mathf::Atan2(0.5f - m_x * m_x - m_z * m_z, m_x * m_y - m_w * m_z)
		);
	}
	return res;
}

Matrix3x3 Quaternion::ToMatrix() const
{
	Matrix3x3 res;
	res[0][0] = 1.0f - 2.0f * (m_y * m_y + m_z * m_z);
	res[0][1] = 2.0f * (m_x * m_y + m_w * m_z);
	res[0][2] = 2.0f * (m_x * m_z - m_w * m_y);
	res[1][0] = 2.0f * (m_x * m_y - m_w * m_z);
	res[1][1] = 1.0f - 2.0f * (m_x * m_x + m_z * m_z);
	res[1][2] = 2.0f * (m_z * m_y + m_w * m_x);
	res[2][0] = 2.0f * (m_x * m_z + m_w * m_y);
	res[2][1] = 2.0f * (m_z * m_y - m_w * m_x);
	res[2][2] = 1.0f - 2.0f * (m_x * m_x + m_y * m_y);
	return res;
}

void Quaternion::Normalize()
{
	float mag = Mathf::Sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
	if (mag > 0.0f) {
		mag = 1.0f / mag;
		m_w *= mag;
		m_x *= mag;
		m_y *= mag;
		m_z *= mag;
	} else {
		m_w = 1.0f;
		m_x = 0.0f;
		m_y = 0.0f;
		m_z = 0.0f;
	}
}

Quaternion Quaternion::Slerp(const Quaternion& to, float k, bool limit) const
{
	if (limit)
		Mathf::Saturate(k);
	float w1 = to.m_w, x1 = to.m_x, y1 = to.m_y, z1 = to.m_z;
	float co = m_w * w1 + m_x * x1 + m_y * y1 + m_z * z1;
	if (co < 0.0f) {
		w1 = -w1;
		x1 = -x1;
		y1 = -y1;
		z1 = -z1;
		co = -co;
	}
	float k0, k1;
	if (co > 0.9999f) {
		k0 = 1.0f - k;
		k1 = k;
	} else {
		float so = Mathf::Sqrt(1.0f - co * co);
		float o = Mathf::Atan2(co, so);
		float ooso = 1.0f / so;
		k0 = Mathf::Sin((1.0f - k) * o) * ooso;
		k1 = Mathf::Sin(k * o) * ooso;
	}
	return Quaternion(m_x * k0 + x1 * k1, m_y * k0 + y1 * k1, m_z * k0 + z1 * k1, m_w * k0 + w1 * k1);
}
