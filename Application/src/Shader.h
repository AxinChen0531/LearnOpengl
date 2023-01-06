#pragma once

class Shader
{
private:
	unsigned int m_vsid;
	unsigned int m_fsid;

public:
	Shader(const char* vertexShader, const char* fragmentShader);
	~Shader();

	void GetID(unsigned int* vertid, unsigned int* fragid) const;
};