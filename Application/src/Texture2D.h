#pragma once

#include <GL/glew.h>

enum ImageFormat
{
	RGB = GL_RGB,
	RGBA = GL_RGBA,
	Alpha = GL_ALPHA,
};

enum ImageWarpingMode
{
	REPEAT = GL_REPEAT,
	MIRROR = GL_MIRRORED_REPEAT,
	FIXED = GL_CLAMP_TO_EDGE,
	CLAMP = GL_CLAMP_TO_BORDER,
};

enum ImageFilter
{
	LINEAR = GL_LINEAR,
	NEAREST = GL_NEAREST,
};

class Texture2D
{
private:
	unsigned int m_id;

	int m_width;
	int m_height;
	int m_channelCount;
	int m_format;

	int m_verWarping;
	int m_horWarping;
	int m_minfilter;
	int m_magfilter;

public:
	static void SetYFlip(bool flip);
	Texture2D(const char* imgPath);
	~Texture2D();

	inline void GetResolution(int* w, int* h) const
	{
		*w = m_width;
		*h = m_height;
	}
	inline ImageFormat GetFormat() const
	{
		return (ImageFormat)m_format;
	}
	inline int GetChannelCount() const
	{
		return m_channelCount;
	}

	inline void Use() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}
	inline void Unuse() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	inline void SetHorizontalWarpingMode(const ImageWarpingMode mode)
	{
		m_horWarping = mode;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_horWarping);
	}
	inline void SetVerticalWarpingMode(const ImageWarpingMode mode)
	{
		m_verWarping = mode;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_verWarping);
	}
	inline void SetMinFilter(const ImageFilter filter)
	{
		m_minfilter = filter;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minfilter);
	}
	inline void SetMagFilter(const ImageFilter filter)
	{
		m_magfilter = filter;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_magfilter);
	}
};