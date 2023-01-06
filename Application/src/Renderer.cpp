#include "Renderer.h"
#include <GL/glew.h>

Renderer::Renderer(Mesh* mesh, Material* mat) : m_mesh(mesh), m_mat(mat)
{
}

Renderer::~Renderer()
{
}

void Renderer::Render() const
{
	m_mesh->Use();
	m_mat->Use();
	glDrawElements(GL_TRIANGLES, m_mesh->GetDrawCount(), GL_UNSIGNED_INT, 0);
	m_mesh->Unuse();
	m_mat->Unuse();
}
