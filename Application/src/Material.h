/*
 * Author  : ����(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobil   : (+86)136 4741 2733
 * Comment : ��shader programʵ������ΪMaterial��
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
/// ���ģʽ����
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
/// ��Ȳ��Բ���
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
/// Material�࣬����ͬ��shader����ʵ��
/// ��ʹ������ָ�����Material���󣬷�ֹ���ֿ���Ⱦ
/// </summary>
class Material final
{
private:
	unsigned int m_id;		//shader����ʵ��id

	int m_srcfactor;		//��ϲ��� src
	int m_dstfactor;		//��ϲ��� dst

	int m_zTestCondition;	//��Ȳ��Բ���

	bool m_needBlend;		//�Ƿ����û��
	bool m_needZTest;		//�Ƿ�������Ȳ���
	bool m_needZWrite;		//�Ƿ��������д��

	std::unordered_map<std::string, unsigned int> uniformMaps;					//uniform����λ��id����
	int m_texSlotOccupied;														//������ʹ������¼��gl�ܱ�֤����֧��16��
	std::unordered_map<int, std::pair<int, std::shared_ptr<Texture2D>>> t2ds;	//ʹ�õ��������λ�û��� location - (slot - t2d)

public:
	/// <summary>
	/// ����shader����shader����ʵ��
	/// Ĭ�����û�ϣ�������Ȳ��Ժ�д��
	/// Ĭ�ϻ�ϲ���Ϊsrc 1-src
	/// Ĭ����Ȳ���ͨ������Ϊ less
	/// </summary>
	/// <param name="shader">��Ӧshader����</param>
	Material(const Shader* shader);

	/// <summary>
	/// ����ʱ����ɾ����shader����ʵ���Դ�
	/// </summary>
	~Material();

	/// <summary>
	/// ��ȡ��shader����ʵ��id
	/// </summary>
	inline unsigned int GetID() const {
		return m_id;
	}

	/// <summary>
	/// ��ȡ��ǰ����ʹ����ͼ��۵�����(�����������)
	/// </summary>
	inline int GetTexSlotOccupied() const {
		return m_texSlotOccupied;
	}

	/// <summary>
	/// ʹ�øò��ʣ��󶨣�
	/// </summary>
	void Use() const;

	/// <summary>
	/// ���øò��ʣ����
	/// </summary>
	inline void Unuse() const {
		glUseProgram(0);
	}

	/// <summary>
	/// �������ƻ�ȡuniform������λ��id
	/// </summary>
	/// <param name="name">uniform��������</param>
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
	/// ���û��
	/// </summary>
	inline void EnableBlend() {
		m_needBlend = true;
	}

	/// <summary>
	/// ���û��
	/// </summary>
	inline void DisableBlend() {
		m_needBlend = false;
	}

	/// <summary>
	/// ���û�ϲ����û�ϲ���
	/// </summary>
	/// <param name="srcf"></param>
	/// <param name="dstf"></param>
	inline void SetBlendParam(const BlendParam srcf, const BlendParam dstf) {
		m_srcfactor = srcf;
		m_dstfactor = dstf;
		m_needBlend = true;
	}

	/// <summary>
	/// ������Ȳ���
	/// </summary>
	inline void EnableZTest() {
		m_needZTest = true;
	}

	/// <summary>
	/// ������Ȳ���
	/// </summary>
	inline void DisableZTest() {
		m_needZTest = false;
	}

	/// <summary>
	/// ������Ȳ��Բ��趨��Ȳ�����������
	/// </summary>
	/// <param name="condition">��Ȳ���ͨ������</param>
	inline void SetZTestParam(ZTestCondition condition) {
		m_zTestCondition = condition;
		m_needZTest = true;
	}

	/// <summary>
	/// �������д��
	/// </summary>
	inline void EnableZWrite() {
		m_needZWrite = true;
	}

	/// <summary>
	/// �������д��
	/// </summary>
	inline void DisableZWrite() {
		m_needZWrite = false;
	}
};