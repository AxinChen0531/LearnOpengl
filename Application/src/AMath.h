/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : 渲染引擎常用数学库
 */

#pragma once

#include <cmath>

class Mathf;
class Vec2;
class Vec3;
class Vec4;
class Matrix2x2;
class Matrix3x3;
class Matrix4x4;
class Quaternion;

class Mathf final
{
public:
	/// <summary>
	/// 求绝对值
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	static inline float Abs(float num) {
		return fabsf(num);
	}

	/// <summary>
	/// 求e为底数的n的对数
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	static inline float Loge(float num) {
		return logf(num);
	}

	/// <summary>
	/// 求以f为底数的p的对数
	/// </summary>
	/// <param name="f"></param>
	/// <param name="p"></param>
	/// <returns></returns>
	static inline float Log(float f, float p) {
		return logf(p) / logf(f);
	}

	/// <summary>
	/// 求以10为底数的n的对数
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	static inline float Log10(float num) {
		return log10f(num);
	}

	/// <summary>
	/// 求以2为底数的n的对数
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	static inline float Log2(float num) {
		return log2f(num);
	}

	/// <summary>
	/// 求平方根
	/// (这里快速平方根算法似乎并没有优势，可能标准库已经被优化过)
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	static inline float Sqrt(float num) {
		return sqrtf(num);
	}

	/// <summary>
	/// 求n的p次幂
	/// </summary>
	/// <param name="n"></param>
	/// <param name="p"></param>
	/// <returns></returns>
	static inline float Pow(float n, float p) {
		return powf(n, p);
	}

	/// <summary>
	/// 求n的p次幂
	/// 快速幂，要求p>=0
	/// </summary>
	/// <param name="n"></param>
	/// <param name="p"></param>
	/// <returns></returns>
	static float FPow(float n, int p);

	/// <summary>
	/// 求n的p次幂
	/// 快速幂，要求p>=0
	/// </summary>
	/// <param name="n"></param>
	/// <param name="p"></param>
	/// <returns></returns>
	static int FPow(int n, int p);

	/// <summary>
	/// 限制num的范围
	/// </summary>
	/// <param name="num">输入</param>
	/// <param name="min">小边界</param>
	/// <param name="max">大边界</param>
	/// <returns></returns>
	static float Clamp(float num, float min, float max);

	/// <summary>
	/// 限制num的范围在0.0到1.0之间
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	static inline float Saturate(float num) {
		return Clamp(num, 0.0f, 1.0f);
	}

	/// <summary>
	/// 线性插值
	/// </summary>
	/// <param name="from">起点</param>
	/// <param name="to">终点</param>
	/// <param name="k">系数</param>
	/// <param name="limit">是否限制系数在0-1</param>
	/// <returns></returns>
	static float Lerp(float from, float to, float k, bool limit = true);

	static const float PI;			//圆周率
	static const float Deg2Rad;		//角度转弧度系数
	static const float Rad2Deg;		//弧度转角度系数

	/// <summary>
	/// 求角度sin值
	/// </summary>
	/// <param name="rad">角度(弧度)</param>
	/// <returns></returns>
	static inline float Sin(float rad) {
		return sinf(rad);
	}

	/// <summary>
	/// 求角度cos值
	/// </summary>
	/// <param name="rad">角度(弧度)</param>
	/// <returns></returns>
	static inline float Cos(float rad) {
		return cosf(rad);
	}

	/// <summary>
	/// 求角度tan值
	/// </summary>
	/// <param name="rad">角度(弧度)</param>
	/// <returns></returns>
	static inline float Tan(float rad) {
		return tanf(rad);
	}

	/// <summary>
	/// 求sin值对应的角度
	/// </summary>
	/// <param name="num">sin值</param>
	/// <returns>角度(弧度)</returns>
	static inline float Asin(float num) {
		return asinf(num);
	}

	/// <summary>
	/// 求cos值对应的角度
	/// </summary>
	/// <param name="num">cos值</param>
	/// <returns>角度(弧度)</returns>
	static inline float Acos(float num) {
		return acosf(num);
	}

	/// <summary>
	/// 求tan值对应的角度
	/// </summary>
	/// <param name="num">tan值</param>
	/// <returns>角度(弧度)</returns>
	static inline float Atan(float num) {
		return atanf(num);
	}

	/// <summary>
	/// 求(x, y)向量与x正向夹角
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static inline float Atan2(float x, float y) {
		return atan2f(y, x);
	}
};

/// <summary>
/// 2D向量, 高维向量可隐式转换为低维向量，因此请注意向量数学计算
/// </summary>
class Vec2 final
{
private:
	float m_x, m_y;
public:
	/// <summary>
	/// (0, 0)
	/// </summary>
	Vec2();
	Vec2(float x, float y);
	Vec2(const Vec2& other);

	/// <summary>
	/// (o.x, o.y)
	/// </summary>
	/// <param name="other"></param>
	/// 
	Vec2(const Vec3& other);

	/// <summary>
	/// (o.x, o.y, o.z)
	/// </summary>
	/// <param name="other"></param>
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

	/// <summary>
	/// 求向量模长的平方
	/// </summary>
	/// <returns></returns>
	inline float LenSquare() const {
		return m_x * m_x + m_y * m_y;
	}

	/// <summary>
	/// 求向量模长
	/// </summary>
	/// <returns></returns>
	inline float Len() const {
		return Mathf::Sqrt(LenSquare());
	}

	/// <summary>
	/// 求归一化向量，当向量长度小于1E-05时，将返回零向量
	/// </summary>
	/// <returns></returns>
	Vec2 Normalized() const;

	/// <summary>
	/// 求到另一点的距离平方
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline float DistSquare(const Vec2& other) const {
		float x = m_x - other.m_x, y = m_y - other.m_y;
		return x * x + y * y;
	}

	/// <summary>
	/// 求到另一点的距离
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline float Dist(const Vec2& other) const {
		return Mathf::Sqrt(DistSquare(other));
	}

	/// <summary>
	/// 向量点乘
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline float Dot(const Vec2& other) const {
		return this->m_x * other.m_x + this->m_y * other.m_y;
	}

	/// <summary>
	/// 向量线性插值
	/// </summary>
	/// <param name="other">作为目的点</param>
	/// <param name="k">插值系数</param>
	/// <param name="limit">是否限制系数到0-1</param>
	/// <returns>插值点</returns>
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

/// <summary>
/// 3D向量, 高维向量可隐式转换为低维向量，因此请注意向量数学计算
/// </summary>
class Vec3 final
{
private:
	float m_x, m_y, m_z;
public:
	/// <summary>
	/// (0, 0, 0)
	/// </summary>
	Vec3();
	Vec3(float x, float y, float z);

	/// <summary>
	/// (o.x, o.y, 0)
	/// </summary>
	/// <param name="other"></param>
	explicit Vec3(const Vec2& other);
	Vec3(const Vec3& other);
	
	/// <summary>
	/// (o.x, o.y, o.z)
	/// </summary>
	/// <param name="other"></param>
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

	/// <summary>
	/// 求向量模长平方
	/// </summary>
	/// <returns></returns>
	inline float LenSquare() const {
		return m_x * m_x + m_y * m_y + m_z * m_z;
	}

	/// <summary>
	/// 求向量模长
	/// </summary>
	/// <returns></returns>
	inline float Len() const {
		return Mathf::Sqrt(LenSquare());
	}

	/// <summary>
	/// 归一化向量，如果向量模长小于1E-05，将返回零向量
	/// </summary>
	/// <returns></returns>
	Vec3 Normalized() const;

	/// <summary>
	/// 求到另一点的距离平方
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline float DistSquare(const Vec3& other) const {
		float x = m_x - other.m_x, y = m_y - other.m_y, z = m_z - other.m_z;
		return x * x + y * y + z * z;
	}

	/// <summary>
	/// 求到另一点的距离
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline float Dist(const Vec3& other) const {
		return Mathf::Sqrt(DistSquare(other));
	}

	/// <summary>
	/// 向量点乘
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline float Dot(const Vec3& other) const {
		return this->m_x * other.m_x + this->m_y * other.m_y + this->m_z * other.m_z;
	}

	/// <summary>
	/// 向量叉乘
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline Vec3 Cross(const Vec3& other) const {
		return Vec3(
			m_y * other.m_z - m_z * other.m_y,
			m_z * other.m_x - m_x * other.m_z,
			m_x * other.m_y - m_y * other.m_x
		);
	}

	/// <summary>
	/// 向量线性插值
	/// </summary>
	/// <param name="other">作为目的点</param>
	/// <param name="k">插值系数</param>
	/// <param name="limit">是否限制插值系数到0-1</param>
	/// <returns>插值点</returns>
	Vec3 Lerp(const Vec3& other, float k, bool limit = true) const;

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

/// <summary>
/// 4D向量, 高维向量可隐式转换为低维向量，因此请注意向量数学计算
/// </summary>
class Vec4 final
{
private:
	float m_x, m_y, m_z, m_w;
public:
	/// <summary>
	/// (0, 0, 0, 0)
	/// </summary>
	Vec4();
	Vec4(float x, float y, float z, float w);

	/// <summary>
	/// (o.x, o.y, 0, 0)
	/// </summary>
	/// <param name="other"></param>
	explicit Vec4(const Vec2& other);

	/// <summary>
	/// (o.x, o.y, o.z, 0)
	/// </summary>
	/// <param name="other"></param>
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

/// <summary>
/// 2x2矩阵，请注意矩阵乘法的顺序会对结果造成影响
/// </summary>
class Matrix2x2 final
{
private:
	float m_p[2][2];
public:
	/// <summary>
	/// 矩阵全部归零
	/// </summary>
	Matrix2x2();
	Matrix2x2(const Matrix2x2& other);

	/// <summary>
	/// 取矩阵左上2x2
	/// </summary>
	/// <param name="other"></param>
	Matrix2x2(const Matrix3x3& other);

	/// <summary>
	/// 取矩阵左上2x2
	/// </summary>
	/// <param name="other"></param>
	Matrix2x2(const Matrix4x4& other);

	inline float*& operator[](int row) {
		float* res = (float*)(m_p + row);
		return res;
	}
	inline const float*& operator[](int row) const {
		const float* res = (float*)(m_p + row);
		return res;
	}

	Matrix2x2 operator+(const Matrix2x2& other) const;
	Matrix2x2 operator-(const Matrix2x2& other) const;
	Matrix2x2 operator*(const Matrix2x2& other) const;
	Vec2 operator*(const Vec2 vec) const;

	/// <summary>
	/// 获取转置矩阵
	/// </summary>
	/// <returns></returns>
	Matrix2x2 Trans() const;

	/// <summary>
	/// 获取逆矩阵
	/// </summary>
	/// <returns></returns>
	Matrix2x2 Inverse() const;


	static Matrix2x2 Zero() {
		return Matrix2x2();
	}
	static Matrix2x2 One() {
		Matrix2x2 res;
		res[1][1] = res[0][0] = 1;
		return res;
	}
};

/// <summary>
/// 3x3矩阵，请注意矩阵乘法的顺序会对结果造成影响
/// </summary>
class Matrix3x3 final
{
private:
	float m_p[3][3];
public:
	/// <summary>
	/// 矩阵全部归零
	/// </summary>
	Matrix3x3();

	/// <summary>
	/// 左上2x2部分复制，[2][2]取1，其余取0
	/// </summary>
	/// <param name="other"></param>
	explicit Matrix3x3(const Matrix2x2& other);
	Matrix3x3(const Matrix3x3& other);

	/// <summary>
	/// 取左上3x3部分
	/// </summary>
	/// <param name="other"></param>
	Matrix3x3(const Matrix4x4& other);

	inline float*& operator[](int row) {
		float* res = (float*)(m_p + row);
		return res;
	}
	inline const float*& operator[](int row) const {
		const float* res = (float*)(m_p + row);
		return res;
	}

	Matrix3x3 operator+(const Matrix3x3& other) const;
	Matrix3x3 operator-(const Matrix3x3& other) const;
	Matrix3x3 operator*(const Matrix3x3& other) const;
	Vec3 operator*(const Vec3& vec) const;

	/// <summary>
	/// 获取转置矩阵
	/// </summary>
	/// <returns></returns>
	Matrix3x3 Trans() const;

	/// <summary>
	/// 获取逆矩阵
	/// </summary>
	/// <returns></returns>
	Matrix3x3 Inverse() const;

	static Matrix3x3 Zero() {
		return Matrix3x3();
	}
	static Matrix3x3 One() {
		Matrix3x3 res;
		res[2][2] = res[1][1] = res[0][0] = 1;
		return res;
	}
};

/// <summary>
/// 4x4矩阵，请注意矩阵乘法的顺序会对结果造成影响
/// </summary>
class Matrix4x4 final
{
private:
	float m_p[4][4];
public:
	/// <summary>
	/// 矩阵全部归零
	/// </summary>
	Matrix4x4();

	/// <summary>
	/// 左上2x2部分复制，[2][2]与[3][3]取1，其余取0
	/// </summary>
	/// <param name="other"></param>
	explicit Matrix4x4(const Matrix2x2& other);

	/// <summary>
	/// 左上3x3部分复制，[3][3]取1，其余取0
	/// </summary>
	/// <param name="other"></param>
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

	Matrix4x4 operator+(const Matrix4x4& other) const;
	Matrix4x4 operator-(const Matrix4x4& other) const;
	Matrix4x4 operator*(const Matrix4x4& other) const;
	Vec4 operator*(const Vec4& vec) const;

	/// <summary>
	/// 获取转置矩阵
	/// </summary>
	/// <returns></returns>
	Matrix4x4 Trans() const;

	/// <summary>
	/// 获取逆矩阵
	/// </summary>
	/// <returns></returns>
	Matrix4x4 Inverse() const;

	static Matrix4x4 Zero() {
		return Matrix4x4();
	}
	static Matrix4x4 One() {
		Matrix4x4 res;
		res[3][3] = res[2][2] = res[1][1] = res[0][0] = 1;
		return res;
	}
};

/// <summary>
/// 表示旋转的四元数，这里统一只能得到单位四元数，表方向
/// </summary>
class Quaternion final
{
private:
	float m_w, m_x, m_y, m_z;
public:
	/// <summary>
	/// 默认单位四元数
	/// </summary>
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Quaternion& other);

	/// <summary>
	/// 从欧拉角(Degree)转到四元数
	/// </summary>
	/// <param name="euler"></param>
	explicit Quaternion(const Vec3& euler);

	/// <summary>
	/// 从旋转矩阵转到四元数
	/// </summary>
	/// <param name="matrix"></param>
	explicit Quaternion(const Matrix3x3& matrix);

	/// <summary>
	/// 四元数转欧拉角
	/// </summary>
	/// <returns></returns>
	Vec3 ToEuler() const;

	/// <summary>
	/// 四元数转旋转矩阵
	/// </summary>
	/// <returns></returns>
	Matrix3x3 ToMatrix() const;

	/// <summary>
	/// 单位化，用于避免累积误差
	/// 四元数类默认所有值模长1，因此当可能出现误差时，请手动调用此函数
	/// </summary>
	void Normalize();

	/// <summary>
	/// 旋转量均匀差值
	/// </summary>
	/// <param name="to">作为目的旋转量</param>
	/// <param name="k">插值系数</param>
	/// <param name="limit">是否将系数限制到0-1</param>
	/// <returns>插值结果</returns>
	Quaternion Slerp(const Quaternion& to, float k, bool limit = true) const;

	/// <summary>
	/// 取相反旋转量
	/// </summary>
	/// <returns></returns>
	inline Quaternion operator-() const {
		return Quaternion(m_x, m_y, m_z, -m_w);
	}

	/// <summary>
	/// 两旋转叠加，先转乘数，再旋转被乘数
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	inline Quaternion operator*(const Quaternion& other) const {
		return Quaternion(
			m_w * other.m_x + m_x * other.m_w + m_z * other.m_y - m_y * other.m_z,
			m_w * other.m_y + m_y * other.m_w + m_x * other.m_z - m_z * other.m_x,
			m_w * other.m_z + m_z * other.m_w + m_y * other.m_x - m_x * other.m_y,
			m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z
		);
	}

	/// <summary>
	/// 两旋转差值，从减数到被减数
	/// </summary>
	/// <param name="other">出发点</param>
	/// <returns>旋转差值</returns>
	inline Quaternion operator-(const Quaternion& other) const {
		return Quaternion(
			m_w * other.m_x - m_x * other.m_w + m_z * other.m_y - m_y * other.m_z,
			m_w * other.m_y - m_y * other.m_w + m_x * other.m_z - m_z * other.m_x,
			m_w * other.m_z - m_z * other.m_w + m_y * other.m_x - m_x * other.m_y,
			-m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z
		);
	}

	static inline Quaternion Identity() {
		return Quaternion();
	}
};