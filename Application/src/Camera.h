#pragma once

#include <GL/glew.h>

#include "AMath.h"

enum ProjectionType
{
	Perspective,	//透视投影
	Orthographic,	//正交投影
};

/// <summary>
/// 摄像机类，用于组织渲染，规划投影矩阵
/// </summary>
class Camera final
{
private:
	Matrix4x4 m_pMat;					//投影矩阵（考虑到透视投影，使用完后要进行齐次化，建议在shader中进行），以摄像机正向为观察空间正向
	ProjectionType m_projection;		//投影类型
	float m_fov;						//横向FOV（仅在透视投影情况下有效）
	float m_width;						//高度（仅在正交投影情况下有效）
	float m_aspect;						//宽高比
	float m_farplaneDist;				//远平面距离
	float m_nearplaneDist;				//近平面距离

public:
	Camera(ProjectionType pt);
	~Camera();

	/// <summary>
	/// 设置投影模式
	/// </summary>
	/// <param name="pt">投影模式</param>
	void SetProjectionType(ProjectionType pt);

	/// <summary>
	/// 获取FOV（横向）弧度值
	/// </summary>
	/// <returns></returns>
	inline float GetFOV_Rad() const {
		return m_fov;
	}

	/// <summary>
	/// 获取FOV（横向）角度值
	/// </summary>
	/// <returns></returns>
	inline float GetFOV_Deg() const {
		return m_fov * Mathf::Rad2Deg;
	}

	/// <summary>
	/// 设置FOV（横向）弧度，仅在透视投影情况下有效
	/// FOV弧度限制在0.017f - pi之间
	/// </summary>
	/// <param name="rad"></param>
	void SetFOV_Rad(float rad);

	/// <summary>
	/// 设置FOV（横向）角度，仅在透视投影情况下有效
	/// </summary>
	/// <param name="degree"></param>
	inline void SetFOV_Deg(float degree) {
		SetFOV_Rad(degree * Mathf::Deg2Rad);
	}

	/// <summary>
	/// 获取宽度
	/// </summary>
	/// <returns></returns>
	inline float GetWidth() const {
		return m_width;
	}

	/// <summary>
	/// 设置宽度，仅在透视投影情况下有效
	/// 宽度限制在0.1f - 100.0f之间
	/// </summary>
	/// <param name="w"></param>
	void SetWidth(float w);

	/// <summary>
	/// 获取宽高比
	/// </summary>
	/// <returns></returns>
	inline float GetAspect() const {
		return m_aspect;
	}

	/// <summary>
	/// 设置宽高比
	/// 比值限制在0.01f - 100.0f之间
	/// </summary>
	/// <param name="asp"></param>
	void SetAspect(float asp);

	/// <summary>
	/// 获取近平面距离
	/// </summary>
	/// <returns></returns>
	inline float GetFarPlaneDist() const {
		return m_farplaneDist;
	}

	/// <summary>
	/// 获取远平面距离
	/// </summary>
	/// <returns></returns>
	inline float GetNearPlaneDist() const {
		return m_nearplaneDist;
	}

	/// <summary>
	/// 设置近平面距离
	/// 若所给值小于0.1f，则自动补充到0.1f
	/// 设置后若远平面距 - 近平面距 < 0.1f，则自动将远平面距离提升至 n + 0.1f 
	/// </summary>
	/// <param name="n">近平面距离</param>
	void SetNearPlaneDist(float n);

	/// <summary>
	/// 设置远平面距离
	/// 若所给值小于0.2f，则自动补充到0.2f
	/// 设置后若远平面距 - 近平面距 < 0.1f，则自动将近平面距离缩小至 f - 0.1f 
	/// </summary>
	/// <param name="f">远平面距离</param>
	void SetFarPlaneDist(float f);

	/// <summary>
	/// 设置近平面及远平面距离
	/// 若近平面小于0.1f，则自动补充到0.1f
	/// 设置后若远平面距 - 近平面距 < 0.1f，则自动将远平面距离提升至 n + 0.1f 
	/// </summary>
	/// <param name="n">近平面距离</param>
	/// <param name="f">远平面距离</param>
	void SetNearFarPlaneDist(float n, float f);
};
