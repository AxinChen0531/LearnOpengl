#pragma once

#include "Shader.h"
#include "Log.h"
#include <memory>

#include <GL/glew.h>

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

class Material
{
private:
	unsigned int m_id;

	int m_srcfactor;
	int m_dstfactor;

	int m_zTestCondition;

	bool m_needBlend;
	bool m_needZTest;
	bool m_needZWrite;

public:
	Material(const Shader& shader);
	~Material();

	inline unsigned int GetID() const
	{
		return m_id;
	}
	void Use() const;
	inline void Unuse() const
	{
		glUseProgram(0);
	}

	inline void EnableBlend() 
	{
		m_needBlend = true;
	}
	inline void DisableBlend()
	{
		m_needBlend = false;
	}
	inline void SetBlendParam(const BlendParam srcf, const BlendParam dstf)
	{
		m_srcfactor = srcf;
		m_dstfactor = dstf;
		m_needBlend = true;
	}
	inline void EnableZTest()
	{
		m_needZTest = true;
	}
	inline void DisableZTest()
	{
		m_needZTest = false;
	}
	inline void SetZTestParam(const ZTestCondition condition)
	{
		m_zTestCondition = condition;
		m_needZTest = true;
	}
	inline void EnableZWrite()
	{
		m_needZWrite = true;
	}
	inline void DisableZWrite()
	{
		m_needZWrite = false;
	}
};