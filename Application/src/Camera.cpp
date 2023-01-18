#include "Camera.h"

Camera::Camera(ProjectionType pt)
{
	m_projection = pt;
	m_width = 4.0f;
	m_fov = 0.5f * Mathf::PI;
	m_aspect = 1.0f;
	m_nearplaneDist = 1.0f;
	m_farplaneDist = 50.0f;
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
}

Camera::~Camera()
{

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