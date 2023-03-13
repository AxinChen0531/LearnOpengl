/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : 将shader program实例抽象为Material类
 */

#include "Material.h"
#include "Log.h"

Material::Material(const Shader* shader) : m_needBlend(true), m_needZTest(true), m_needZWrite(true), 
										   m_srcfactor(BlendParam::SRC_ALPHA), m_dstfactor(BlendParam::ONE_MINUS_SRC_ALPHA), 
										   m_zTestCondition(ZTestCondition::LESS_OR_EQUAL), 
										   m_texSlotOccupied(0)
{
	m_id = glCreateProgram();
	unsigned int vsid = 0, fsid = 0;
	shader->GetID(&vsid, &fsid);
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

	for (auto p : t2ds) {
		std::shared_ptr<Texture2D> t2d = p.second.second;
		int slot = p.second.first;
		if (t2d.use_count()) {
			glActiveTexture(slot);
			t2d.get()->Use();
		}
	}
	glUseProgram(m_id);
}

int Material::GetUniformID(const std::string name)
{
	if (uniformMaps.find(name) != uniformMaps.end())
		return uniformMaps[name];
	int id = glGetUniformLocation(m_id, name.c_str());
	if (id != -1) 
		uniformMaps[name] = id;
	return id;
}

float Material::GetFloat(int id) const
{
	glUseProgram(m_id);
	float p = 0;
	glGetUniformfv(m_id, id, &p);
	glUseProgram(0);
	return p;
}

void Material::GetVecf(int id, float* arr) const
{
	glUseProgram(m_id);
	glGetUniformfv(m_id, id, arr);
	glUseProgram(0);
}

int Material::GetInt(int id) const
{
	glUseProgram(m_id);
	int p = 0;
	glGetUniformiv(m_id, id, &p);
	glUseProgram(0);
	return p;
}

void Material::GetVeci(int id, int* arr) const
{
	glUseProgram(m_id);
	glGetUniformiv(m_id, id, arr);
	glUseProgram(0);
}

void Material::SetBlendParam(const BlendParam srcf, const BlendParam dstf)
{
	m_srcfactor = srcf;
	m_dstfactor = dstf;
	m_needBlend = true;
}

void Material::SetTexture2D(int id, std::shared_ptr<Texture2D>& t2d) 
{
	if (id == -1)
		return;
	if (t2ds.find(id) == t2ds.end()) {
		int slot = GL_TEXTURE0 + m_texSlotOccupied;
		SetInt(id, m_texSlotOccupied);
		t2ds[id] = std::pair<int, std::shared_ptr<Texture2D>>(slot, t2d);
		m_texSlotOccupied++;
	} else {
		t2ds[id].second = t2d;
	}
}
