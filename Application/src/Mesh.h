/*
 * Author  : ����(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : �� VAO - (VBO, EBO) ����ΪMesh��
 */

#pragma once

#include <GL/glew.h>

/// <summary>
/// ʹ��Mesh�࣬��VAO,VBO,EBO���з�װ����
/// ��ʹ������ָ�����Mesh���󣬱�����ֿ���Ⱦ
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
	/// ͨ�������Ķ������� �� �������ݴ�����Ӧ��VAO
	/// Ҫ��ÿ��������˳����� λ��(3)������(3)��uv(2) ����������
	/// Ҫ����������Ϊ�����λ����Ų�
	/// </summary>
	/// <param name="vertices">�����������ָ��</param>
	/// <param name="vcsize">���������ֽڴ�С</param>
	/// <param name="indices">�����������ָ��</param>
	/// <param name="icount">�������ݸ���</param>
	Mesh(float* vertices, int vcsize, unsigned int* indices, int icount);

	/// <summary>
	/// ����ʱ�����ͷ����������Դ�
	/// </summary>
	~Mesh();

	/// <summary>
	/// ���ظ���������Ӧ��VAO ID
	/// </summary>
	/// <returns></returns>
	inline unsigned int GetID() const
	{
		return vao;
	}

	/// <summary>
	/// ��ȡ���ƶ�����ܴ���
	/// </summary>
	/// <returns></returns>
	inline int GetDrawCount() const
	{
		return m_icount;
	}

	/// <summary>
	/// ʹ�ø����񣨰󶨸�VAO��
	/// </summary>
	inline void Use() const
	{
		glBindVertexArray(vao);
	}

	/// <summary>
	/// ���ø����񣨽���VAO��
	/// </summary>
	inline void Unuse() const
	{
		glBindVertexArray(0);
	}
};