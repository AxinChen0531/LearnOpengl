/*
* Author  : 陈鑫(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : 抽象Camera类，提供视角变换和渲染后处理能力
*/

#pragma once

#include <GL/glew.h>
#include <memory>

#include "AMath.h"
#include "Material.h"
#include "Texture2D.h"
#include "Object.h"

enum ProjectionType
{
	Perspective,	//透视投影
	Orthographic,	//正交投影
};

/// <summary>
/// 摄像机类，用于组织渲染，规划投影矩阵
/// </summary>
class Camera final : public Component, public IAwake1<ProjectionType>
{
private:
	Matrix4x4 m_pMat;					//投影矩阵（考虑到透视投影，使用完后要进行齐次化(shader将自动齐次)），以摄像机正向为观察空间正向
	ProjectionType m_projection;		//投影类型
	float m_fov;						//横向FOV（仅在透视投影情况下有效）
	float m_width;						//宽度（仅在正交投影情况下有效）
	float m_aspect;						//宽高比
	float m_farplaneDist;				//远平面距离
	float m_nearplaneDist;				//近平面距离


	/*
	 * 后处理framebuffer相关
	 * 默认传参策略和一般模型不同，请注意
	 */
	float post_vertex[16] = {
		//pos			//uv
		 1.0f,  1.0f,	1.0f, 1.0f,	// 右上角
		 1.0f, -1.0f,	1.0f, 0.0f,	// 右下角
		-1.0f, -1.0f,	0.0f, 0.0f,	// 左下角
		-1.0f,  1.0f,	0.0f, 1.0f	// 左上角
	};
	unsigned int post_indices[6]  = {
		3, 1, 0,
		3, 2, 1
	};
	unsigned int fbo;
	std::shared_ptr<Texture2D> cba;
	unsigned int rbo;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	std::shared_ptr<Material> post_mat;

public:
	Camera();
	Camera(const Camera&) = delete;
	void Awake(ProjectionType pt) override;
	~Camera() override;
	inline const type_info* GetTypeInfo() const override {
		return &typeid(Camera);
	}

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

	/// <summary>
	/// 开始参与到渲染，后续截取输出离屏渲染
	/// </summary>
	void Begin() const;

	/// <summary>
	/// 结束离屏渲染
	/// </summary>
	void End() const;

	/// <summary>
	/// 设置后处理材质
	/// </summary>
	/// <param name="mat">后处理材质</param>
	void SetPostProcessingMat(std::shared_ptr<Material>& mat);

	/// <summary>
	/// 利用给定的材质进行后处理渲染，将离屏buffer渲染出去
	/// </summary>
	void PostProcessing() const;
};
