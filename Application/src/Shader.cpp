/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : 抽象shader类，对显存中的shader代码段进行管理
 */

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <string>

#include "Shader.h"
#include "Log.h"

void Shader::CompileShader(const char* vertexShader, const char* fragmentShader)
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
		Log::Error(msg, "ShaderCompileERR");
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
		Log::Error(msg, "ShaderCompileERR");
	}
}

void Shader::Include(const std::string& path, std::stringstream& ss) const
{
	std::string dirPath = path.substr(0, path.find_last_of("/\\") + 1);
	std::ifstream stream(path);
	std::string line;
	if (stream.fail()) 
		Log::Error("Shader include file not found", "PathERR");
	while (std::getline(stream, line)) {
		if (line.find("#include") != std::string::npos) {
			int start = line.find('\"');
			int end = line.find('\"', start + 1);
			Include(dirPath + line.substr(start + 1, end - start - 1), ss);
		}
		else
			ss << line << std::endl;
	}
}

Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
	CompileShader(vertexShader, fragmentShader);
}

Shader::Shader(const char* shaderfilePath)
{
	std::stringstream ss[2];
	std::ifstream stream(shaderfilePath);
	std::string path(shaderfilePath);
	std::string dirPath = path.substr(0, path.find_last_of("/\\") + 1);
	std::string line;
	int index = 0;
	ss[0] << "#version 330 core" << std::endl;
	ss[1] << "#version 330 core" << std::endl;
	if (stream.fail()) 
		Log::Error("Shader file not found", "PathERR");
	while (std::getline(stream, line)) {
		if (line.find("#Vertex") != std::string::npos)
			index = 0;
		else if (line.find("#Fragment") != std::string::npos)
			index = 1;
		else if (line.find("#include") != std::string::npos) {
			int start = line.find("\"");
			int end = line.find("\"", start + 1);
			Include(dirPath + line.substr(start + 1, end - start - 1), ss[index]);
		}
		else
			ss[index] << line << std::endl;
	}
	CompileShader(ss[0].str().c_str(), ss[1].str().c_str());
}

Shader::~Shader()
{
	glDeleteShader(m_vsid);
	glDeleteShader(m_fsid);
}

void Shader::GetID(unsigned int* vertid, unsigned int* fragid) const
{
	*vertid = m_vsid;
	*fragid = m_fsid;
}
