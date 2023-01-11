/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobil   : (+86)136 4741 2733
 * Comment : 将shader program实例抽象为Material类
 */

#pragma once

#include <memory>
#include <unordered_map>
#include <string>

#include "Shader.h"
#include "Texture2D.h"
#include "Log.h"

#include <GL/glew.h>

/// <summary>
/// 混合模式参数
/// </summary>
enum BlendParam
{
	ZERO = GL_ZERO,
	ONE = GL_ONE,
	SRC_COLOR = GL_SRC_COLOR,
	ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
	DST_COLOR = GL_DST_COLOR,
	ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
	SRC_ALPHA = GL_SRC_ALPHA,
	ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
	DST_ALPHA = GL_DST_ALPHA,
	ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
	CONSTANT_COLOR = GL_CONSTANT_COLOR,
	ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
	CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
	ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
	SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE,
};

/// <summary>
/// 深度测试参数
/// </summary>
enum ZTestCondition
{
	ALWAYS = GL_ALWAYS,
	NEVER = GL_NEVER,
	EQUAL = GL_EQUAL,
	NOT_EQUEAL = GL_NOTEQUAL,
	LESS = GL_LESS,
	LESS_OR_EQUAL = GL_LEQUAL,
	GREATER = GL_GREATER,
	GREATER_OR_EQUAL = GL_GEQUAL,
};

/// <summary>
/// Material类，管理不同的shader程序实例
/// 请使用智能指针管理Material对象，防止出现空渲染
/// </summary>
class Material final
{
private:
	unsigned int m_id;		//shader程序实例id

	int m_srcfactor;		//混合参数 src
	int m_dstfactor;		//混合参数 dst

	int m_zTestCondition;	//深度测试参数

	bool m_needBlend;		//是否启用混合
	bool m_needZTest;		//是否启用深度测试
	bool m_needZWrite;		//是否启用深度写入

	std::unordered_map<std::string, unsigned int> uniformMaps;					//uniform参数位置id缓存
	int m_texSlotOccupied;														//纹理插槽使用数记录，gl能保证至少支持16个
	std::unordered_map<int, std::pair<int, std::shared_ptr<Texture2D>>> t2ds;	//使用的纹理对象及位置缓存 location - (slot - t2d)

public:
	/// <summary>
	/// 根据shader生成shader程序实例
	/// 默认启用混合，启用深度测试和写入
	/// 默认混合参数为src 1-src
	/// 默认深度测试通过条件为 less
	/// </summary>
	/// <param name="shader">对应shader对象</param>
	Material(const Shader* shader);

	/// <summary>
	/// 析构时，将删除该shader程序实例显存
	/// </summary>
	~Material();

	/// <summary>
	/// 获取该shader程序实例id
	/// </summary>
	inline unsigned int GetID() const {
		return m_id;
	}

	/// <summary>
	/// 获取当前材质使用贴图插槽的数量(此数不会减少)
	/// </summary>
	inline int GetTexSlotOccupied() const {
		return m_texSlotOccupied;
	}

	/// <summary>
	/// 使用该材质（绑定）
	/// </summary>
	void Use() const;

	/// <summary>
	/// 禁用该材质（解绑）
	/// </summary>
	inline void Unuse() const {
		glUseProgram(0);
	}

	/// <summary>
	/// 根据名称获取uniform变量的位置id
	/// </summary>
	/// <param name="name">uniform变量名称</param>
	int GetUniformID(const std::string name);


	inline void SetFloat(int id, float value) const {
		glUseProgram(m_id);
		glUniform1f(id, value);
		glUseProgram(0);
	}
	inline void SetFloat(std::string name, float value) {
		SetFloat(GetUniformID(name), value);
	}
	inline void SetVec2f(int id, float u, float v) const {
		glUseProgram(m_id);
		glUniform2f(id, u, v);
		glUseProgram(0);
	}
	inline void SetVec2f(std::string name, float u, float v) {
		SetVec2f(GetUniformID(name), u, v);
	}
	inline void SetVec3f(int id, float x, float y, float z) const {
		glUseProgram(m_id);
		glUniform3f(id, x, y, z);
		glUseProgram(0);
	}
	inline void SetVec3f(std::string name, float x, float y, float z) {
		SetVec3f(GetUniformID(name), x, y, z);
	}
	inline void SetVec4f(int id, float x, float y, float z, float w) const {
		glUseProgram(m_id);
		glUniform4f(id, x, y, z, w);
		glUseProgram(0);
	}
	inline void SetVec4f(std::string name, float x, float y, float z, float w) {
		SetVec4f(GetUniformID(name), x, y, z, w);
	}
	inline void SetInt(int id, int value) const {
		glUseProgram(m_id);
		glUniform1i(id, value);
		glUseProgram(0);
	}
	inline void SetInt(std::string name, int value) {
		SetInt(GetUniformID(name), value);
	}
	inline void SetVec2i(int id, int u, int v) const {
		glUseProgram(m_id);
		glUniform2i(id, u, v);
		glUseProgram(0);
	}
	inline void SetVec2i(std::string name, int u, int v) {
		SetVec2i(GetUniformID(name), u, v);
	}
	inline void SetVec3i(int id, int x, int y, int z) const {
		glUseProgram(m_id);
		glUniform3i(id, x, y, z);
		glUseProgram(0);
	}
	inline void SetVec3i(std::string name, int x, int y, int z) {
		SetVec3i(GetUniformID(name), x, y, z);
	}
	inline void SetVec4i(int id, int x, int y, int z, int w) const {
		glUseProgram(m_id);
		glUniform4i(id, x, y, z, w);
		glUseProgram(0);
	}
	inline void SetVec4i(std::string name, int x, int y, int z, int w) {
		SetVec4i(GetUniformID(name), x, y, z, w);
	}
	float GetFloat(int id) const;
	inline float GetFloat(std::string name) {
		return GetFloat(GetUniformID(name));
	}
	float* GetVecf(int id) const;
	inline float* GetVecf(std::string name) {
		return GetVecf(GetUniformID(name));
	}
	int GetInt(int id) const;
	inline int GetInt(std::string name) {
		return GetInt(GetUniformID(name));
	}
	int* GetVeci(int id) const;
	inline int* GetVeci(std::string name) {
		return GetVeci(GetUniformID(name));
	}

	void SetTexture2D(int id, std::shared_ptr<Texture2D> t2d);
	inline void SetTexture2D(std::string name, std::shared_ptr<Texture2D> t2d) {
		SetTexture2D(GetUniformID(name), t2d);
	}

	/// <summary>
	/// 启用混合
	/// </summary>
	inline void EnableBlend() {
		m_needBlend = true;
	}

	/// <summary>
	/// 禁用混合
	/// </summary>
	inline void DisableBlend() {
		m_needBlend = false;
	}

	/// <summary>
	/// 启用混合并设置混合参数
	/// </summary>
	/// <param name="srcf"></param>
	/// <param name="dstf"></param>
	inline void SetBlendParam(const BlendParam srcf, const BlendParam dstf) {
		m_srcfactor = srcf;
		m_dstfactor = dstf;
		m_needBlend = true;
	}

	/// <summary>
	/// 启用深度测试
	/// </summary>
	inline void EnableZTest() {
		m_needZTest = true;
	}

	/// <summary>
	/// 禁用深度测试
	/// </summary>
	inline void DisableZTest() {
		m_needZTest = false;
	}

	/// <summary>
	/// 启用深度测试并设定深度测试条件参数
	/// </summary>
	/// <param name="condition">深度测试通过条件</param>
	inline void SetZTestParam(ZTestCondition condition) {
		m_zTestCondition = condition;
		m_needZTest = true;
	}

	/// <summary>
	/// 启用深度写入
	/// </summary>
	inline void EnableZWrite() {
		m_needZWrite = true;
	}

	/// <summary>
	/// 禁用深度写入
	/// </summary>
	inline void DisableZWrite() {
		m_needZWrite = false;
	}
};