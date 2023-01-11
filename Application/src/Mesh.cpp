/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobil   : (+86)136 4741 2733
 * Comment : 将 VAO - (VBO, EBO) 抽象为Mesh类
 */

#include "Mesh.h"

Mesh::Mesh(float* vertices, int vsize, unsigned int* indices, int icount) : m_icount(icount)
{
	//绑定，数据复制到显存
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(float), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	//默认传参 位置 法线 uv
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);										//position vec3
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float)));		//normal vec3
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(6 * sizeof(float)));		//uv vec2
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//解绑
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}
