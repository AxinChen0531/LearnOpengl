#include "Shader.h"
#include <memory>
#include "Log.h"

#include <GL/glew.h>

Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
	int compileStatus;
	m_vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vsid, 1, &vertexShader, nullptr);
	glCompileShader(m_vsid);
	glGetShaderiv(m_vsid, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		int len;
		glGetShaderiv(m_vsid, GL_INFO_LOG_LENGTH, &len);
		char* msg = (char*)alloca(len * sizeof(char));
		glGetShaderInfoLog(m_vsid, len, &len, msg);
		Log::Error(msg, "ShaderCompileError");
	}

	m_fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fsid, 1, &fragmentShader, nullptr);
	glCompileShader(m_fsid);
	glGetShaderiv(m_fsid, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		int len;
		glGetShaderiv(m_fsid, GL_INFO_LOG_LENGTH, &len);
		char* msg = (char*)alloca(len * sizeof(char));
		glGetShaderInfoLog(m_fsid, len, &len, msg);
		Log::Error(msg, "ShaderCompileError");
	}
}

Shader::~Shader()
{
	glDeleteShader(m_vsid);
	glDeleteShader(m_fsid);
}

void Shader::GetShaderID(unsigned int* vertid, unsigned int* fragid) const
{
	*vertid = m_vsid;
	*fragid = m_fsid;
}
