/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobil   : (+86)136 4741 2733
 * Comment : 将 Mesh - Material 的组合渲染单元抽象为Render类
 */

#pragma once
#include "Mesh.h"
#include "Material.h"
#include <memory>

class Renderer
{
private:
	std::shared_ptr<Mesh> m_mesh;		//网格指针
	std::shared_ptr<Material> m_mat;	//材质指针

public:
	/// <summary>
	/// 传入的网格和对应材质，作为一个渲染单元
	/// 请统一对网格和材质管理对象使用智能指针进行管理，避免出现资源为空，渲染错误的情况
	/// 即在释放网格和材质前，需要先释放管理他们的渲染单元
	/// </summary>
	/// <param name="mesh">网格对象指针</param>
	/// <param name="mat">材质对象指针</param>
	Renderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat);

	/// <summary>
	/// 析构时，将释放管理的网格和材质智能指针
	/// </summary>
	~Renderer();

	/// <summary>
	/// 利用管理的网格和材质进行渲染
	/// </summary>
	void Render() const;
};