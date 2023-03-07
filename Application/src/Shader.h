/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : 抽象shader类，对显存中的shader代码段进行管理
 */

#pragma once

#include <string>

class Shader final
{
private:
	unsigned int m_vsid;	//顶点shader id
	unsigned int m_fsid;	//片元shader id

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

private:
	/// <summary>
	/// 编译shader
	/// </summary>
	/// <param name="vertexShader"></param>
	/// <param name="fragmentShader"></param>
	void CompileShader(const char* vertexShader, const char* fragmentShader);
	void Include(const std::string& path, std::stringstream& ss) const;
};