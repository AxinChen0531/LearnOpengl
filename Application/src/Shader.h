/*
 * Author  : ����(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : ����shader�࣬���Դ��е�shader����ν��й���
 */

#pragma once

#include <string>

class Shader final
{
private:
	unsigned int m_vsid;	//����shader id
	unsigned int m_fsid;	//ƬԪshader id

public:
	/// <summary>
	/// ���벢����shader����
	/// </summary>
	/// <param name="vertexShader">����shader�ı�</param>
	/// <param name="fragmentShader">ƬԪshader�ı�</param>
	Shader(const char* vertexShader, const char* fragmentShader);

	/// <summary>
	/// ���벢����shader����
	/// </summary>
	/// <param name="shaderfilePath">shader�ı��ļ�·������ʽ��ο�����shader</param>
	Shader(const char* shaderfilePath);

	/// <summary>
	/// ����ʱ��ɾ�����ͷ�shader�����Դ�
	/// </summary>
	~Shader();

	/// <summary>
	/// ��ȡshader����id
	/// </summary>
	/// <param name="vertid">����shader����id����λ</param>
	/// <param name="fragid">ƬԪshader����id����λ</param>
	void GetID(unsigned int* vertid, unsigned int* fragid) const;

private:
	/// <summary>
	/// ����shader
	/// </summary>
	/// <param name="vertexShader"></param>
	/// <param name="fragmentShader"></param>
	void CompileShader(const char* vertexShader, const char* fragmentShader);
	void Include(const std::string& path, std::stringstream& ss) const;
};