#pragma once
#include <cmath>
#include <memory>

class Mathf
{
public:
	static inline float Abs(float num) {
		return fabsf(num);
	}
	static inline float Loge(float num) {
		return logf(num);
	}
	static inline float Log(float f, float p) {
		return logf(p) / logf(f);
	}
	static inline float Log10(float num) {
		return log10f(num);
	}
	static inline float Log2(float num) {
		return log2f(num);
	}
	static inline float Sqrt(float num) {
		return sqrtf(num);
	}
	static inline float Pow(float n, float p) {
		return powf(n, p);
	}
	static float FPow(float n, int p);
	static float FPow(int n, int p);
	static float Clamp(float num, float min, float max);
	static inline float Saturate(float num) {
		return Clamp(num, 0.0f, 1.0f);
	}
	static float Lerp(float from, float to, float k, bool limit = true);

	static const float PI;
	static const float Deg2Rad;
	static const float Rad2Deg;
	static inline float Sin(float num) {
		return sinf(num);
	}
	static inline float Cos(float num) {
		return cosf(num);
	}
	static inline float Tan(float num) {
		return tanf(num);
	}
	static inline float Asin(float num) {
		return asinf(num);
	}
	static inline float Acos(float num) {
		return acosf(num);
	}
	static inline float Atan(float num) {
		return atanf(num);
	}
};

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

	inline float& operator[](int n) {
		return *((float*)this + n);
	}
	inline const float& operator[](int n) const {
		return *((float*)this + n);
	}
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

	inline float LenSquare() const {
		return m_x * m_x + m_y * m_y;
	}
	inline float Len() const {
		return Mathf::Sqrt(LenSquare());
	}
	Vec2 Normalized() const;
	inline float DistSquare(const Vec2& other) const {
		float x = m_x - other.m_x, y = m_y - other.m_y;
		return x * x + y * y;
	}
	inline float Dist(const Vec2& other) const {
		return Mathf::Sqrt(DistSquare(other));
	}

	inline float Dot(const Vec2& other) const {
		return this->m_x * other.m_x + this->m_y * other.m_y;
	}
	Vec2 Lerp(const Vec2& other, float k, bool limit = true) const;
	
	inline Vec2 operator-() const {
		return Vec2(-m_x, -m_y);
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

	static Vec2 Zero() {
		return Vec2();
	}
	static Vec2 One() {
		return Vec2(1.0f, 1.0f);
	}
	static Vec2 Up() {
		return Vec2(0.0f, 1.0f);
	}
	static Vec2 Down() {
		return Vec2(0.0f, -1.0f);
	}
	static Vec2 Right() {
		return Vec2(1.0f, 0.0f);
	}
	static Vec2 Left() {
		return Vec2(-1.0f, 0.0f);
	}
};

class Vec3 final
{
private:
	float m_x, m_y, m_z;
public:
	Vec3();
	Vec3(float x, float y, float z);
	explicit Vec3(const Vec2& other);
	Vec3(const Vec3& other);
	Vec3(const Vec4& other);

	inline float& operator[](int n) {
		return *((float*)this + n);
	}
	inline const float& operator[](int n) const {
		return *((float*)this + n);
	}
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

	inline float LenSquare() const {
		return m_x * m_x + m_y * m_y + m_z * m_z;
	}
	inline float Len() const {
		return Mathf::Sqrt(LenSquare());
	}
	Vec3 Normalized() const;
	inline float DistSquare(const Vec3& other) const {
		float x = m_x - other.m_x, y = m_y - other.m_y, z = m_z - other.m_z;
		return x * x + y * y + z * z;
	}
	inline float Dist(const Vec3& other) const {
		return Mathf::Sqrt(DistSquare(other));
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

	inline Vec3 operator-() const {
		return Vec3(-m_x, -m_y, -m_z);
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

	static Vec3 Zero() {
		return Vec3();
	}
	static Vec3 One() {
		return Vec3(1.0f, 1.0f, 1.0f);
	}
	static Vec3 Up() {
		return Vec3(0.0f, 1.0f, 0.0f);
	}
	static Vec3 Down() {
		return Vec3(0.0f, -1.0f, 0.0f);
	}
	static Vec3 Right() {
		return Vec3(1.0f, 0.0f, 0.0f);
	}
	static Vec3 Left() {
		return Vec3(-1.0f, 0.0f, 0.0f);
	}
	static Vec3 Front() {
		return Vec3(0.0f, 0.0f, 1.0f);
	}
	static Vec3 Back() {
		return Vec3(0.0f, 0.0f, -1.0f);
	}
};

class Vec4 final
{
private:
	float m_x, m_y, m_z, m_w;
public:
	Vec4();
	Vec4(float x, float y, float z, float w);
	explicit Vec4(const Vec2& other);
	explicit Vec4(const Vec3& other);
	Vec4(const Vec4& other);

	inline float& operator[](int n) {
		return *((float*)this + n);
	}
	inline const float& operator[](int n) const {
		return *((float*)this + n);
	}
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

	inline Vec4 operator-() const {
		return Vec4(-m_x, -m_y, -m_z, -m_w);
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

	static Vec4 Zero() {
		return Vec4();
	}
	static Vec4 One() {
		return Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
};

class Matrix2x2 final
{
private:
	float m_p[2][2];
public:
	Matrix2x2();
	Matrix2x2(const Matrix2x2& other);
	Matrix2x2(const Matrix3x3& other);
	Matrix2x2(const Matrix4x4& other);

	inline float*& operator[](int row) {
		float* res = (float*)(m_p + row);
		return res;
	}
	inline const float*& operator[](int row) const {
		const float* res = (float*)(m_p + row);
		return res;
	}

	Matrix2x2 operator+(const Matrix2x2 other) const;
	Matrix2x2 operator-(const Matrix2x2 other) const;
	Matrix2x2 operator*(const Matrix2x2 other) const;
	Vec2 operator*(const Vec2 vec) const;

	static Matrix2x2 Zero() {
		return Matrix2x2();
	}
	static Matrix2x2 One() {
		Matrix2x2 res;
		res[1][1] = res[0][0] = 1;
		return res;
	}
};

class Matrix3x3 final
{
private:
	float m_p[3][3];
public:
	Matrix3x3();
	explicit Matrix3x3(const Matrix2x2& other);
	Matrix3x3(const Matrix3x3& other);
	Matrix3x3(const Matrix4x4& other);

	inline float*& operator[](int row) {
		float* res = (float*)(m_p + row);
		return res;
	}
	inline const float*& operator[](int row) const {
		const float* res = (float*)(m_p + row);
		return res;
	}

	Matrix3x3 operator+(const Matrix3x3 other) const;
	Matrix3x3 operator-(const Matrix3x3 other) const;
	Matrix3x3 operator*(const Matrix3x3 other) const;
	Vec3 operator*(const Vec3 vec) const;

	static Matrix3x3 Zero() {
		return Matrix3x3();
	}
	static Matrix3x3 One() {
		Matrix3x3 res;
		res[2][2] = res[1][1] = res[0][0] = 1;
		return res;
	}
};

class Matrix4x4 final
{
private:
	float m_p[4][4];
public:
	Matrix4x4();
	explicit Matrix4x4(const Matrix2x2& other);
	explicit Matrix4x4(const Matrix3x3& other);
	Matrix4x4(const Matrix4x4& other);

	inline float*& operator[](int row) {
		float* res = (float*)(m_p + row);
		return res;
	}
	inline const float*& operator[](int row) const {
		const float* res = (float*)(m_p + row);
		return res;
	}

	Matrix4x4 operator+(const Matrix4x4 other) const;
	Matrix4x4 operator-(const Matrix4x4 other) const;
	Matrix4x4 operator*(const Matrix4x4 other) const;
	Vec4 operator*(const Vec4 vec) const;

	static Matrix4x4 Zero() {
		return Matrix4x4();
	}
	static Matrix4x4 One() {
		Matrix4x4 res;
		res[3][3] = res[2][2] = res[1][1] = res[0][0] = 1;
		return res;
	}
};