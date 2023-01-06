#pragma once
#include "Mesh.h"
#include "Material.h"

class Renderer
{
private:
	Mesh* m_mesh;
	Material* m_mat;
public:
	Renderer(Mesh* mesh, Material* mat);
	~Renderer();

	void Rendering() const;
};