#include "Material.h"

Material::Material(const Shader& shader) : m_needBlend(true), m_needZTest(true), m_needZWrite(true), 
										   m_srcfactor(BlendParam::SRC_ALPHA), m_dstfactor(BlendParam::ONE_MINUS_SRC_ALPHA), 
										   m_zTestCondition(ZTestCondition::LESS)
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
		Log::Error(msg, "ShaderProgramLinkERR");
	}
}

Material::~Material()
{
	glDeleteProgram(m_id);
}

void Material::Use() const
{
	if (m_needBlend) {
		glEnable(GL_BLEND);
		glBlendFunc(m_srcfactor, m_dstfactor);
	} else 
		glDisable(GL_BLEND);

	if (m_needZTest) {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(m_zTestCondition);
	} else 
		glDisable(GL_DEPTH_TEST);

	m_needZWrite ? glDepthMask(GL_TRUE) : glDepthMask(GL_FALSE);
	glUseProgram(m_id);
}
