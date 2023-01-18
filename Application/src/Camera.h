#pragma once

#include <GL/glew.h>

#include "AMath.h"

enum ProjectionType
{
	Perspective,	//͸��ͶӰ
	Orthographic,	//����ͶӰ
};

/// <summary>
/// ������࣬������֯��Ⱦ���滮ͶӰ����
/// </summary>
class Camera final
{
private:
	Matrix4x4 m_pMat;					//ͶӰ���󣨿��ǵ�͸��ͶӰ��ʹ�����Ҫ������λ���������shader�н��У��������������Ϊ�۲�ռ�����
	ProjectionType m_projection;		//ͶӰ����
	float m_fov;						//����FOV������͸��ͶӰ�������Ч��
	float m_width;						//�߶ȣ���������ͶӰ�������Ч��
	float m_aspect;						//��߱�
	float m_farplaneDist;				//Զƽ�����
	float m_nearplaneDist;				//��ƽ�����

public:
	Camera(ProjectionType pt);
	~Camera();

	/// <summary>
	/// ����ͶӰģʽ
	/// </summary>
	/// <param name="pt">ͶӰģʽ</param>
	void SetProjectionType(ProjectionType pt);

	/// <summary>
	/// ��ȡFOV�����򣩻���ֵ
	/// </summary>
	/// <returns></returns>
	inline float GetFOV_Rad() const {
		return m_fov;
	}

	/// <summary>
	/// ��ȡFOV�����򣩽Ƕ�ֵ
	/// </summary>
	/// <returns></returns>
	inline float GetFOV_Deg() const {
		return m_fov * Mathf::Rad2Deg;
	}

	/// <summary>
	/// ����FOV�����򣩻��ȣ�����͸��ͶӰ�������Ч
	/// FOV����������0.017f - pi֮��
	/// </summary>
	/// <param name="rad"></param>
	void SetFOV_Rad(float rad);

	/// <summary>
	/// ����FOV�����򣩽Ƕȣ�����͸��ͶӰ�������Ч
	/// </summary>
	/// <param name="degree"></param>
	inline void SetFOV_Deg(float degree) {
		SetFOV_Rad(degree * Mathf::Deg2Rad);
	}

	/// <summary>
	/// ��ȡ���
	/// </summary>
	/// <returns></returns>
	inline float GetWidth() const {
		return m_width;
	}

	/// <summary>
	/// ���ÿ�ȣ�����͸��ͶӰ�������Ч
	/// ���������0.1f - 100.0f֮��
	/// </summary>
	/// <param name="w"></param>
	void SetWidth(float w);

	/// <summary>
	/// ��ȡ��߱�
	/// </summary>
	/// <returns></returns>
	inline float GetAspect() const {
		return m_aspect;
	}

	/// <summary>
	/// ���ÿ�߱�
	/// ��ֵ������0.01f - 100.0f֮��
	/// </summary>
	/// <param name="asp"></param>
	void SetAspect(float asp);

	/// <summary>
	/// ��ȡ��ƽ�����
	/// </summary>
	/// <returns></returns>
	inline float GetFarPlaneDist() const {
		return m_farplaneDist;
	}

	/// <summary>
	/// ��ȡԶƽ�����
	/// </summary>
	/// <returns></returns>
	inline float GetNearPlaneDist() const {
		return m_nearplaneDist;
	}

	/// <summary>
	/// ���ý�ƽ�����
	/// ������ֵС��0.1f�����Զ����䵽0.1f
	/// ���ú���Զƽ��� - ��ƽ��� < 0.1f�����Զ���Զƽ����������� n + 0.1f 
	/// </summary>
	/// <param name="n">��ƽ�����</param>
	void SetNearPlaneDist(float n);

	/// <summary>
	/// ����Զƽ�����
	/// ������ֵС��0.2f�����Զ����䵽0.2f
	/// ���ú���Զƽ��� - ��ƽ��� < 0.1f�����Զ�����ƽ�������С�� f - 0.1f 
	/// </summary>
	/// <param name="f">Զƽ�����</param>
	void SetFarPlaneDist(float f);

	/// <summary>
	/// ���ý�ƽ�漰Զƽ�����
	/// ����ƽ��С��0.1f�����Զ����䵽0.1f
	/// ���ú���Զƽ��� - ��ƽ��� < 0.1f�����Զ���Զƽ����������� n + 0.1f 
	/// </summary>
	/// <param name="n">��ƽ�����</param>
	/// <param name="f">Զƽ�����</param>
	void SetNearFarPlaneDist(float n, float f);
};
