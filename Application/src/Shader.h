#pragma once

class Shader final
{
private:
	unsigned int m_vsid;
	unsigned int m_fsid;
	void CompileShader(const char* vertexShader, const char* fragmentShader);
public:
	Shader(const char* vertexShader, const char* fragmentShader);
	Shader(const char* shaderfilePath);
	~Shader();

	void GetID(unsigned int* vertid, unsigned int* fragid) const;
};