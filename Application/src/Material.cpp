#include "Material.h"
#include <GL/glew.h>

Material::Material(const Shader& shader)
{
	m_id = glCreateProgram();
	unsigned int vsid = 0, fsid = 0;
	shader.GetID(&vsid, &fsid);
	glAttachShader(m_id, vsid);
	glAttachShader(m_id, fsid);
	glLinkProgram(m_id);
	int linkstatus;
	glGetProgramiv(m_id, GL_LINK_STATUS, &linkstatus);
	if (!linkstatus) {
		int len;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &len);
		char* msg = (char*)alloca(len * sizeof(char));
		glGetProgramInfoLog(m_id, len, &len, msg);
		Log::Error(msg, "ShaderProgramLinkError");
	}
}

Material::~Material()
{
	glDeleteProgram(m_id);
}

unsigned int Material::GetID() const
{
	return m_id;
}

void Material::Use() const
{
	glUseProgram(m_id);
}

void Material::Unuse() const
{
	glUseProgram(0);
}
