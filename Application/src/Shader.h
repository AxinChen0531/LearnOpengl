#pragma once

class Shader final
{
private:
	unsigned int m_vsid;	//����shader id
	unsigned int m_fsid;	//ƬԪshader id
	void CompileShader(const char* vertexShader, const char* fragmentShader);
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
};