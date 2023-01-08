#pragma once
#include "Mesh.h"
#include "Material.h"
#include <memory>

class Renderer
{
private:
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Material> m_mat;

public:
	Renderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat);
	~Renderer();

	void Render() const;
};