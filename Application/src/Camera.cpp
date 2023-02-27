/*
* Author  : 陈鑫(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : 抽象Camera类，提供视角变换和渲染后处理能力
*/

#include "Camera.h"
#include "Screen.h"
#include "Log.h"

Camera::Camera()
{
	m_projection = ProjectionType::Perspective;
	m_width = 4.0f;
	m_fov = 0.5f * Mathf::PI;
	m_aspect = 1.0f;
	m_nearplaneDist = 1.0f;
	m_farplaneDist = 50.0f;
	post_mat = nullptr;
}

void Camera::Awake(ProjectionType pt)
{
	m_projection = pt;
	if (pt == ProjectionType::Perspective) {
		m_pMat[0][0] = 1.0f;
		m_pMat[1][1] = 1.0f;
		m_pMat[2][2] = 51.0f / 49.0f;
		m_pMat[2][3] = -100.0f / 49.0f;
		m_pMat[3][2] = 1.0f;
	} else {
		m_pMat[0][0] = 0.5f;
		m_pMat[1][1] = 0.5f;
		m_pMat[2][2] = 2.0f / 49.0f;
		m_pMat[2][3] = -51.0f / 49.0f;
		m_pMat[3][3] = 1.0f;
	}

	int w = Screen::Instance()->GetWidth();
	int h = Screen::Instance()->GetHeight();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), post_vertex, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), post_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);										//position vec2
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float)));		//uv vec2
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	cba = std::shared_ptr<Texture2D>(new Texture2D(w, h));
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cba.get()->GetID(), 0);
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		Log::Error("Framebuffer is not complete!", "GL_ERR");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Camera::~Camera()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	glDeleteFramebuffers(1, &fbo);
	cba = nullptr;
	glDeleteRenderbuffers(1, &rbo);
}

void Camera::SetProjectionType(ProjectionType pt)
{
	if (pt == m_projection)
		return;
	if (pt == ProjectionType::Perspective) {
		m_pMat[3][3] = 0.0f;
		float t = 1.0f / Mathf::Tan(0.5f * m_fov);
		m_pMat[0][0] = t / m_aspect;
		m_pMat[1][1] = t;
		m_pMat[2][2] = (m_farplaneDist + m_nearplaneDist) / (m_farplaneDist - m_nearplaneDist);
		m_pMat[2][3] = 2.0f * m_nearplaneDist * m_farplaneDist / (m_nearplaneDist - m_farplaneDist);
		m_pMat[3][2] = 1.0f;
	} else {
		float t = 2.0f / m_width;
		m_pMat[3][3] = 1.0f;
		m_pMat[3][2] = 0.0f;
		m_pMat[0][0] = t;
		m_pMat[1][1] = t * m_aspect;
		m_pMat[2][2] = 2.0f / (m_farplaneDist - m_nearplaneDist);
		m_pMat[2][3] = (m_farplaneDist + m_nearplaneDist) / (m_nearplaneDist - m_farplaneDist);
	}
	m_projection = pt;
}

void Camera::SetFOV_Rad(float rad)
{
	rad = Mathf::Clamp(rad, 0.017f, Mathf::PI);
	if (m_projection == ProjectionType::Perspective) {
		float nt = 1.0f / Mathf::Tan(rad * 0.5f);
		m_pMat[0][0] = nt / m_aspect;
		m_pMat[1][1] = nt;
	}
	m_fov = rad;
}

void Camera::SetWidth(float w)
{
	w = Mathf::Clamp(w, 0.1f, 100.0f);
	if (m_projection == ProjectionType::Orthographic) {
		float k = m_width / w;
		m_pMat[0][0] = m_pMat[0][0] * k;
		m_pMat[1][1] = m_pMat[1][1] * k;
	}
	m_width = w;
}

void Camera::SetAspect(float asp)
{
	asp = Mathf::Clamp(asp, 0.01f, 100.0f);
	if (m_projection == ProjectionType::Perspective) {
		m_pMat[0][0] = m_pMat[0][0] * m_aspect / asp;
	} else {
		m_pMat[1][1] = m_pMat[1][1] * asp / m_aspect;
	}
	m_aspect = asp;
}

void Camera::SetNearPlaneDist(float n)
{
	if (n < 0.1f)
		n = 0.1f;
	if (m_farplaneDist - n < 0.1f)
		m_farplaneDist = n + 0.1f;
	if (m_projection == ProjectionType::Perspective) {
		m_pMat[2][2] = (m_farplaneDist + n) / (m_farplaneDist - n);
		m_pMat[2][3] = 2.0f * n * m_farplaneDist / (n - m_farplaneDist);
	} else {
		m_pMat[2][2] = 2.0f / (m_farplaneDist - n);
		m_pMat[3][3] = (m_farplaneDist + n) / (n - m_farplaneDist);
	}
	m_nearplaneDist = n;
}

void Camera::SetFarPlaneDist(float f)
{
	if (f < 0.2f)
		f = 0.2f;
	if (f - m_nearplaneDist < 0.1f)
		m_nearplaneDist = f - 0.1f;
	if (m_projection == ProjectionType::Perspective) {
		m_pMat[2][2] = (f + m_nearplaneDist) / (f - m_nearplaneDist);
		m_pMat[2][3] = 2.0f * m_nearplaneDist * f / (m_nearplaneDist - f);
	} else {
		m_pMat[2][2] = 2.0f / (f - m_nearplaneDist);
		m_pMat[3][3] = (f + m_nearplaneDist) / (m_nearplaneDist - f);
	}
	m_farplaneDist = f;
}

void Camera::SetNearFarPlaneDist(float n, float f)
{
	if (n < 0.1f)
		n = 0.1f;
	if (f - n < 0.1f)
		f = n + 0.1f;
	if (m_projection == ProjectionType::Perspective) {
		m_pMat[2][2] = (f + n) / (f - n);
		m_pMat[2][3] = 2.0f * n * f / (n - f);
	} else {
		m_pMat[2][2] = 2.0f / (f - n);
		m_pMat[3][3] = (f + n) / (n - f);
	}
	m_nearplaneDist = n;
	m_farplaneDist = f;
}

void Camera::Begin() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glDepthMask(GL_TRUE);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Camera::End() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Camera::SetPostProcessingMat(std::shared_ptr<Material>& mat) 
{
	post_mat = mat;
	post_mat.get()->SetTexture2D("MainTexture", cba);
}

void Camera::PostProcessing() const
{
	glBindVertexArray(vao);
	post_mat.get()->Use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	post_mat.get()->Unuse();
}