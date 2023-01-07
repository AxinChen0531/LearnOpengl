#include "Texture2D.h"
#include "Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

void Texture2D::SetYFlip(bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
}

Texture2D::Texture2D(const char* imgPath) : m_verWarping(ImageWarpingMode::REPEAT), m_horWarping(ImageWarpingMode::REPEAT),
										m_minfilter(ImageFilter::LINEAR), m_magfilter(ImageFilter::LINEAR),
										m_format(ImageFormat::RGBA), m_channelCount(0), m_width(0), m_height(0)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	unsigned char* img = stbi_load(imgPath, &m_width, &m_height, &m_channelCount, 0);
	if (m_channelCount == 1 || m_channelCount == 3 || m_channelCount == 4) {
		if (m_channelCount == 1) m_format = ImageFormat::Alpha;
		else if (m_channelCount == 3) m_format = ImageFormat::RGB;
		else m_format = ImageFormat::RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_horWarping);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_verWarping);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minfilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magfilter);
	} else {
		Log::Error("Texture format unsupported, please make sure the channel of the texture is 1 or 3 or 4", "TextureLoadERR");
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(img);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_id);
}
