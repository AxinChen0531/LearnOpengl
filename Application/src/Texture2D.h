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

class Texture2D final
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
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void SetHorizontalWarpingMode(ImageWarpingMode mode);
	void SetVerticalWarpingMode(ImageWarpingMode mode);
	void SetMinFilter(ImageFilter filter);
	void SetMagFilter(ImageFilter filter);

};