/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : 将 Mesh - Material 的组合渲染单元抽象为Render类
 */


#include "Renderer.h"
#include <GL/glew.h>

Renderer::Renderer(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Material>& mat) : m_mesh(mesh), m_mat(mat)
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
