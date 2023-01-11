#pragma once

class Shader final
{
private:
	unsigned int m_vsid;	//顶点shader id
	unsigned int m_fsid;	//片元shader id
	void CompileShader(const char* vertexShader, const char* fragmentShader);
public:
	/// <summary>
	/// 编译并保存shader程序
	/// </summary>
	/// <param name="vertexShader">顶点shader文本</param>
	/// <param name="fragmentShader">片元shader文本</param>
	Shader(const char* vertexShader, const char* fragmentShader);

	/// <summary>
	/// 编译并保存shader程序
	/// </summary>
	/// <param name="shaderfilePath">shader文本文件路径，格式请参考样例shader</param>
	Shader(const char* shaderfilePath);

	/// <summary>
	/// 析构时，删除并释放shader程序显存
	/// </summary>
	~Shader();

	/// <summary>
	/// 获取shader程序id
	/// </summary>
	/// <param name="vertid">顶点shader程序id数据位</param>
	/// <param name="fragid">片元shader程序id数据位</param>
	void GetID(unsigned int* vertid, unsigned int* fragid) const;
};