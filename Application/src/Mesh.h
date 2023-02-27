/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : 将 VAO - (VBO, EBO) 抽象为Mesh类
 */

#pragma once

#include <GL/glew.h>

/// <summary>
/// 使用Mesh类，对VAO,VBO,EBO进行封装管理
/// 请使用智能指针管理Mesh对象，避免出现空渲染
/// </summary>
class Mesh final
{
private:
	unsigned int vao;	//vao id
	unsigned int vbo;	//vbo id
	unsigned int ebo;	//ebo id
	int m_icount;
public:
	/// <summary>
	/// 通过给定的顶点数据 和 索引数据创建对应的VAO
	/// 要求每个顶点依顺序包含 位置(3)，法线(3)，uv(2) 这三个属性
	/// 要求索引数据为三角形绘制排布
	/// </summary>
	/// <param name="vertices">顶点数据起点指针</param>
	/// <param name="vcsize">顶点数据字节大小</param>
	/// <param name="indices">索引数据起点指针</param>
	/// <param name="icount">索引数据个数</param>
	Mesh(float* vertices, int vcsize, unsigned int* indices, int icount);

	/// <summary>
	/// 析构时，将释放网格数据显存
	/// </summary>
	~Mesh();

	/// <summary>
	/// 返回该网格对象对应的VAO ID
	/// </summary>
	/// <returns></returns>
	inline unsigned int GetID() const
	{
		return vao;
	}

	/// <summary>
	/// 获取绘制顶点的总次数
	/// </summary>
	/// <returns></returns>
	inline int GetDrawCount() const
	{
		return m_icount;
	}

	/// <summary>
	/// 使用该网格（绑定该VAO）
	/// </summary>
	inline void Use() const
	{
		glBindVertexArray(vao);
	}

	/// <summary>
	/// 禁用该网格（解绑该VAO）
	/// </summary>
	inline void Unuse() const
	{
		glBindVertexArray(0);
	}
};