#pragma once
#include <cmath>
#include <memory>

class Vec2;
class Vec3;
class Vec4;
class Matrix2x2;
class Matrix3x3;
class Matrix4x4;

class Vec2 final
{
private:
	float m_x, m_y;
public:
	Vec2();
	Vec2(float x, float y);
	Vec2(const Vec2& other);
	Vec2(const Vec3& other);
	Vec2(const Vec4& other);

	inline float GetX() const {
		return m_x;
	}
	inline float GetY() const {
		return m_y;
	}
	inline void SetX(float x) {
		m_x = x;
	}
	inline void SetY(float y) {
		m_y = y;
	}
	inline void Set(float x, float y) {
		SetX(x);
		SetY(y);
	}

	inline float GetDistSquare() const {
		return m_x * m_x + m_y * m_y;
	}
	inline float GetDist() const {
		return sqrtf(GetDistSquare());
	}

	inline float Dot(const Vec2& other) const {
		return this->m_x * other.m_x + this->m_y * other.m_y;
	}
	
	inline Vec2 operator+(const Vec2& other) const {
		return Vec2(this->m_x + other.m_x, this->m_y + other.m_y);
	}
	inline Vec2 operator+(float num) const {
		return Vec2(this->m_x + num, this->m_y + num);
	}
	inline Vec2 operator-(const Vec2& other) const {
		return Vec2(this->m_x - other.m_x, this->m_y - other.m_y);
	}
	inline Vec2 operator-(float num) const {
		return Vec2(this->m_x - num, this->m_y - num);
	}
	inline Vec2 operator*(const Vec2& other) const {
		return Vec2(this->m_x * other.m_x, this->m_y * other.m_y);
	}
	inline Vec2 operator*(float num) const {
		return Vec2(this->m_x * num, this->m_y * num);
	}
};

class Vec3
{
private:
	float m_x, m_y, m_z;
public:
	Vec3();
	Vec3(float x, float y, float z);
	explicit Vec3(const Vec2& other);
	Vec3(const Vec3& other);
	Vec3(const Vec4& other);

	inline float GetX() const {
		return m_x;
	}
	inline float GetY() const {
		return m_y;
	}
	inline float GetZ() const {
		return m_z;
	}
	inline void SetX(float x) {
		this->m_x = x;
	}
	inline void SetY(float y) {
		this->m_y = y;
	}
	inline void SetZ(float z) {
		this->m_z = z;
	}
	inline void Set(float x, float y, float z) {
		SetX(x);
		SetY(y);
		SetZ(z);
	}

	inline float GetDistSqure() const {
		return m_x * m_x + m_y * m_y + m_z * m_z;
	}
	inline float GetDist() const {
		return sqrtf(GetDistSqure());
	}

	inline float Dot(const Vec3& other) const {
		return this->m_x * other.m_x + this->m_y * other.m_y + this->m_z * other.m_z;
	}
	inline Vec3 Cross(const Vec3& other) const {
		return Vec3(
			m_y * other.m_z - m_z * other.m_y,
			m_z * other.m_x - m_x * other.m_z,
			m_x * other.m_y - m_y * other.m_x
		);
	}

	inline Vec3 operator+(const Vec3& other) const {
		return Vec3(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z);
	}
	inline Vec3 operator+(float num) const {
		return Vec3(this->m_x + num, this->m_y + num, this->m_z + num);
	}
	inline Vec3 operator-(const Vec3& other) const {
		return Vec3(this->m_x - other.m_x, this->m_y - other.m_y, this->m_z - other.m_z);
	}
	inline Vec3 operator-(float num) const {
		return Vec3(this->m_x - num, this->m_y - num, this->m_z - num);
	}
	inline Vec3 operator*(const Vec3& other) const {
		return Vec3(this->m_x * other.m_x, this->m_y * other.m_y, this->m_z * other.m_z);
	}
	inline Vec3 operator*(float num) const {
		return Vec3(this->m_x * num, this->m_y * num, this->m_z * num);
	}
};

class Vec4
{
private:
	float m_x, m_y, m_z, m_w;
public:
	Vec4();
	Vec4(float x, float y, float z, float w);
	explicit Vec4(const Vec2& other);
	explicit Vec4(const Vec3& other);
	Vec4(const Vec4& other);

	inline float GetX() const {
		return m_x;
	}
	inline float GetY() const {
		return m_y;
	}
	inline float GetZ() const {
		return m_z;
	}
	inline float GetW() const {
		return m_w;
	}
	inline void SetX(float x) {
		this->m_x = x;
	}
	inline void SetY(float y) {
		this->m_y = y;
	}
	inline void SetZ(float z) {
		this->m_z = z;
	}
	inline void SetW(float w) {
		this->m_w = m_w;
	}
	inline void Set(float x, float y, float z, float w) {
		SetX(x);
		SetY(y);
		SetZ(z);
		SetW(w);
	}

	inline Vec4 operator+(const Vec4& other) const {
		return Vec4(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z, this->m_w + other.m_w);
	}
	inline Vec4 operator+(float num) const {
		return Vec4(this->m_x + num, this->m_y + num, this->m_z + num, this->m_w + num);
	}
	inline Vec4 operator-(const Vec4& other) const {
		return Vec4(this->m_x - other.m_x, this->m_y - other.m_y, this->m_z - other.m_z, this->m_w - m_w);
	}
	inline Vec4 operator-(float num) const {
		return Vec4(this->m_x - num, this->m_y - num, this->m_z - num, this->m_w - num);
	}
	inline Vec4 operator*(const Vec4& other) const {
		return Vec4(this->m_x * other.m_x, this->m_y * other.m_y, this->m_z * other.m_z, this->m_w * other.m_w);
	}
	inline Vec4 operator*(float num) const {
		return Vec4(this->m_x * num, this->m_y * num, this->m_z * num, this->m_w * num);
	}
};

class Matrix2x2
{
private:
	float m_p[4];
public:
	Matrix2x2();
	Matrix2x2(const Matrix2x2& other);
	Matrix2x2(const Matrix3x3& other);
	Matrix2x2(const Matrix4x4& other);

	inline float*& operator[](int row) {
		float* res;
		res = m_p + (row << 1);
		return res;
	}
	inline const float*& operator[](int row) const {
		const float* res;
		res = m_p + (row << 1);
		return res;
	}

	Matrix2x2 operator+(const Matrix2x2 other) const;
	Matrix2x2 operator-(const Matrix2x2 other) const;
	Matrix2x2 operator*(const Matrix2x2 other) const;
	Vec2 operator*(const Vec2 vec) const;
};

class Matrix3x3
{
private:
	float m_p[9];
public:
	Matrix3x3();
	explicit Matrix3x3(const Matrix2x2& other);
	Matrix3x3(const Matrix3x3& other);
	Matrix3x3(const Matrix4x4& other);

	inline float*& operator[](int row) {
		float* res;
		res = m_p + (row << 1);
		return res;
	}
	inline const float*& operator[](int row) const {
		const float* res;
		res = m_p + (row << 1);
		return res;
	}

	Matrix3x3 operator+(const Matrix3x3 other) const;
	Matrix3x3 operator-(const Matrix3x3 other) const;
	Matrix3x3 operator*(const Matrix3x3 other) const;
	Vec3 operator*(const Vec3 vec) const;
};

class Matrix4x4
{
private:
	float m_p[9];
public:
	Matrix4x4();
	explicit Matrix4x4(const Matrix2x2& other);
	explicit Matrix4x4(const Matrix3x3& other);
	Matrix4x4(const Matrix4x4& other);

	inline float*& operator[](int row) {
		float* res;
		res = m_p + (row << 1);
		return res;
	}
	inline const float*& operator[](int row) const {
		const float* res;
		res = m_p + (row << 1);
		return res;
	}

	Matrix4x4 operator+(const Matrix4x4 other) const;
	Matrix4x4 operator-(const Matrix4x4 other) const;
	Matrix4x4 operator*(const Matrix4x4 other) const;
	Vec4 operator*(const Vec4 vec) const;
};