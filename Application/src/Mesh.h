#pragma once
#include <unordered_map>

class Mesh
{
private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	int m_icount;
public:
	Mesh(float* vertices, int vcount, unsigned int* indices, int icount);
	~Mesh();

	unsigned int GetID() const;
	int GetDrawCount() const;
	void Use() const;
	void Unuse() const;
};