#pragma once
#include <unordered_map>

#include <GL/glew.h>

class Mesh final
{
private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	int m_icount;
public:
	Mesh(float* vertices, int vcount, unsigned int* indices, int icount);
	~Mesh();

	inline unsigned int GetID() const
	{
		return vao;
	}
	inline int GetDrawCount() const
	{
		return m_icount;
	}
	inline void Use() const
	{
		glBindVertexArray(vao);
	}
	inline void Unuse() const
	{
		glBindVertexArray(0);
	}
};